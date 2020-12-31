#ifndef PONG_APP_H
#define PONG_APP_H

typedef struct App
{
  /* data */
} App;

App *initApp(void);

void runApp(App *const app);

void freeApp(App **app);

#endif // PONG_APP_H
