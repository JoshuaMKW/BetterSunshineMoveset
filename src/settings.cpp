#include "settings.hxx"
#include <Dolphin/types.h>

LongJumpMappingSetting gLongJumpMappingSetting{};
LongJumpSetting gLongJumpSetting{};

static bool sBackFlipActive = true;
Settings::SwitchSetting gBackFlipSetting("Back Flip", &sBackFlipActive);

static bool sPoundJumpActive = true;
Settings::SwitchSetting gPoundJumpSetting("Ground Pound Jump", &sPoundJumpActive);

static bool sWaterPoundActive = true;
Settings::SwitchSetting gWaterPoundSetting("Water Ground Pound", &sWaterPoundActive);

static bool sHoverBurstActive = true;
Settings::SwitchSetting gHoverBurstSetting("Hover Burst", &sHoverBurstActive);

HoverSlideSetting gHoverSlideSetting{};

static bool sRocketDiveActive = true;
Settings::SwitchSetting gRocketDiveSetting("Rocket Dive", &sRocketDiveActive);

FastTurboSetting gFastTurboSetting{};

FastDiveSetting gFastDiveSetting{};

FallDamageSetting gFallDamageSetting{};

u32 getCrouchAndLongJumpButtonMeaning() {
    switch (gLongJumpMappingSetting.getInt()) {
    case LongJumpMappingSetting::BUTTON_Z:
    default:
        return 0x1000;
    case LongJumpMappingSetting::BUTTON_L:
        return 0x1000;
    }
}

