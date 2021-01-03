#include "app.h"
#include "config.h"
#include "global.h"
#include <stdlib.h>

// declaration static functions.
static bool finished = false;

static void settingApp(void);
static void updateApp(App *const app);
static void drawApp(const App *const app);
static void freeInternalApp(App *app);

Global globalData = { 0 };

// implementation public functions.
App *initApp(void) {
  finished = false;
  App *app = malloc(sizeof(App));
  if (app == NULL) {
    return NULL;
  }
  settingApp();

  globalData.colors = getPocketGB();
  globalData.maxPtos = 5;

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
}

static void updateApp(App *const app) {
  updateSceneHandler(app->sceneHandler);

  if (IsKeyPressed(KEY_F1)) {
    globalData.showCollisionShape = !globalData.showCollisionShape;
  }

  finished = finishSceneHanlder();
}

static void drawApp(const App *const app) {
  BeginDrawing();
  ClearBackground(globalData.colors.color0);
  drawSceneHandler(app->sceneHandler);
  EndDrawing();
}

static void freeInternalApp(App *const app) {
  freeScenehandler(&app->sceneHandler);
  CloseWindow();
}