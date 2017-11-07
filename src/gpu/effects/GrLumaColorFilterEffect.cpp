/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * This file was autogenerated from GrLumaColorFilterEffect.fp; do not modify.
 */
#include "GrLumaColorFilterEffect.h"
#if SK_SUPPORT_GPU
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLLumaColorFilterEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLLumaColorFilterEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrLumaColorFilterEffect& _outer = args.fFp.cast<GrLumaColorFilterEffect>();
        (void)_outer;
        fragBuilder->codeAppendf(
                "\nhalf luma = dot(half3(0.21260000000000001, 0.71519999999999995, 0.0722), "
                "%s.xyz);\n%s = half4(0.0, 0.0, 0.0, luma);\n",
                args.fInputColor ? args.fInputColor : "half4(1)", args.fOutputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {}
};
GrGLSLFragmentProcessor* GrLumaColorFilterEffect::onCreateGLSLInstance() const {
    return new GrGLSLLumaColorFilterEffect();
}
void GrLumaColorFilterEffect::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                                    GrProcessorKeyBuilder* b) const {}
bool GrLumaColorFilterEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrLumaColorFilterEffect& that = other.cast<GrLumaColorFilterEffect>();
    (void)that;
    return true;
}
GrLumaColorFilterEffect::GrLumaColorFilterEffect(const GrLumaColorFilterEffect& src)
        : INHERITED(kGrLumaColorFilterEffect_ClassID, src.optimizationFlags()) {}
std::unique_ptr<GrFragmentProcessor> GrLumaColorFilterEffect::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrLumaColorFilterEffect(*this));
}
#endif