const u8 gSaveBnr[] = {
    0x09, 0x00, 0x00, 0x60, 0x00, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0xf3, 0x00, 0x00, 0x0c, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x00, 0x00, 0x00, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x00, 0x00, 0x09, 0x1b, 0x1b, 0x1c, 0x1d, 0x1e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0d, 0x0e, 0x0e, 0x0e, 0x0f, 0x10, 0x00, 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0d, 0x11, 0x0e, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x21, 0x22, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x12, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x13, 0x11, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x14, 0x23, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0d, 0x24,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0d, 0x15, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51,
    0x26, 0x27, 0x28, 0x29, 0x07, 0x2a, 0x04, 0x2b, 0x3a, 0x3b, 0x3c, 0x3d, 0x00, 0x00, 0x3e, 0x1b,
    0x46, 0x47, 0x48, 0x3c, 0x49, 0x4a, 0x37, 0x4b, 0x47, 0x47, 0x48, 0x52, 0x53, 0x54, 0x55, 0x56,
    0x0c, 0x2c, 0x1c, 0x1d, 0x2d, 0x2d, 0x2e, 0x2f, 0x1d, 0x3f, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x40,
    0x2e, 0x4c, 0x4d, 0x4e, 0x4f, 0x0c, 0x4c, 0x50, 0x4f, 0x08, 0x57, 0x55, 0x58, 0x35, 0x59, 0x5a,
    0x30, 0x11, 0x31, 0x31, 0x32, 0x0e, 0x11, 0x0e, 0x0e, 0x31, 0x31, 0x41, 0x15, 0x21, 0x11, 0x11,
    0x1f, 0x11, 0x31, 0x22, 0x15, 0x32, 0x11, 0x31, 0x12, 0x31, 0x31, 0x0e, 0x32, 0x31, 0x11, 0x0e,
    0x15, 0x33, 0x11, 0x11, 0x31, 0x11, 0x11, 0x11, 0x42, 0x22, 0x11, 0x31, 0x0e, 0x32, 0x14, 0x0e,
    0x15, 0x22, 0x11, 0x31, 0x22, 0x15, 0x15, 0x15, 0x15, 0x33, 0x31, 0x31, 0x0e, 0x32, 0x0e, 0x0e,
    0x24, 0x12, 0x11, 0x11, 0x11, 0x31, 0x31, 0x31, 0x24, 0x33, 0x0e, 0x0e, 0x0e, 0x31, 0x31, 0x31,
    0x00, 0x00, 0x00, 0x00, 0x15, 0x0e, 0x31, 0x31, 0x42, 0x00, 0x00, 0x00, 0x15, 0x31, 0x11, 0x11,
    0x31, 0x31, 0x31, 0x31, 0x11, 0x11, 0x11, 0x31, 0x31, 0x31, 0x11, 0x11, 0x0e, 0x0e, 0x0e, 0x0e,
    0x0e, 0x0e, 0x0e, 0x0d, 0x15, 0x00, 0x00, 0x13, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
    0x31, 0x31, 0x31, 0x31, 0x31, 0x11, 0x22, 0x15, 0x31, 0x31, 0x31, 0x31, 0x11, 0x11, 0x22, 0x24,
    0x11, 0x31, 0x31, 0x0e, 0x0e, 0x0e, 0x33, 0x24, 0x11, 0x11, 0x31, 0x15, 0x00, 0x00, 0x00, 0x24,
    0x0e, 0x11, 0x31, 0x31, 0x11, 0x11, 0x22, 0x15, 0x31, 0x31, 0x31, 0x32, 0x32, 0x14, 0x33, 0x15,
    0x31, 0x11, 0x0e, 0x24, 0x15, 0x15, 0x00, 0x15, 0x11, 0x11, 0x31, 0x14, 0x14, 0x0e, 0x5b, 0x42,
    0x31, 0x31, 0x31, 0x31, 0x31, 0x11, 0x11, 0x31, 0x31, 0x11, 0x31, 0x32, 0x32, 0x31, 0x31, 0x31,
    0x31, 0x11, 0x31, 0x15, 0x15, 0x0d, 0x31, 0x0e, 0x11, 0x11, 0x31, 0x24, 0x5b, 0x31, 0x31, 0x32,
    0x34, 0x35, 0x00, 0x00, 0x00, 0x00, 0x36, 0x37, 0x0f, 0x43, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x38,
    0x34, 0x38, 0x16, 0x00, 0x00, 0x00, 0x1a, 0x43, 0x23, 0x38, 0x38, 0x5c, 0x00, 0x5c, 0x38, 0x38,
    0x38, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5e, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x6d,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x6e, 0x5f,
    0x47, 0x60, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x6e, 0x60, 0x48, 0x6f, 0x38, 0x29, 0x1f, 0x70,
    0x78, 0x48, 0x6e, 0x79, 0x7a, 0x03, 0x7b, 0x7c, 0x5f, 0x48, 0x5f, 0x83, 0x80, 0x84, 0x55, 0x65,
    0x56, 0x5a, 0x66, 0x67, 0x68, 0x3d, 0x58, 0x01, 0x71, 0x72, 0x43, 0x62, 0x5e, 0x04, 0x67, 0x73,
    0x7d, 0x67, 0x43, 0x65, 0x5e, 0x01, 0x65, 0x55, 0x85, 0x86, 0x87, 0x71, 0x59, 0x00, 0x88, 0x59,
    0x1f, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x0e, 0x30, 0x31, 0x31, 0x0e, 0x32, 0x14, 0x31, 0x31,
    0x30, 0x31, 0x31, 0x32, 0x15, 0x21, 0x31, 0x31, 0x7b, 0x31, 0x31, 0x31, 0x32, 0x14, 0x11, 0x11,
    0x24, 0x22, 0x31, 0x31, 0x31, 0x11, 0x69, 0x10, 0x14, 0x0e, 0x31, 0x31, 0x0e, 0x14, 0x0e, 0x13,
    0x31, 0x14, 0x31, 0x31, 0x22, 0x15, 0x15, 0x00, 0x0e, 0x24, 0x32, 0x11, 0x31, 0x14, 0x0e, 0x0f,
    0x00, 0x00, 0x00, 0x00, 0x15, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x15, 0x11, 0x11, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x42, 0x11, 0x11, 0x11, 0x0f, 0x42, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13,
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x11, 0x42, 0x00, 0x00, 0x00, 0x00, 0x42, 0x11,
    0x11, 0x11, 0x31, 0x15, 0x00, 0x00, 0x00, 0x24, 0x11, 0x11, 0x11, 0x15, 0x00, 0x00, 0x00, 0x24,
    0x11, 0x11, 0x11, 0x42, 0x00, 0x00, 0x00, 0x42, 0x11, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x11, 0x31, 0x11, 0x11, 0x0e, 0x00, 0x15, 0x11, 0x11, 0x31, 0x0e, 0x0e, 0x0d, 0x00, 0x00,
    0x11, 0x11, 0x31, 0x24, 0x15, 0x15, 0x00, 0x00, 0x10, 0x11, 0x11, 0x0e, 0x14, 0x0e, 0x0e, 0x5b,
    0x0e, 0x11, 0x11, 0x14, 0x0e, 0x31, 0x31, 0x5b, 0x13, 0x11, 0x11, 0x31, 0x31, 0x31, 0x31, 0x5b,
    0x24, 0x11, 0x11, 0x14, 0x31, 0x11, 0x31, 0x5b, 0x24, 0x11, 0x11, 0x24, 0x5b, 0x11, 0x31, 0x14,
    0x00, 0x6a, 0x38, 0x38, 0x05, 0x38, 0x37, 0x38, 0x00, 0x19, 0x38, 0x38, 0x38, 0x37, 0x74, 0x75,
    0x35, 0x43, 0x18, 0x7e, 0x7f, 0x37, 0x38, 0x37, 0x89, 0x43, 0x8a, 0x8b, 0x80, 0x47, 0x47, 0x43,
    0x03, 0x00, 0x00, 0x00, 0x6b, 0x43, 0x35, 0x00, 0x76, 0x25, 0x77, 0x71, 0x43, 0x47, 0x3e, 0x00,
    0x75, 0x37, 0x43, 0x47, 0x80, 0x53, 0x81, 0x00, 0x75, 0x74, 0x38, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x6e, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x94, 0x6e, 0x5f, 0x5f,
    0x00, 0x00, 0x00, 0x45, 0x5f, 0x5f, 0x9f, 0x6e, 0x00, 0x00, 0x00, 0x53, 0x5f, 0x5f, 0x9f, 0x6e,
    0x6e, 0x6e, 0x5f, 0x28, 0x28, 0x43, 0x43, 0x87, 0x6d, 0x78, 0x95, 0x47, 0x47, 0x47, 0x47, 0x96,
    0x6e, 0x95, 0x83, 0xa0, 0x47, 0x47, 0x47, 0x96, 0xa6, 0x3a, 0x28, 0x47, 0x47, 0x47, 0x47, 0xa7,
    0x8d, 0x8e, 0x09, 0x8f, 0x8f, 0x16, 0x5e, 0x00, 0x0c, 0x8e, 0x4c, 0x2a, 0x59, 0x97, 0x98, 0x07,
    0x0c, 0x8e, 0x4d, 0x23, 0xa1, 0x09, 0xa2, 0x7d, 0x50, 0x4c, 0x4c, 0xa8, 0xa9, 0x4c, 0x4d, 0x7d,
    0x90, 0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x99, 0x90, 0x11, 0x0e, 0x0e, 0x0f, 0x11, 0x0e,
    0xa0, 0x96, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x15, 0x32, 0x11, 0x11, 0x11, 0x11, 0x90, 0x24, 0x00, 0x0d, 0x11, 0x0f, 0x0e, 0x0f, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x13, 0x00, 0x00, 0x11, 0x90, 0x11, 0x90, 0x11, 0x0e, 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x13, 0x00, 0x00, 0x00, 0x00, 0x13, 0x90, 0x11, 0x13, 0x00, 0x00, 0x00, 0x00, 0x24, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x11, 0x90, 0x11, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x0f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x90, 0x11, 0x11, 0x11, 0x90, 0x69, 0x0d, 0x20, 0x11, 0x11, 0x0f, 0x0f, 0x11, 0x11, 0x0e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x23, 0x11, 0x11, 0x24, 0x00, 0x0d, 0x11, 0x0e, 0x0e, 0x11, 0x11, 0x0e, 0x00, 0x00, 0x0d, 0x9a,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35,
    0x0f, 0x54, 0x91, 0x16, 0x2a, 0x92, 0x93, 0x3c, 0x9b, 0x72, 0x06, 0x00, 0x9c, 0x4a, 0x00, 0x9d,
    0x67, 0x88, 0x74, 0x6a, 0xa4, 0xa5, 0x00, 0x47, 0x38, 0x00, 0xab, 0x75, 0x37, 0x37, 0x37, 0x38,
    0x38, 0x74, 0x7f, 0x16, 0x00, 0x00, 0x00, 0x00, 0x43, 0x9e, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x38, 0x9e, 0x37, 0x67, 0x00, 0x00, 0x00, 0x00, 0x75, 0x7f, 0x37, 0x43, 0x17, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x51, 0x5f, 0x5f, 0x5f, 0x5f, 0x00, 0x00, 0x00, 0x8c, 0x6e, 0x5f, 0x5f, 0xa6,
    0x00, 0x00, 0x07, 0x5f, 0x48, 0x48, 0x95, 0x6c, 0x00, 0x00, 0xbb, 0xbc, 0x47, 0x47, 0xbd, 0x45,
    0x6c, 0x00, 0x27, 0x47, 0x47, 0x47, 0xac, 0x56, 0x00, 0x00, 0x5e, 0x29, 0x02, 0x6f, 0x54, 0xb5,
    0x00, 0x00, 0x00, 0x00, 0xb3, 0x3d, 0x94, 0x01, 0x00, 0x00, 0x00, 0x00, 0x45, 0xba, 0xbe, 0x21,
    0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0x0c, 0x01, 0xb5, 0xad, 0x2f, 0xb6, 0x10, 0x93, 0x00, 0x00,
    0x88, 0x66, 0x0f, 0xb7, 0xb7, 0x63, 0x00, 0x00, 0x21, 0x41, 0xb8, 0xb8, 0xb8, 0xb8, 0xbf, 0xc0,
    0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x34, 0xb8, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0xc1, 0xc1, 0xb9, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xb9, 0xb8, 0x0f, 0x0f, 0xb8, 0x10, 0x00, 0x34, 0xc2, 0xc1, 0xc2, 0xc1, 0xc1, 0x34, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0d, 0x90, 0xb8, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x34, 0xc1, 0xc3, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xba, 0xb8, 0xb8, 0x90, 0x0d, 0x00, 0x42, 0x0f, 0x12, 0xc3, 0xc3, 0xc1, 0x00, 0x00, 0x13, 0xc1,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x0f, 0x0f, 0x11, 0x11, 0x34, 0x00, 0x00, 0xc1, 0xc1, 0xc1, 0xc1, 0xb8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x11, 0x0f, 0x0f, 0x7b, 0x00, 0x00, 0x00, 0x33, 0xc1, 0xb8, 0xb8, 0xb8, 0x0d, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x11, 0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x00, 0xba, 0xc1, 0xc2, 0xb8, 0xb8, 0xc1, 0xb9,
    0x43, 0xb3, 0x00, 0x36, 0xb4, 0xa4, 0x74, 0x6a, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0d, 0x0e, 0x14, 0x14, 0x32, 0x0d, 0x0d, 0x0d, 0x13, 0xc2, 0xc1, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8,
    0x7f, 0x91, 0x8b, 0x5e, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0d, 0x0d, 0x14, 0x24, 0x00, 0x00, 0x00, 0x00, 0xb8, 0xb8, 0xc1, 0x93, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x48, 0xbc, 0x47, 0x47, 0x5f, 0x00, 0x00, 0x3a, 0x47, 0xbc, 0xbc, 0xcd, 0xbb, 0x00,
    0x00, 0x53, 0x83, 0x48, 0x95, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x8c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x42, 0xbe, 0x21, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x24, 0xce,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0xce, 0x24, 0x00, 0x00, 0x00, 0x00, 0x07, 0x21, 0xce, 0xba,
    0x21, 0xc5, 0xc2, 0xb8, 0xb8, 0xb8, 0xc6, 0xc7, 0x21, 0xcb, 0xcc, 0xcb, 0xc3, 0xcf, 0xcf, 0xc3,
    0xcc, 0x6d, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0x6d, 0x6d, 0xbd, 0xbd, 0xbd, 0x6d, 0x6d,
    0xc2, 0xc2, 0xc1, 0xc8, 0x00, 0x00, 0xba, 0xc3, 0xcb, 0xcb, 0x46, 0xb7, 0x00, 0x00, 0x63, 0x48,
    0xbd, 0xbd, 0x6d, 0xcc, 0x00, 0x00, 0xd4, 0x48, 0xbd, 0xbd, 0x6d, 0x6d, 0xd4, 0x00, 0xd1, 0x6d,
    0xc3, 0xc3, 0xc2, 0xc2, 0xc2, 0xc1, 0xc2, 0x93, 0x6d, 0xbd, 0xcb, 0xc9, 0xc3, 0xcb, 0xcb, 0xc3,
    0x6d, 0xbd, 0xd0, 0x42, 0xc9, 0xcc, 0xbd, 0xbd, 0x6d, 0xbd, 0x3a, 0x00, 0xd2, 0xbd, 0xbc, 0xbc,
    0x00, 0x00, 0xc9, 0x46, 0xca, 0xb0, 0x00, 0x00, 0x13, 0x00, 0xd0, 0x6d, 0xbd, 0xd1, 0x00, 0xd2,
    0xc3, 0x45, 0xcb, 0x48, 0x48, 0xd0, 0x00, 0xbb, 0x6d, 0xd2, 0x78, 0xbc, 0xbc, 0xbd, 0x3a, 0x78,
    0xb0, 0xcb, 0xcb, 0xb7, 0x00, 0x00, 0xc3, 0xcb, 0xcb, 0x46, 0xcb, 0x42, 0x00, 0x13, 0xbd, 0xbd,
    0x48, 0xbc, 0xbd, 0x42, 0x00, 0x3a, 0xbc, 0xbc, 0xbc, 0xbc, 0x48, 0x2a, 0x00, 0x3d, 0xbc, 0x47,
    0xc3, 0xc3, 0xc3, 0xcb, 0xc3, 0x00, 0x00, 0x00, 0x46, 0xcf, 0xc9, 0xc3, 0xc9, 0x00, 0x00, 0x93,
    0x48, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x42, 0xc3, 0x47, 0xbc, 0xcc, 0xcb, 0xd1, 0x00, 0x00, 0xd7,
    0xba, 0xcb, 0xcb, 0xc3, 0xc2, 0xc3, 0xc3, 0x34, 0x46, 0x6d, 0xbd, 0xcb, 0xc9, 0xc3, 0xcb, 0xc9,
    0x48, 0xbc, 0xbc, 0xbd, 0xd2, 0xd6, 0xd1, 0x00, 0x6d, 0xbc, 0xbc, 0xbc, 0x3a, 0x45, 0xb0, 0x00,
    0x93, 0xc3, 0x46, 0xcb, 0xc3, 0xc3, 0xc3, 0xc8, 0xd3, 0x6d, 0x48, 0xbd, 0xc3, 0xc9, 0xc9, 0xb0,
    0xd7, 0x48, 0xbc, 0x48, 0xb0, 0x00, 0x00, 0x00, 0xd7, 0xbc, 0xbc, 0xbc, 0x48, 0xcc, 0xcc, 0xd5,
    0x13, 0xc3, 0xcb, 0xcb, 0xcb, 0x46, 0x46, 0xcc, 0x45, 0xc3, 0xc3, 0xcb, 0xbd, 0xbc, 0xbc, 0x48,
    0x00, 0x00, 0x00, 0x45, 0xbd, 0x47, 0x47, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x48, 0x47, 0x47, 0xbc,
    0xcb, 0xcb, 0xcb, 0x10, 0x00, 0x00, 0x00, 0x00, 0xbd, 0xbd, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x00,
    0x6d, 0x46, 0xbd, 0xba, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x45, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x49, 0x07, 0xbe, 0xd8, 0xbe, 0xcb, 0x00, 0x01, 0x65, 0x70, 0xba, 0xdb, 0xdc, 0xcc,
    0x00, 0x85, 0x18, 0xe0, 0x2b, 0xd8, 0xe1, 0xd9, 0x00, 0xa9, 0x05, 0xe8, 0x59, 0xbe, 0xe9, 0xd9,
    0xd9, 0x6d, 0x6d, 0x78, 0xc9, 0x6d, 0xd9, 0xbd, 0xd9, 0xd9, 0xbd, 0x96, 0xdd, 0x6d, 0xd9, 0xc8,
    0xd9, 0xe2, 0x78, 0xe3, 0x8f, 0x3b, 0xd4, 0xba, 0xd9, 0xde, 0xb3, 0x57, 0x57, 0xea, 0x01, 0x2a,
    0xbb, 0xcc, 0x6d, 0x6d, 0xd3, 0x00, 0xd1, 0xd9, 0x07, 0xcc, 0xd9, 0x6d, 0xd3, 0x6c, 0xcc, 0xd9,
    0x00, 0xcc, 0xd9, 0xd9, 0xd9, 0xd5, 0x00, 0xda, 0x00, 0xe7, 0xd9, 0xd9, 0xd9, 0xda, 0x00, 0x00,
    0x6d, 0x6d, 0x78, 0x00, 0x13, 0x6d, 0xbc, 0xbc, 0xd9, 0xd9, 0x6d, 0xcc, 0xcc, 0x6d, 0xd9, 0xbc,
    0xd9, 0xd9, 0xd9, 0xe4, 0xe4, 0xe4, 0xd9, 0xd9, 0xd4, 0xd9, 0xd9, 0xe2, 0xe2, 0xe2, 0xd9, 0xd9,
    0x6d, 0x45, 0x93, 0x6d, 0xbc, 0xbc, 0x6d, 0xbc, 0xd5, 0x00, 0x00, 0xbd, 0xd9, 0xd9, 0xd9, 0xd9,
    0x6c, 0x00, 0x00, 0xde, 0xd9, 0xe4, 0xe4, 0x6d, 0xd2, 0x00, 0x00, 0xde, 0xd9, 0xe4, 0xe4, 0xe2,
    0xbc, 0xbc, 0x51, 0x00, 0x00, 0xd5, 0xbc, 0xbc, 0xbc, 0xbc, 0x6c, 0x00, 0x00, 0xd7, 0xbc, 0xbc,
    0xd9, 0x6d, 0x45, 0x00, 0x00, 0x93, 0x6d, 0xd9, 0xe2, 0xd7, 0x00, 0x00, 0x00, 0x00, 0xd7, 0xd9,
    0xbc, 0xbc, 0xbc, 0xbd, 0x42, 0x00, 0x42, 0xd5, 0xbc, 0x6d, 0x6d, 0xcc, 0x00, 0x00, 0xd2, 0xde,
    0xd9, 0xd5, 0x45, 0x00, 0x00, 0x45, 0xde, 0xd9, 0xe2, 0xde, 0xe5, 0xeb, 0xde, 0xe4, 0xde, 0xe4,
    0xda, 0xbd, 0xbc, 0xbc, 0x6d, 0x78, 0x00, 0x00, 0xdf, 0x93, 0x78, 0xd9, 0xd9, 0xd9, 0xd4, 0x00,
    0xde, 0xe5, 0xde, 0x6d, 0x6d, 0xd9, 0xe4, 0xe6, 0xe2, 0xe2, 0xe4, 0xe4, 0xe2, 0xd9, 0xe7, 0x00,
    0xba, 0xbc, 0xbc, 0xbc, 0xbc, 0xbc, 0xbd, 0x53, 0x6c, 0xbc, 0xbc, 0xbc, 0x6d, 0x6d, 0x78, 0x00,
    0xd2, 0x6d, 0xd9, 0x6d, 0xbb, 0x45, 0x07, 0x00, 0x00, 0xd5, 0xd9, 0xd9, 0xde, 0xe5, 0xde, 0xe4,
    0x00, 0x00, 0x00, 0x00, 0xbd, 0xbc, 0xbc, 0xbc, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xbc, 0xbc, 0x6d,
    0x00, 0x00, 0x00, 0x00, 0xe7, 0xd9, 0xbc, 0xbd, 0xec, 0x00, 0x00, 0xd5, 0xd9, 0xd9, 0xd9, 0xd9,
    0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5e, 0xed, 0x56, 0xad, 0x2b, 0xd6, 0xe4, 0xd9, 0x5e, 0x56, 0x6a, 0xe8, 0xf1, 0x93, 0x45, 0x07,
    0x00, 0x5c, 0xe8, 0xad, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe2, 0xde, 0x07, 0xee, 0xb5, 0xea, 0x57, 0x00, 0x45, 0xf0, 0x00, 0x01, 0x85, 0x57, 0xea, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x5e, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xe2, 0xd9, 0xd9, 0xec, 0x00, 0x00, 0x00, 0x00, 0xde, 0xd9, 0xd9, 0xda, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xe7, 0xd9, 0xe2, 0xe4, 0xe4, 0xe2, 0xe6, 0x00, 0x00, 0xcc, 0xf2, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xde, 0xd9, 0xe2, 0xe2, 0xd9, 0x00, 0x00, 0x00, 0x45, 0xde, 0xe4, 0xe4, 0xe2,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe2, 0xef, 0x00, 0x00, 0x00, 0x00, 0xd2, 0xd9, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, 0xe2,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe2, 0xe2, 0xe2, 0xd9, 0xd9, 0xeb, 0x42, 0xd2, 0xe2, 0xe4, 0xe4, 0xe4, 0xe2, 0xe4, 0xda, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe4, 0xe2, 0xe2, 0xe2, 0xe2, 0xd9, 0xf0, 0x00, 0xe6, 0xe4, 0xe4, 0xe4, 0xe4, 0xe5, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xe6, 0xd9, 0xd9, 0xe2, 0xd9, 0xd9, 0xd9, 0x00, 0xe6, 0xd9, 0xe4, 0xe4, 0xe4, 0xe4, 0xd9,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe7, 0x00, 0x00, 0xd4, 0xd9, 0xd9, 0xd9, 0xd9, 0xd9, 0xbb, 0x00, 0xda, 0xd9, 0xe4, 0xe4, 0xd9,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0xa4, 0xc5, 0xe7, 0x36, 0xc5, 0xe9, 0xc1, 0xee, 0xfb, 0x52, 0xea, 0xcb, 0x88, 0x42,
    0x98, 0x00, 0xc8, 0x83, 0xdc, 0xc3, 0xd4, 0xa3, 0xa4, 0x00, 0xa9, 0x76, 0xb1, 0xba, 0xb9, 0xdb,
    0x98, 0xed, 0xb9, 0xdd, 0xa1, 0x12, 0x8c, 0x89, 0xad, 0x99, 0x80, 0x05, 0x98, 0x81, 0xeb, 0x12,
    0xff, 0xb1, 0xda, 0x49, 0xa9, 0x26, 0xf9, 0x8a, 0xfd, 0x67, 0xfd, 0x25, 0xed, 0x07, 0xb5, 0x75,
    0x90, 0xab, 0x84, 0x8c, 0xa1, 0x34, 0x90, 0xac, 0x88, 0x69, 0xb9, 0x86, 0xb1, 0xae, 0xd2, 0x95,
    0xf3, 0x9d, 0xda, 0xb2, 0x90, 0x85, 0xb9, 0x4a, 0xe4, 0xc4, 0xe4, 0x82, 0xd4, 0x41, 0xd9, 0xad,
    0xc1, 0xf9, 0xb5, 0xbc, 0xad, 0x78, 0x9d, 0x12, 0xa5, 0x52, 0xb9, 0x8a, 0xb1, 0x02, 0xff, 0xf2,
    0xff, 0xf5, 0x9c, 0xc3, 0xa5, 0x6c, 0xc6, 0x75, 0xca, 0x95, 0xb5, 0xf0, 0xca, 0x0c, 0xf8, 0xe4,
    0xd1, 0x09, 0x99, 0x34, 0x84, 0x46, 0xff, 0xfa, 0xde, 0x8b, 0x88, 0x86, 0xd3, 0x3f, 0xfb, 0xff,
    0xe3, 0xbe, 0xa5, 0x29, 0xde, 0xcb, 0xf5, 0x68, 0xb8, 0x01, 0xc8, 0x42, 0xed, 0xaa, 0xd9, 0x68,
    0xb8, 0x42, 0xb6, 0x11, 0xba, 0x0f, 0x94, 0xc6, 0xca, 0x30, 0xfb, 0x15, 0xfe, 0xae, 0xc1, 0x24,
    0xda, 0x0d, 0xb9, 0x27, 0xa4, 0x41, 0x98, 0xf1, 0xa4, 0xc1, 0xb1, 0x44, 0x94, 0x61, 0xd7, 0x39,
    0xeb, 0xbb, 0xeb, 0x57, 0xe6, 0xd1, 0xb5, 0xd5, 0xc9, 0xd7, 0xfa, 0xd2, 0xc9, 0x47, 0xfb, 0x56,
    0xb1, 0x28, 0xc1, 0xff, 0xfb, 0x2e, 0xce, 0x0a, 0x99, 0x0a, 0xdb, 0x9f, 0xdb, 0x5a, 0xe7, 0x5a,
    0xea, 0x71, 0xfb, 0x12, 0xda, 0x0a, 0xf2, 0xf4, 0xff, 0x8e, 0xff, 0xcf, 0xe6, 0xec, 0xda, 0xcf,
    0xca, 0xda, 0xca, 0x4f, 0xce, 0x27, 0xb5, 0xb6, 0xd5, 0xcf, 0xea, 0x2d, 0xea, 0x87, 0xff, 0x0a,
    0xda, 0x8f, 0xad, 0x03, 0x9d, 0x4a, 0xd6, 0xd6, 0xe2, 0x90, 0xd5, 0xa8, 0xe1, 0x68, 0xf6, 0xb0,
    0xa4, 0x82, 0xd6, 0xbb, 0xf6, 0xa9, 0xd6, 0x06, 0xce, 0xd7, 0xc4, 0xc4, 0xc0, 0x00, 0xcd, 0xa9,
    0xc2, 0x1f, 0xf6, 0xc9, 0xf7, 0xb6, 0x90, 0xca, 0xb5, 0xcf, 0xd6, 0xf9, 0xda, 0x51, 0xbc, 0xe6,
    0xac, 0xa4, 0xd2, 0x9e, 0xc2, 0x18, 0xfb, 0x98, 0xa9, 0x46, 0xc2, 0x14, 0xff, 0x4a, 0xcf, 0x18,
    0xf7, 0x59, 0xa0, 0x44, 0xd8, 0xa4, 0xa0, 0xe9, 0xf7, 0x6f, 0xbd, 0xc6, 0xba, 0x53, 0xe6, 0xd5,
    0xc1, 0xf2, 0xea, 0x4b, 0xea, 0x6f, 0xbd, 0x83, 0xef, 0x38, 0xe5, 0xe9, 0xa4, 0xaa, 0x88, 0xb0,
    0xa5, 0x92, 0xda, 0x4d, 0x98, 0x45, 0xa9, 0x49, 0xe2, 0x8a, 0xd5, 0x87, 0xb5, 0x4e, 0xba, 0x1a,
    0xba, 0x3d, 0xa9, 0x95, 0x99, 0x0d, 0xa5, 0x8e, 0xeb, 0xff, 0xd7, 0x5f, 0x88, 0xce, 0x8d, 0x34,
    0x99, 0x53, 0xc2, 0x7f, 0xbe, 0x5e, 0xc6, 0x9e, 0x80, 0x6c, 0xad, 0xfa, 0x8d, 0x55, 0x9d, 0x98,
    0xa9, 0xd5, 0xba, 0x5a, 0xd2, 0xff, 0xca, 0xdf, 0xcb, 0x1d, 0xe3, 0x7d, 0x80, 0x29, 0xbe, 0x9d,
    0xc2, 0x9a, 0xb6, 0x36, 0x8c, 0xe9, 0xbe, 0x9a, 0xb6, 0x56, 0xa9, 0xd1, 0xae, 0x16, 0x99, 0x4c,
    0x84, 0xf1, 0xd7, 0xff, 0xaa, 0x13, 0x84, 0xd4, 0x8d, 0x33, 0xce, 0x73, 0xc7, 0x7f, 0x9d, 0xd1,
    0xfe, 0xcd, 0xae, 0x9b, 0xcf, 0xdf, 0xd1, 0xca, 0xcb, 0xbf, 0xbf, 0x1c, 0x99, 0xaf, 0xba, 0xfa,
    0xee, 0x2a, 0xb6, 0xfd, 0xb0, 0xc3, 0xbf, 0x5d, 0xae, 0x54, 0xf2, 0x4b, 0xc9, 0x87, 0x88, 0xc7,
    0xb6, 0x97, 0xc1, 0x69, 0xbb, 0x1b};

