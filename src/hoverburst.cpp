#include <SMS/Player/Mario.hxx>
#include <SMS/Player/Watergun.hxx>
#include <SMS/raw_fn.hxx>
#include <SMS/MSound/MSound.hxx>
#include <SMS/MSound/MSoundSESystem.hxx>

#include <BetterSMS/module.hxx>
#include "common.hxx"

using namespace BetterSMS;

static bool sIsTriggerNozzleDead = false;

static void checkExecWaterGun(TWaterGun *fludd) {
    if (fludd->mCurrentNozzle != TWaterGun::Hover) {
        fludd->emit();
        return;
    }

    if (!sIsTriggerNozzleDead)
        fludd->emit();
}
SMS_PATCH_BL(SMS_PORT_REGION(0x8024E548, 0x802462D4, 0, 0), checkExecWaterGun);

static void killTriggerNozzle() {
    TNozzleTrigger *nozzle;
    SMS_FROM_GPR(29, nozzle);

    nozzle->mSprayState = TNozzleTrigger::DEAD;
    if (nozzle->mFludd->mCurrentNozzle == TWaterGun::Hover && gHoverBurstSetting.getBool())
        sIsTriggerNozzleDead = true;
}
SMS_PATCH_BL(SMS_PORT_REGION(0x8026C370, 0x802640FC, 0, 0), killTriggerNozzle);

// 0x80262580
// extern -> SME.cpp
static bool checkAirNozzle() {
    TMario *player;
    SMS_FROM_GPR(31, player);

    sIsTriggerNozzleDead &=
        !SMS_IsMarioTouchGround4cm__Fv() && !SMS_IsMarioStatusTypeSwimming__Fv() && !(player->mState == TMario::STATE_NPC_BOUNCE);

    if (player->mFludd->mCurrentNozzle != TWaterGun::Hover)
        return player->mState != static_cast<u32>(TMario::STATE_HOVER_F);

    return (!(player->mState & static_cast<u32>(TMario::STATE_AIRBORN)) || !sIsTriggerNozzleDead);
}
SMS_PATCH_BL(SMS_PORT_REGION(0x80262580, 0x8025A30C, 0, 0), checkAirNozzle);
SMS_WRITE_32(SMS_PORT_REGION(0x80262584, 0x8025A310, 0, 0), 0x2C030000);

// extern -> fluddgeneral.cpp
void checkSpamHover(TMario *player, bool isMario) {
    TWaterGun *fludd = player->mFludd;
    if (!fludd)
        return;

    if ((player->mState & TMario::STATE_WATERBORN))
        return;

    if (fludd->mCurrentNozzle != TWaterGun::Hover || !gHoverBurstSetting.getBool())
        return;

    TNozzleTrigger *nozzle = reinterpret_cast<TNozzleTrigger *>(fludd->mNozzleList[fludd->mCurrentNozzle]);
    auto &emitParams = nozzle->mEmitParams;

    emitParams.mNum.set(1.0f);
    emitParams.mDirTremble.set(0.0f);

    if (player->mController->mButtons.mAnalogR < 0.9f ||
        !(player->mController->mFrameMeaning & 0x80))
        return;

    if ((emitParams.mTriggerTime.get() - nozzle->mSprayQuarterFramesLeft) >= 20)
        return;

    if (nozzle->mFludd->mCurrentWater < 510)
        return;

    emitParams.mNum.set(255.0f);
    emitParams.mDirTremble.set(0.5f);
    nozzle->emit(0);
    nozzle->emit(1);

    nozzle->mSprayQuarterFramesLeft = 0;
    nozzle->mSprayState             = TNozzleTrigger::DEAD;
    nozzle->mFludd->mCurrentWater -= 255;

    player->mSpeed.y += (70.0f * player->mSize.y) - player->mSpeed.y;
    player->mJumpingState &= 0xFFFFFEFF;

    sIsTriggerNozzleDead = true;
    return;
}