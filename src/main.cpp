#include <Dolphin/OS.h>
#include <JSystem/J2D/J2DOrthoGraph.hxx>
#include <JSystem/J2D/J2DTextBox.hxx>

#include <SMS/System/Application.hxx>

#include <BetterSMS/game.hxx>
#include <BetterSMS/module.hxx>
#include <BetterSMS/player.hxx>
#include <BetterSMS/stage.hxx>

#include "common.hxx"

extern void initFastTurbo(TMario *, bool);
extern void updateTurboContext(TMario *, bool);

extern void checkSpamHover(TMario *, bool);
extern void checkRocketNozzleDiveBlast(TMario *, bool);

extern u32 CrouchState;
extern void checkForCrouch(TMario *, bool);
extern bool processCrouch(TMario *);

// Module definition

using namespace BetterSMS;

static BetterSMS::ModuleInfo sModuleInfo("Better Sunshine Moveset", 1, 0, &gSettingsGroup);

static void initModule() {
    // Register settings
    gSettingsGroup.addSetting(&gLongJumpMappingSetting);
    gSettingsGroup.addSetting(&gLongJumpSetting);
    gSettingsGroup.addSetting(&gBackFlipSetting);
    gSettingsGroup.addSetting(&gHoverBurstSetting);
    gSettingsGroup.addSetting(&gHoverSlideSetting);
    gSettingsGroup.addSetting(&gRocketDiveSetting);
    gSettingsGroup.addSetting(&gFastTurboSetting);
    gSettingsGroup.addSetting(&gFastDiveSetting);
    {
        auto &saveInfo        = gSettingsGroup.getSaveInfo();
        saveInfo.mSaveName    = Settings::getGroupName(gSettingsGroup);
        saveInfo.mBlocks      = 1;
        saveInfo.mGameCode    = 'GMSB';
        saveInfo.mCompany     = 0x3031;  // '01'
        saveInfo.mBannerFmt   = CARD_BANNER_CI;
        saveInfo.mBannerImage = reinterpret_cast<const ResTIMG *>(gSaveBnr);
        saveInfo.mIconFmt     = CARD_ICON_CI;
        saveInfo.mIconSpeed   = CARD_SPEED_FAST;
        saveInfo.mIconCount   = 2;
        saveInfo.mIconTable   = reinterpret_cast<const ResTIMG *>(gSaveIcon);
        saveInfo.mSaveGlobal  = false;
    }

    // Register module
    BetterSMS::registerModule(&sModuleInfo);

    Player::registerInitCallback("_moveset_init_fast_turbo", initFastTurbo);
    Player::registerUpdateCallback("_moveset_update_turbo_usage", updateTurboContext);
    Player::registerUpdateCallback("_moveset_update_hover_burst", checkSpamHover);
    Player::registerUpdateCallback("_moveset_update_rocket_dive", checkRocketNozzleDiveBlast);
    Player::registerUpdateCallback("_moveset_update_crouch", checkForCrouch);
    Player::registerStateMachine(CrouchState, processCrouch);
}

static void deinitModule() {
    Player::deregisterInitCallback("_moveset_init_fast_turbo");
    Player::deregisterUpdateCallback("_moveset_update_turbo_usage");
    Player::deregisterUpdateCallback("_moveset_update_hover_burst");
    Player::deregisterUpdateCallback("_moveset_update_rocket_dive");
    Player::deregisterUpdateCallback("_moveset_update_crouch");
    Player::deregisterStateMachine(CrouchState);

    BetterSMS::deregisterModule(&sModuleInfo);
}

// Definition block
KURIBO_MODULE_BEGIN("OurModule", "JoshuaMK", "v1.0") {
    // Set the load and unload callbacks to our registration functions
    KURIBO_EXECUTE_ON_LOAD { initModule(); }
    KURIBO_EXECUTE_ON_UNLOAD { deinitModule(); }
}
KURIBO_MODULE_END()

// Map on D Pad down
SMS_WRITE_32(SMS_PORT_REGION(0x8017A830, 0x801706F4, 0, 0), 0x5400077B);
SMS_WRITE_32(SMS_PORT_REGION(0x80297A60, 0x8028F8F8, 0, 0), 0x5400077B);
