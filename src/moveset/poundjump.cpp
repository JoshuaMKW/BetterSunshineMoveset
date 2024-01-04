
#include <SMS/MSound/MSound.hxx>
#include <SMS/MSound/MSoundSESystem.hxx>
#include <SMS/Player/Mario.hxx>
#include <SMS/Player/Watergun.hxx>
#include <SMS/System/Application.hxx>
#include <SMS/System/MarDirector.hxx>
#include <SMS/raw_fn.hxx>

#include <BetterSMS/memory.hxx>
#include <BetterSMS/module.hxx>
#include <BetterSMS/player.hxx>

#include "common.hxx"

using namespace BetterSMS;

u32 PoundJumpState = 0xF00001C2;

BETTER_SMS_FOR_CALLBACK void checkForPoundJump(TMario *player, bool isMario) {
    if (gpMarDirector->mCurState != TMarDirector::Status::STATE_NORMAL)
        return;

    if (!isMario || player->onYoshi() || !gPoundJumpSetting.getBool())
        return;

    if (player->mState != TMario::STATE_SLAM)
        return;

    if ((player->mActionState & 0x8) || player->isForceSlip())
        return;

    if ((player->mFloorTriangle->mType & 0x1FFF) == 7)
        return;

    auto *controller = player->mController;
    if (!controller)
        return;

    if (!(controller->mButtons.mFrameInput & TMarioGamePad::A))
        return;

    player->changePlayerStatus(PoundJumpState, 0, false);
}

BETTER_SMS_FOR_CALLBACK bool processPoundJump(TMario *player) {
    player->changePlayerStatus(TMario::STATE_TRIPLE_J, 0, false);
    return true;
}