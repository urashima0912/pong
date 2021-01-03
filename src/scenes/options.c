#include "options.h"
#include "../../config.h"
#include <stdlib.h>


static bool finished = false;

static void resetValue(void);

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
  // to do.
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
