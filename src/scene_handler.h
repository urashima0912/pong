#ifndef PONG_SCENE_HANDLER_H
#define PONG_SCENE_HANDLER_H

typedef enum ScenesTypes {
  SCENE_MENU = 1,
  SCENE_BOARD,
  SCENE_OPTIONS,
} ScenesTypes;

typedef struct SceneHandler {
  void *scene;
  ScenesTypes type;
} SceneHandler;

SceneHandler *initSceneHandler(void);

void updateSceneHandler(SceneHandler *const handler);

void drawSceneHandler(const SceneHandler *const handler);

void freeScenehandler(SceneHandler **handler);

#endif /* PONG_SCENE_HANDLER_H */
