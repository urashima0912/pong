#include "app.h"
#include "config.h"
#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declaration static functions.
static void settingApp(void);
static void updateApp(App *const app);
static void drawApp(const App *const app);
static void freeInternalApp(App *app);


// implementation public functions.
App *initApp(void) {
  App *app = malloc(sizeof(App));
  if (app == NULL) {
    return NULL;
  }
  settingApp();
  return app;
}

void runApp(App *const app) {
  while (!WindowShouldClose()) {
    updateApp(app);
    drawApp(app);
  }
}

void freeApp(App **app) {
  if (*app != NULL) {
    #ifdef PONG_DEBUG
      printf("deleted app\n");
    #endif
    freeInternalApp(*app);
    free(*app);
    *app = NULL;
  }
}


// implementation static functions.
static void settingApp(void) {
  InitWindow(PONG_SCREEN_WIDTH, PONG_SCREEN_HEIGHT, PONG_SCREEN_TITLE);
  HideCursor();
  SetTargetFPS(60);
}

static void updateApp(App *const app) {
  // I need to do it
}

static void drawApp(const App *const app) {
  BeginDrawing();
  ClearBackground(PONG_COLOR_0);

  EndDrawing();
}

static void freeInternalApp(App *const app) {
  CloseWindow();
}