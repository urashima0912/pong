#include "scene_handler.h"
#include "./scenes/board.h"
#include "./scenes/menu.h"
#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declaration static functions.
static void loadScene(SceneHandler *handler, ScenesTypes type);
static Menu *loadMenuScene(void);
static Board *loadBoardScene(void);
static void unloadScene(SceneHandler *handler);
static void updateScene(SceneHandler *handler);
static void drawScene(const SceneHandler *const handler);

// implementation public functions.
SceneHandler *initSceneHandler(void) {
  SceneHandler *handler = malloc(sizeof(SceneHandler)); 
  if (handler == NULL) {
    return NULL;
  }

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
    printf("deleted SceneHandler.\n");
    #endif
  }
}

// implementation static functions.
static void loadScene(SceneHandler *handler, ScenesTypes type) {
  unloadScene(handler);
  switch (handler->type) {
    case SCENE_MENU:
      handler->type = type;
      handler->scene = loadMenuScene();
      break;
    case SCENE_BOARD:
      handler->type = type;
      handler->scene = loadBoardScene();
  }
}

static Menu *loadMenuScene(void) {
  return initMenu();
}
static Board *loadBoardScene(void) {
  return initBoard();
}

static void unloadScene(SceneHandler *handler) {
  if (handler->type) {
    switch (handler->type) {
      case SCENE_MENU:
        freeMenu((Menu **)&handler->scene);
        break;
      case SCENE_BOARD:
        freeBoard((Board **)&handler->scene);
    }
  }
}

static void updateScene(SceneHandler *handler) {
  switch (handler->type) {
    case SCENE_MENU:
      updateMenu((Menu *)handler->scene);
      break;
    case SCENE_BOARD:
      updateBoard((Board *)handler->scene);
  }
}

static void drawScene(const SceneHandler *const handler) {
  switch (handler->type) {
    case SCENE_MENU:
      drawMenu((Menu *)handler->scene);
      break;
    case SCENE_BOARD:
      drawBoard((Board *)handler->scene);
  }
}
