#include <SMS/Camera/PolarSubCamera.hxx>
#include <SMS/Player/Mario.hxx>

#include <BetterSMS/libs/constmath.hxx>
#include <BetterSMS/module.hxx>

static f32 sLastFactor = 1.0f;
static void updateSlideFOV(CPolarSubCamera *cam) {
    f32 factor = scaleLinearAtAnchor<f32>(gpMarioAddress->mForwardSpeed / 100.0f, 0.5f, 1.0f);

    factor = lerp<f32>(sLastFactor, factor, 0.01f);

    if (factor > 1.0f && gpMarioAddress->mState == static_cast<u32>(TMario::STATE_DIVESLIDE)) {
        sLastFactor = factor;
        reinterpret_cast<f32 *>(cam)[0x48 / 4] *= factor;
    } else {
        sLastFactor = lerp<f32>(sLastFactor, 1.0f, 0.01f);
        reinterpret_cast<f32 *>(cam)[0x48 / 4] *= sLastFactor;
    }
}

static bool updateContexts(CPolarSubCamera *cam) {
    updateSlideFOV(cam);
    return cam->isNormalDeadDemo();
}
SMS_PATCH_BL(SMS_PORT_REGION(0x80023598, 0x80023650, 0, 0), updateContexts);