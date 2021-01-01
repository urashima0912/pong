#ifndef PONG_APP_H
#define PONG_APP_H

#include "scene_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct App
{
  SceneHandler *sceneHandler;
} App;

App *initApp(void);

void runApp(App *const app);

void freeApp(App **app);

#ifdef __cplusplus
}
#endif

#endif // PONG_APP_H
