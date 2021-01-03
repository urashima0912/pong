#include "scene_handler.h"
#include "./scenes/board.h"
#include "./scenes/menu.h"
#include "./scenes/options.h"
#include "../config.h"
#include <stdlib.h>


// declaration static functions.
static bool finished = false;

static void loadScene(SceneHandler *handler, ScenesTypes type);
static Menu *loadMenuScene(void);
static Board *loadBoardScene(void);
static Options *loadBoardOptions(void);
static void unloadScene(SceneHandler *handler);
static void updateScene(SceneHandler *handler);
static void drawScene(const SceneHandler *const handler);


// implementation public functions.
SceneHandler *initSceneHandler(void) {
  finished = false;
  SceneHandler *handler = malloc(sizeof(SceneHandler)); 
  if (handler == NULL) {
    return NULL;
  }

  handler->scene = NULL;
  loadScene(handler, SCENE_MENU);

  return handler;
}

void updateSceneHandler(SceneHandler *const handler) {
  updateScene(handler);
}

void drawSceneHandler(const SceneHandler *const handler) {
  drawScene(handler);
}

void freeScenehandler(SceneHandler **handler) {
  if (*handler != NULL) {
    unloadScene(*handler);
    free(*handler);
    handler = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_SCENE_HANDLER_DELETED);
    #endif
  }
}

bool finishSceneHanlder(void) {
  return finished;
}


// implementation static functions.
static void loadScene(SceneHandler *handler, ScenesTypes type) {
  unloadScene(handler);
  handler->type = type;
  switch (type) {
    case SCENE_MENU:
      handler->scene = loadMenuScene();
      break;
    case SCENE_BOARD:
      handler->scene = loadBoardScene();
      break;
    case SCENE_OPTIONS:
      handler->scene = loadBoardOptions();
  }
}

static Menu *loadMenuScene(void) {
  return initMenu();
}
static Board *loadBoardScene(void) {
  return initBoard();
}

static Options *loadBoardOptions(void) {
  return initOptions();
}

static void unloadScene(SceneHandler *handler) {
  switch (handler->type) {
    case SCENE_MENU:
      freeMenu((Menu **)&handler->scene);
      break;
    case SCENE_BOARD:
      freeBoard((Board **)&handler->scene);
      break;
    case SCENE_OPTIONS:
      freeOptions((Options **)&handler->scene);
  }
}

static void updateScene(SceneHandler *handler) {
  switch (handler->type) {
    case SCENE_MENU:
      updateMenu((Menu *)handler->scene);
      const OptionEvent event = finishMenu();
      if (event!= OPT_EMPTY) {
        if (event == OPT_START) {
          loadScene(handler, SCENE_BOARD);
        } else if (event == OPT_OPTIONS) {
          loadScene(handler, SCENE_OPTIONS);
        } else if (event == OPT_EXIT) {
          finished = true;
        }
      }
      break;
    case SCENE_BOARD:
      updateBoard((Board *)handler->scene);
      if (finishBoard()) {
        loadScene(handler, SCENE_MENU);
      }
      break;
    case SCENE_OPTIONS:
      updateOptions((Options *)handler->scene);
      if (finishOptions()) {
        loadScene(handler, SCENE_MENU);
      }
  }
}

static void drawScene(const SceneHandler *const handler) {
  switch (handler->type) {
    case SCENE_MENU:
      drawMenu((Menu *)handler->scene);
      break;
    case SCENE_BOARD:
      drawBoard((Board *)handler->scene);
      break;
    case SCENE_OPTIONS:
      drawOptions((Options *)handler->scene);
  }
}
