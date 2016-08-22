/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkCodec.h"
#include "SkColorSpaceXform.h"
#include "SkColorTable.h"
#include "SkPngChunkReader.h"
#include "SkEncodedFormat.h"
#include "SkImageInfo.h"
#include "SkRefCnt.h"
#include "SkSwizzler.h"

#include "png.h"

class SkStream;

class SkPngCodec : public SkCodec {
public:
    static bool IsPng(const char*, size_t);

    // Assume IsPng was called and returned true.
    static SkCodec* NewFromStream(SkStream*, SkPngChunkReader* = NULL);

    virtual ~SkPngCodec();

protected:
    Result onGetPixels(const SkImageInfo&, void*, size_t, const Options&, SkPMColor*, int*, int*)
            override;
    SkEncodedFormat onGetEncodedFormat() const override { return kPNG_SkEncodedFormat; }
    bool onRewind() override;
    uint32_t onGetFillValue(SkColorType) const override;

    // Helper to set up swizzler, color xforms, and color table. Also calls png_read_update_info.
    bool initializeXforms(const SkImageInfo& requestedInfo, const Options&, SkPMColor* colorPtr,
                          int* colorCount);
    SkSampler* getSampler(bool createIfNecessary) override {
        SkASSERT(fSwizzler);
        return fSwizzler;
    }
    void allocateStorage();

    virtual int readRows(const SkImageInfo& dstInfo, void* dst, size_t rowBytes, int count,
                         int startRow) = 0;

    SkPngCodec(const SkEncodedInfo&, const SkImageInfo&, SkStream*, SkPngChunkReader*,
            png_structp, png_infop, int, int);

    SkAutoTUnref<SkPngChunkReader>     fPngChunkReader;
    png_structp                        fPng_ptr;
    png_infop                          fInfo_ptr;

    // These are stored here so they can be used both by normal decoding and scanline decoding.
    SkAutoTUnref<SkColorTable>         fColorTable;    // May be unpremul.
    SkAutoTDelete<SkSwizzler>          fSwizzler;
    std::unique_ptr<SkColorSpaceXform> fColorXform;
    SkAutoTMalloc<uint8_t>             fStorage;
    uint8_t*                           fSwizzlerSrcRow;
    uint32_t*                          fColorXformSrcRow;
    size_t                             fSrcRowBytes;

    const int                          fNumberPasses;
    int                                fBitDepth;

private:
    bool createColorTable(const SkImageInfo& dstInfo, int* ctableCount);
    void destroyReadStruct();

    typedef SkCodec INHERITED;
};