const u8 gSaveIcon[] = {
    0x09, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x08, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00, 0x03, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x0a, 0x0b, 0x0b, 0x00, 0x00, 0x00, 0x0a, 0x13, 0x13, 0x14, 0x15,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x17, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x00, 0x2f,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x46, 0x47, 0x47, 0x47, 0x48, 0x49, 0x1b, 0x4a,
    0x21, 0x22, 0x23, 0x14, 0x15, 0x24, 0x24, 0x25, 0x30, 0x14, 0x15, 0x25, 0x25, 0x31, 0x25, 0x31,
    0x3d, 0x25, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52,
    0x26, 0x27, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x33, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x44, 0x43, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x4d, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x36,
    0x38, 0x47, 0x47, 0x47, 0x55, 0x56, 0x57, 0x58, 0x36, 0x63, 0x47, 0x47, 0x64, 0x3c, 0x65, 0x66,
    0x38, 0x6e, 0x47, 0x37, 0x6f, 0x70, 0x05, 0x71, 0x38, 0x63, 0x37, 0x1c, 0x7a, 0x65, 0x65, 0x76,
    0x59, 0x5a, 0x5b, 0x5c, 0x4f, 0x52, 0x5d, 0x50, 0x67, 0x68, 0x69, 0x6a, 0x68, 0x6b, 0x05, 0x4f,
    0x72, 0x73, 0x02, 0x6a, 0x4a, 0x74, 0x75, 0x5a, 0x4a, 0x7b, 0x41, 0x5a, 0x4a, 0x52, 0x6b, 0x5b,
    0x5e, 0x5f, 0x60, 0x61, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x1d, 0x47, 0x6c, 0x00, 0x00, 0x00, 0x00,
    0x68, 0x69, 0x76, 0x77, 0x78, 0x00, 0x00, 0x00, 0x75, 0x5c, 0x7c, 0x7c, 0x7d, 0x7e, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x6d, 0x38, 0x00, 0x00, 0x00, 0x00, 0x88, 0x89, 0x38, 0x38,
    0x00, 0x00, 0x00, 0x00, 0x7f, 0x6d, 0x38, 0x63, 0x00, 0x00, 0x00, 0x00, 0x92, 0x36, 0x38, 0x93,
    0x36, 0x38, 0x38, 0x1c, 0x47, 0x47, 0x47, 0x6a, 0x63, 0x38, 0x6e, 0x7a, 0x47, 0x47, 0x47, 0x47,
    0x63, 0x38, 0x6e, 0x7c, 0x77, 0x47, 0x47, 0x47, 0x37, 0x37, 0x89, 0x77, 0x47, 0x47, 0x47, 0x47,
    0x5a, 0x80, 0x81, 0x82, 0x83, 0x5c, 0x84, 0x74, 0x8a, 0x3e, 0x81, 0x44, 0x84, 0x4e, 0x75, 0x8b,
    0x1b, 0x4d, 0x81, 0x25, 0x8e, 0x8f, 0x3f, 0x16, 0x4a, 0x94, 0x81, 0x3e, 0x2d, 0x69, 0x3e, 0x44,
    0x85, 0x86, 0x47, 0x7c, 0x87, 0x00, 0x00, 0x00, 0x8c, 0x47, 0x47, 0x8d, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x4a, 0x50, 0x91, 0x00, 0x00, 0x00, 0x00, 0x95, 0x50, 0x75, 0x96, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x6d, 0x63, 0x6e, 0x63, 0x00, 0x00, 0x00, 0xa1, 0x38, 0x63, 0x6e, 0x38,
    0x00, 0x00, 0xa9, 0x63, 0x63, 0x63, 0x37, 0x38, 0x00, 0x00, 0x00, 0xb2, 0x38, 0x47, 0x47, 0x38,
    0x38, 0x38, 0x97, 0x98, 0x47, 0x47, 0x47, 0x86, 0x38, 0x38, 0x00, 0xa2, 0x6f, 0xa3, 0x7a, 0xa4,
    0x38, 0xaa, 0x00, 0x00, 0xab, 0xac, 0xad, 0xae, 0x6d, 0x00, 0x00, 0x00, 0x00, 0xb3, 0x8e, 0xb4,
    0x5a, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x6b, 0x4d, 0x4c, 0x7b, 0x7b, 0xa5, 0xa6, 0xa7, 0x8e, 0xa8,
    0xaf, 0xb0, 0xb1, 0x41, 0x4c, 0x5f, 0xad, 0x00, 0xb4, 0x9b, 0xb5, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6,
    0x9e, 0x9f, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb8, 0x37, 0x38, 0x47, 0x37, 0x38, 0x00, 0x00, 0xbb, 0x37, 0x38, 0x37, 0x38, 0x38,
    0x00, 0x00, 0xc1, 0xc2, 0x47, 0xc3, 0xc1, 0x00, 0x00, 0x00, 0x00, 0xb8, 0xc2, 0xc7, 0x00, 0x00,
    0xb2, 0x00, 0x00, 0x00, 0x00, 0xb9, 0xb4, 0xba, 0x79, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbd, 0xba,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xc9, 0xba,
    0xba, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0xba, 0xba, 0xba, 0xba, 0xbe, 0xbf, 0xba, 0xba,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xba, 0xc5, 0x9b, 0xbf, 0xca, 0xcb, 0xcc, 0xc9, 0x9b, 0xb5, 0xb5,
    0xb5, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9b, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xbb, 0xce, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb8, 0xcf, 0xd0, 0xd1, 0xb5, 0x9b, 0x00, 0x00, 0xd5, 0x5a, 0x95, 0xd6, 0xb5, 0xd7,
    0x00, 0x00, 0xd9, 0xda, 0xdb, 0x60, 0xd7, 0x9b, 0x00, 0xe1, 0xe2, 0xda, 0xe3, 0x75, 0xba, 0xba,
    0xba, 0xbf, 0x2c, 0xa4, 0xd2, 0xd3, 0xb5, 0x9b, 0xba, 0xba, 0xd8, 0x83, 0x69, 0xa5, 0x8e, 0xc5,
    0xba, 0xdc, 0x00, 0xdd, 0xde, 0x4c, 0x75, 0xdf, 0x8e, 0xdc, 0x00, 0xe4, 0xe5, 0x4e, 0xb0, 0xaf,
    0xba, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xe6, 0xe7, 0xe8, 0x7b, 0x75, 0xdf, 0xe9, 0x00, 0xeb, 0xec, 0xec, 0x7b, 0x75, 0xed, 0xee,
    0x00, 0x00, 0xf0, 0xec, 0x7b, 0xf1, 0xf2, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xf7, 0x00, 0x00, 0x00,
    0xdc, 0x00, 0x00, 0xc1, 0xea, 0xe5, 0xb0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xef, 0x4c, 0xb0, 0xb0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xf4, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00, 0xf8, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x09, 0x0a, 0x0b, 0x0b, 0x00, 0x00, 0x00, 0x0a, 0x13, 0x13, 0x14, 0x15,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x17, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x00, 0x2f,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x46, 0x47, 0x47, 0x37, 0x48, 0x49, 0x1b, 0x4a,
    0x21, 0x22, 0x23, 0x14, 0x15, 0x24, 0x24, 0x25, 0x30, 0x14, 0x15, 0x25, 0x25, 0x31, 0x25, 0x31,
    0x3d, 0x25, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52,
    0x26, 0x27, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x33, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x44, 0x43, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x4d, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x6e,
    0xc3, 0x47, 0x47, 0x47, 0x55, 0x56, 0x57, 0x58, 0x36, 0x37, 0x47, 0x37, 0x38, 0x3c, 0x65, 0x66,
    0x37, 0x38, 0x37, 0x64, 0x6f, 0x70, 0x05, 0x71, 0x37, 0x38, 0x38, 0x6d, 0x7a, 0x65, 0x65, 0x76,
    0x59, 0x5a, 0x5b, 0x5c, 0x4f, 0x52, 0x5d, 0x50, 0x67, 0x68, 0x69, 0x6a, 0x68, 0x6b, 0x05, 0x4f,
    0x72, 0x73, 0x02, 0x6a, 0x4a, 0x74, 0x75, 0x5a, 0x4a, 0x7b, 0x41, 0x5a, 0x4a, 0x52, 0x6b, 0x5b,
    0x5e, 0x5f, 0x60, 0x61, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x1d, 0x47, 0x6c, 0x00, 0x00, 0x00, 0x00,
    0x68, 0x69, 0x76, 0x77, 0x78, 0x00, 0x00, 0x00, 0x75, 0x5c, 0x7c, 0x7c, 0x7d, 0x7e, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0x38, 0x63, 0x00, 0x00, 0x00, 0x00, 0x54, 0x63, 0x6e, 0x63,
    0x00, 0x00, 0x00, 0x00, 0x6e, 0x63, 0x6e, 0xfa, 0x00, 0x00, 0x00, 0xa1, 0x6e, 0x36, 0x38, 0xfa,
    0x6e, 0x37, 0x37, 0x1c, 0x47, 0x47, 0x47, 0x6a, 0x6e, 0x47, 0x37, 0x7a, 0x47, 0x47, 0x47, 0x47,
    0x6d, 0x47, 0x1c, 0x7c, 0x77, 0x47, 0x47, 0x47, 0x37, 0x37, 0xfb, 0x77, 0x47, 0x47, 0x47, 0x47,
    0x5a, 0x80, 0x81, 0x82, 0x83, 0x5c, 0x84, 0x74, 0x8a, 0x3e, 0x81, 0x44, 0x84, 0x4e, 0x75, 0x8b,
    0x1b, 0x4d, 0x81, 0x25, 0x8e, 0x8f, 0x3f, 0x16, 0x4a, 0x94, 0x81, 0x3e, 0x2d, 0x69, 0x3e, 0x44,
    0x85, 0x86, 0x47, 0x7c, 0x87, 0x00, 0x00, 0x00, 0x8c, 0x47, 0x47, 0x8d, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x4a, 0x50, 0x91, 0x00, 0x00, 0x00, 0x00, 0x95, 0x50, 0x75, 0x96, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xfc, 0x6e, 0x6e, 0x38, 0x38, 0x6e, 0x00, 0x00, 0xfb, 0xfa, 0x6d, 0x38, 0x63, 0x63,
    0x00, 0x00, 0xb2, 0xf9, 0x38, 0x37, 0x38, 0x7a, 0x00, 0x79, 0x6e, 0x6e, 0x37, 0x47, 0x47, 0x38,
    0x47, 0x37, 0xfd, 0x98, 0x47, 0x47, 0x47, 0x86, 0x47, 0x1c, 0xbb, 0xa2, 0x6f, 0xa3, 0x7a, 0xa4,
    0x36, 0xfe, 0xc1, 0x00, 0xab, 0xac, 0xad, 0xae, 0x63, 0xfd, 0x00, 0x00, 0x00, 0xb3, 0x8e, 0xb4,
    0x5a, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x6b, 0x4d, 0x4c, 0x7b, 0x7b, 0xa5, 0xa6, 0xa7, 0x8e, 0xa8,
    0xaf, 0xb0, 0xb1, 0x41, 0x4c, 0x5f, 0xad, 0x00, 0xb4, 0x9b, 0xb5, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6,
    0x9e, 0x9f, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xfb, 0x63, 0x38, 0x38, 0x47, 0x37, 0x38, 0x00, 0xaa, 0x47, 0x47, 0x38, 0x37, 0x38, 0x36,
    0x00, 0x00, 0xcf, 0x56, 0x47, 0xc3, 0xce, 0x63, 0x00, 0x00, 0x00, 0xb8, 0xc2, 0xc7, 0x00, 0xfc,
    0x6e, 0xc1, 0x00, 0x00, 0x00, 0xb9, 0xb4, 0xba, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbd, 0xba,
    0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xc9, 0xba,
    0xba, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0xba, 0xba, 0xba, 0xba, 0xbe, 0xbf, 0xba, 0xba,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xba, 0xc5, 0x9b, 0xbf, 0xca, 0xcb, 0xcc, 0xc9, 0x9b, 0xb5, 0xb5,
    0xb5, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9b, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xce, 0xce, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb8, 0xcf, 0xd0, 0xd1, 0xb5, 0x9b, 0x00, 0x00, 0xd5, 0x5a, 0x95, 0xd6, 0xb5, 0xd7,
    0x00, 0x00, 0xd9, 0xda, 0xdb, 0x60, 0xd7, 0x9b, 0x00, 0xe1, 0xe2, 0xda, 0xe3, 0x75, 0xba, 0xba,
    0xba, 0xbf, 0x2c, 0xa4, 0xd2, 0xd3, 0xb5, 0x9b, 0xba, 0xba, 0xd8, 0x83, 0x69, 0xa5, 0x8e, 0xc5,
    0xba, 0xdc, 0x00, 0xdd, 0xde, 0x4c, 0x75, 0xdf, 0x8e, 0xdc, 0x00, 0xe4, 0xe5, 0x4e, 0xb0, 0xaf,
    0xba, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xe6, 0xe7, 0xe8, 0x7b, 0x75, 0xdf, 0xe9, 0x00, 0xeb, 0xec, 0xec, 0x7b, 0x75, 0xed, 0xee,
    0x00, 0x00, 0xf0, 0xec, 0x7b, 0xf1, 0xf2, 0x00, 0x00, 0x00, 0x00, 0xeb, 0xff, 0x00, 0x00, 0x00,
    0xdc, 0x00, 0x00, 0xc1, 0xea, 0xe5, 0xb0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xef, 0x4c, 0xb0, 0xb0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xf4, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3a, 0x99, 0x7f, 0xeb, 0x3e, 0xe8, 0x0e, 0xd7, 0x79, 0x87, 0xde, 0xae, 0x7d, 0xc5,
    0x1e, 0xc4, 0x1f, 0x42, 0x4f, 0x43, 0x5f, 0x42, 0x3f, 0x31, 0x0a, 0x10, 0x7e, 0xe9, 0xf7, 0x6e,
    0xd2, 0x26, 0x48, 0x75, 0x0b, 0xbc, 0xfd, 0x47, 0xfd, 0x05, 0xf8, 0xe4, 0x7c, 0x32, 0x6a, 0x33,
    0x07, 0x11, 0x09, 0x9a, 0x59, 0x9a, 0x7a, 0xaa, 0xe7, 0x7c, 0x6f, 0xec, 0x27, 0x74, 0x46, 0x55,
    0x6a, 0x99, 0x4d, 0xab, 0x3f, 0x43, 0x6f, 0x42, 0xe4, 0xa2, 0xd8, 0x62, 0xe1, 0xad, 0xea, 0x31,
    0x39, 0x43, 0x04, 0x68, 0x66, 0x78, 0xbe, 0x54, 0xc6, 0x76, 0x78, 0x89, 0x27, 0x67, 0x6c, 0xb8,
    0xe9, 0x6a, 0xd8, 0x82, 0xd9, 0x28, 0xd5, 0x8c, 0x47, 0x33, 0x19, 0xdf, 0x7b, 0xee, 0x7d, 0xff,
    0x7c, 0xee, 0x7a, 0xbc, 0x67, 0x66, 0x6e, 0xe7, 0xff, 0xf4, 0xf5, 0x88, 0xb8, 0x01, 0xc8, 0x83,
    0xf1, 0xcb, 0xe5, 0xa9, 0xac, 0x42, 0xbc, 0x63, 0xc4, 0x42, 0x46, 0x11, 0x4b, 0xef, 0x7f, 0xff,
    0x5d, 0xed, 0x3a, 0xa7, 0xfb, 0x35, 0xfa, 0xb0, 0xd9, 0xa9, 0x74, 0x00, 0xc9, 0x47, 0xff, 0x76,
    0xda, 0x2e, 0xbd, 0xac, 0xb9, 0x48, 0x64, 0x00, 0x0a, 0xdd, 0x6f, 0xfe, 0x5f, 0xfd, 0x78, 0x8c,
    0xd2, 0x19, 0xfe, 0xf4, 0xfe, 0xf1, 0xa8, 0x81, 0xcd, 0xaa, 0xbe, 0x12, 0x67, 0x54, 0x78, 0x55,
    0xc1, 0x8c, 0x28, 0x66, 0x3b, 0xee, 0x7b, 0xdd, 0xe7, 0x9b, 0xe6, 0xf2, 0xbd, 0xb7, 0xf6, 0xb5,
    0xfb, 0x13, 0xea, 0x4d, 0xff, 0xf9, 0x94, 0x43, 0x5f, 0xff, 0x7b, 0xde, 0x7a, 0xcc, 0xd2, 0x91,
    0xd6, 0x69, 0xc5, 0xf7, 0xde, 0x31, 0xf6, 0x6e, 0x72, 0x11, 0x77, 0x43, 0xfb, 0x79, 0xf7, 0xbd,
    0x3a, 0xaa, 0x3a, 0xcd, 0xe7, 0x5a, 0xe5, 0xe9, 0xe7, 0x18, 0x5b, 0xbb, 0x0b, 0xbb, 0x19, 0xbc,
    0xc5, 0x05, 0xc4, 0x20, 0xc8, 0xc5, 0x7a, 0x75, 0xa0, 0xa5, 0x25, 0x32, 0x7e, 0xed, 0x2b, 0xbb,
    0x0a, 0xcc, 0x5a, 0xbc, 0xe6, 0x92, 0x59, 0x44, 0x0e, 0xcb, 0x6b, 0xbb, 0x72, 0x37, 0xa0, 0x65,
    0x6f, 0xb9, 0x39, 0x87, 0x29, 0xbb, 0xce, 0xf8, 0xbc, 0x83, 0xe6, 0x0d, 0x05, 0x32, 0x3a, 0xbc,
    0x6d, 0xde, 0xf2, 0x2c, 0xa8, 0xcb, 0x88, 0xf2, 0xa5, 0xb4, 0xde, 0x6e, 0x68, 0x43, 0x48, 0x54,
    0x17, 0x43, 0x6b, 0xdd, 0x1b, 0xa7, 0xe3, 0x17, 0xda, 0x71, 0xdd, 0xec, 0xbd, 0x6d, 0x98, 0xcb,
    0x06, 0x33, 0x08, 0xbb, 0x3c, 0xee, 0x0b, 0xa5, 0x67, 0x76, 0x77, 0x78, 0xc1, 0xf0, 0xac, 0xe6,
    0x76, 0x31, 0xdd, 0x66, 0x4b, 0xdd, 0x35, 0x79, 0x88, 0xcf, 0x91, 0x35, 0x73, 0x5b, 0x32, 0x4b,
    0x0e, 0xff, 0x25, 0x6a, 0x70, 0x26, 0x2d, 0xee, 0x07, 0x9c, 0x61, 0x27, 0x84, 0x6c, 0x80, 0x69,
    0x42, 0x4a, 0x1e, 0xee, 0x6d, 0xff, 0x6c, 0xee, 0x51, 0x37, 0x88, 0xb0, 0x31, 0x39, 0x6b, 0xde,
    0x0c, 0xef, 0x72, 0x48, 0x80, 0x07, 0x8c, 0xcb, 0xc2, 0x14, 0x10, 0x27, 0x2c, 0xef, 0x2e, 0xff,
    0x1c, 0xbb, 0x44, 0x6b, 0xb9, 0x28, 0x99, 0x0f, 0x00, 0x15, 0x2f, 0xda, 0xa1, 0x30, 0x8d, 0x13,
    0x6a, 0xaa, 0x4f, 0xc7, 0xff, 0x2f, 0xfe, 0xcd, 0x03, 0x47, 0x5b, 0x85, 0xe2, 0x2b, 0x88, 0x8b,
    0x55, 0x69, 0x0f, 0x95, 0x6f, 0xb7, 0xf2, 0x2a, 0x3d, 0xa8, 0xd1, 0xa7, 0x1f, 0x95, 0x7f, 0x95,
    0xfe, 0x8b, 0x60, 0x15, 0xcd, 0xa7, 0x1f, 0xa6, 0xfe, 0xac, 0x61, 0x24, 0x00, 0x26, 0x4a, 0x75,
    0x3f, 0xa6, 0x66, 0x32, 0x05, 0x21, 0x2a, 0x64, 0x46, 0x31, 0x15, 0x20, 0x1f, 0xa5, 0x2d, 0x74,
    0x1c, 0xc9, 0x6a, 0xcc, 0xcf, 0x18, 0x5a, 0xcc, 0x2a, 0xcc, 0x3b, 0xcc, 0x6a, 0xbc, 0x2d, 0x84};