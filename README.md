# BetterSunshineModule
Template repository for making modules using Better Sunshine Engine

## Structure
`include/` This is where public header files go.

`lib/` This is where submodules and libraries go.

`src/` This is where source files and private header files go.

## Including SMS files
Super Mario Sunshine, Dolphin, JSystem, and BetterSunshineEngine headers can be included like so:

```c++
#include <SMS/...>
#include <Dolphin/...>
#include <JSystem/...>
#include <BetterSMS/...>
```

## Portability
You can port code to different regions using the macro `SMS_PORT_REGION(us, eu, jp, kr)`, which can be included using `#include <SMS/macros.h>`. This is commonly useful for porting addresses when patching.

## Patching

### Low Level
BetterSunshineEngine provides utilities to patch arbitary memory and code through Kuribo. The following macros are provided:

```c++
#include <BetterSMS/module.hxx>

SMS_PATCH_B(address, function);  // Branches to the specified function at the address
SMS_PATCH_BL(address, function);  // Calls the specified function at the address
SMS_WRITE_32(address, value);  // Writes the specified value at the address
```

These are the fundamental patching methods for low level module construction.

### High Level
BetterSunshineEngine provides utilities to hook into different points of the game generically. These are very useful for non-volatility and multi-module support. Examples shown below:

```c++
#include <Dolphin/OS.h>
#include <JSystem/J2D/J2DOrthoGraph.hxx>
#include <JSystem/J2D/J2DTextBox.hxx>

#include <SMS/System/Application.hxx>

#include <BetterSMS/game.hxx>
#include <BetterSMS/module.hxx>
#include <BetterSMS/stage.hxx>

/*
/ Example module that logs to the console and draws to the screen during gameplay
*/

static void onGameInit(TApplication *app) { OSReport("Game initialized!\n"); }

static void onGameBoot(TApplication *app) { OSReport("Game booted!\n"); }

static J2DTextBox *sOurTextBox = nullptr;

static void onStageInit(TMarDirector *director) {
    sOurTextBox = new J2DTextBox(gpSystemFont->mFont, "Hello Screen!");
    OSReport("Textbox initialization successful!\n");
}

static void onStageUpdate(TMarDirector *director) { OSReport("Hello world!\n"); }

static void onStageDraw2D(TMarDirector *director, const J2DOrthoGraph *ortho) {
    sOurTextBox->draw(180, 140);  // Draw text to the screen at x=180, y=140
}

// Module definition

static void initModule() {
    OSReport("Initializing Module...\n");

    // Register callbacks
    BetterSMS::Game::registerOnInitCallback("OurModule_GameInitCallBack", onGameInit);
    BetterSMS::Game::registerOnBootCallback("OurModule_GameBootCallBack", onGameBoot);
    BetterSMS::Stage::registerInitCallback("OurModule_StageInitCallBack", onStageInit);
    BetterSMS::Stage::registerUpdateCallback("OurModule_StageUpdateCallBack", onStageUpdate);
    BetterSMS::Stage::registerDraw2DCallback("OurModule_StageDraw2DCallBack", onStageDraw2D);
}

static void deinitModule() {
    OSReport("Deinitializing Module...\n");

    // Cleanup callbacks
    BetterSMS::Game::deregisterOnInitCallback("OurModule_GameInitCallBack");
    BetterSMS::Game::deregisterOnBootCallback("OurModule_GameBootCallBack");
    BetterSMS::Stage::deregisterInitCallback("OurModule_StageInitCallBack");
    BetterSMS::Stage::deregisterUpdateCallback("OurModule_StageUpdateCallBack");
    BetterSMS::Stage::deregisterDraw2DCallback("OurModule_StageDraw2DCallBack");
}

// Definition block
KURIBO_MODULE_BEGIN("OurModule", "JoshuaMK", "v1.0") {
    // Set the load and unload callbacks to our registration functions
    KURIBO_EXECUTE_ON_LOAD { initModule(); }
    KURIBO_EXECUTE_ON_UNLOAD { deinitModule(); }
}
KURIBO_MODULE_END()
```

The benefit of designing your module this way is generalization, ease of patching, and the ability to mix your module with other modules more easily!

## Compiling

Simply build the CMake project using your favorite tool (Visual Studio is recommended).

## Usage

Place the compiled module in the directory `/files/Kuribo!/Mods/` of your extracted ISO. Make sure it is ordered after BetterSunshineEngine.kxe (Easiest way is to add an underscore at the start of the module filename).