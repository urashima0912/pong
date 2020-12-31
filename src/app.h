#ifndef PONG_APP_H
#define PONG_APP_H

#include "scene_handler.h"

typedef struct App
{
  SceneHandler *sceneHandler;
} App;

App *initApp(void);

void runApp(App *const app);

void freeApp(App **app);

#endif // PONG_APP_H
