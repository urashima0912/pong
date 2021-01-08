#include "app.h"
#include "config.h"
#include "global.h"
#include <stdlib.h>

// declaration static functions.
static bool finished = false;
static bool showFPS = false;

static void settingApp(void);
static void updateFullScreen(void);
static void updateApp(App *const app);
static void drawApp(const App *const app);
static void freeInternalApp(App *app);
static void updateTheme(void);
static void drawFPS(void);
static void getEvent(void);

Global globalData = { 0 };

// implementation public functions.
App *initApp(void) {
  finished = false;
  App *app = malloc(sizeof(App));
  if (app == NULL) {
    return NULL;
  }
  settingApp();
  initGlobal(&globalData);
  app->sceneHandler = initSceneHandler();
  return app;
}

void runApp(App *const app) {
  while (!WindowShouldClose() && !finished) {
    updateApp(app);
    drawApp(app);
  }
}

void freeApp(App **app) {
  if (*app != NULL) {
    freeGlobal(&globalData);
    freeInternalApp(*app);
    free(*app);
    *app = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_APP_DELETED);
    #endif
  }
}


// implementation static functions.
static void settingApp(void) {
  InitWindow(PONG_SCREEN_WIDTH, PONG_SCREEN_HEIGHT, PONG_SCREEN_TITLE);
  HideCursor();
  SetExitKey(KEY_F8);
  SetTargetFPS(60);
  InitAudioDevice();
}

static void updateApp(App *const app) {
  updateTheme();
  updateFullScreen();
  updateSceneHandler(app->sceneHandler);
  getEvent();
  finished = finishSceneHanlder();
}

static void drawApp(const App *const app) {
  BeginDrawing();
  ClearBackground(globalData.colors.color0);
  drawSceneHandler(app->sceneHandler);
  drawFPS();
  EndDrawing();
}

static void freeInternalApp(App *const app) {
  freeScenehandler(&app->sceneHandler);
  CloseAudioDevice();
  CloseWindow();
}

static void updateTheme(void) {
  static GlTheme theme = -1;
  if (theme != globalData.theme) {
    theme = globalData.theme;
    switch (theme) {
      case THEME_POCKET_GB:
        globalData.colors = getPocketGB();
        break;
      case THEME_RUSTIC_GB:
        globalData.colors = getRusticGB();
        break;
      case THEME_MIST_GB:
        globalData.colors = getMistGB();
        break;
      case THEME_CRIMSON_GB:
        globalData.colors = getCrimsonGB();
        break;
    }
  }
}

static void updateFullScreen(void) {
  if (globalData.fullScreen && !IsWindowFullscreen()) {
    ToggleFullscreen();
  } else if (!globalData.fullScreen && IsWindowFullscreen()) {
    ToggleFullscreen();
  }
}

static void drawFPS(void) {
  if (showFPS) {
    const char *strFPS = TextFormat("FPS: %d", GetFPS());
    DrawText(strFPS, 10, 10, 24, GREEN);
  }
}

static void getEvent(void) {
  if (IsKeyPressed(KEY_F1)) {
    globalData.showCollisionShape = !globalData.showCollisionShape;
  }
  if (IsKeyPressed(KEY_F2)) {
    showFPS = !showFPS;
  }
}
