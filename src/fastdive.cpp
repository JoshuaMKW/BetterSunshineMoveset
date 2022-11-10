#include <SMS/Player/Mario.hxx>

#include <SMS/System/MarDirector.hxx>
#include <SMS/Player/Watergun.hxx>
#include <SMS/raw_fn.hxx>
#include <SMS/MSound/MSound.hxx>
#include <SMS/MSound/MSoundSESystem.hxx>

#include <BetterSMS/module.hxx>
#include <BetterSMS/player.hxx>

#include "settings.hxx"


static void uncapDiveSpeed(f32 diveSpeed) {
    TMario *player;
    SMS_FROM_GPR(30, player);

    if (gFastDiveSetting.getBool())
        player->mForwardSpeed = Max(
            48.0f, player->mForwardSpeed + ((player->mState & TMario::STATE_AIRBORN) ? 15.0f : 0));
    else
        player->mForwardSpeed = 48.0f;
}
SMS_PATCH_BL(SMS_PORT_REGION(0x80254920, 0, 0, 0), uncapDiveSpeed);

static void uncapDiveRolloutSpeed() {
    TMario *player;
    SMS_FROM_GPR(30, player);

    if (gFastDiveSetting.getBool())
        player->mForwardSpeed =
            Max(player->mJumpParams.mRotBroadJumpForce.get(), player->mForwardSpeed);
    else
        player->mForwardSpeed = player->mJumpParams.mRotBroadJumpForce.get();
}
SMS_PATCH_BL(SMS_PORT_REGION(0x802549B0, 0, 0, 0), uncapDiveRolloutSpeed);