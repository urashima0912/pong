#include "options.h"
#include "../../config.h"
#include "../global.h"
#include <stdlib.h>
#include <stdint.h>

extern Global globalData;

static bool finished = false;

static void resetValue(void);
static void drawTitle(void);

Options *initOptions(void) {
  resetValue();
  Options *options = malloc(sizeof(Options));
  if (options == NULL) {
    return NULL;
  }
  return options;
}

void updateOptions(Options *const options) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    finished = true;
  }
}

void drawOptions(const Options *const options) {
  drawTitle();
}

void freeOptions(Options **options) {
  if (*options != NULL) {
    free(*options);
    *options = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_SCENE_OPTIONS_DELETED);
    #endif
  }
}

bool finishOptions(void) {
  return finished;
}

static void resetValue(void) {
  finished = false;
}

static void drawTitle(void) {
  const int32_t fontSize = 24;
  const int32_t middle = GetScreenWidth() / 2;
  const int32_t posX = middle - TextLength(PONG_OPTIONS_TITLE) * (fontSize / 2) / 2; 

  DrawText(PONG_OPTIONS_TITLE, posX, 10, fontSize, globalData.colors.color2);
}
