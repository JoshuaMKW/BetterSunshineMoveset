#include <Dolphin/types.h>
#include <SMS/Player/Mario.hxx>

#include <SMS/raw_fn.hxx>

#include <BetterSMS/module.hxx>
#include <BetterSMS/player.hxx>

#include "player.hxx"

using namespace BetterSMS;

u32 MultiJumpState = 0xF00001C1;

BETTER_SMS_FOR_CALLBACK void checkForMultiJump(TMario *player, bool isMario) {
    auto *playerData = getPlayerMovementData(player);
    if (!playerData || !isMario)
        return;

    auto *params = getPlayerMovementParams(player);
    if (!params)
		return;

    const bool isYoshi   = player->mYoshi ? player->mYoshi->mState == TYoshi::MOUNTED : false;
    const bool isAirBorn = (player->mState & TMario::STATE_AIRBORN) && (player->mActionState & 0x4);
    const bool isInvalidState =
        (player->mState & 0x800000) || isYoshi || player->mState == TMario::STATE_SLIP_JUMP ||
        player->mState == TMario::STATE_THROWN || player->mAttributes.mIsGameOver;

    if (isInvalidState)
        return;

    if (!isAirBorn) {
        playerData->mCurJump = 1;
        return;
    }

    if (player->mFludd && player->mFludd->mIsEmitWater &&
        player->mFludd->mCurrentNozzle == TWaterGun::Hover)
        return;

    const s32 jumpsLeft = (params->mMaxJumps.get() - playerData->mCurJump);

    if ((player->mController->mButtons.mFrameInput & TMarioGamePad::EButtons::A) && jumpsLeft > 0 &&
        player->mState != TMario::STATE_WALLSLIDE && player->mState != TMario::STATE_F_KNCK_H) {
        player->changePlayerStatus(MultiJumpState, 0, false);
    }
}

BETTER_SMS_FOR_CALLBACK bool processMultiJump(TMario *player) {
    auto *playerData = getPlayerMovementData(player);
    if (!playerData)
        return true;

    auto *params = getPlayerMovementParams(player);
    if (!params)
        return true;

    const s32 jumpsLeft = (params->mMaxJumps.get() - playerData->mCurJump);

    u32 state   = player->mState;
    int voiceID = 0;
    int animID  = 0;

    if (jumpsLeft == 1) {
        state = static_cast<u32>(TMario::STATE_D_JUMP);
    } else if (jumpsLeft % 2) {
        state = static_cast<u32>(TMario::STATE_JUMP);
    } else {
        state = static_cast<u32>(TMario::STATE_D_JUMP);
    }

    const TMarioGamePad *controller = player->mController;
    const f32 stickMagnitude        = controller->mControlStick.mLengthFromNeutral;

    if (stickMagnitude > 0.1f) {
        Player::rotateRelativeToCamera(
            player, gpCamera,
            {controller->mControlStick.mStickX, controller->mControlStick.mStickY}, 1.0f);
    }

    playerData->mIsLongJumping = false;
    playerData->mCurJump += 1;

    player->mForwardSpeed *= stickMagnitude;
    player->changePlayerJumping(state, 1);

    return true;
}

static bool avoidSlipJumpOnMultiJump(TMario *player) {
    auto *playerData = getPlayerMovementData(player);
    if (!playerData)
        return player->isForceSlip();

    auto *params = getPlayerMovementParams(player);
    if (!params)
        return player->isForceSlip();

    if (playerData->mCurJump <= 1) {
        return player->isForceSlip();
    }
    return false;
}
SMS_PATCH_BL(SMS_PORT_REGION(0x80253A8C, 0, 0, 0), avoidSlipJumpOnMultiJump);

static void playDoubleOrTripleAnim(TMario *player, int state, int anim, int unk_0) {
    auto *playerData = getPlayerMovementData(player);
    if (!playerData) {
        player->jumpingBasic(state, anim, unk_0);
        return;
    }

    auto *params = getPlayerMovementParams(player);
    if (!params) {
        player->jumpingBasic(state, anim, unk_0);
        return;
    }

    size_t maxjumps = params->mMaxJumps.get();
    if (maxjumps > 1 && playerData->mCurJump >= maxjumps) {
        player->jumpingBasic(state, 0x6F, unk_0);
        if (playerData->mCurJump == maxjumps) {  // Hack
            player->startVoice(0x78B6);
            playerData->mCurJump += 1;
        }
    } else {
        player->jumpingBasic(state, anim, unk_0);
    }
}
SMS_PATCH_BL(SMS_PORT_REGION(0x80249618, 0, 0, 0), playDoubleOrTripleAnim);