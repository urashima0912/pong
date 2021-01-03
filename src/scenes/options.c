#include "options.h"
#include "../../config.h"
#include <stdlib.h>


Options *initOptions(void) {
  Options *options = malloc(sizeof(Options));
  if (options == NULL) {
    return NULL;
  }
  return options;
}

void updateOptions(Options *const options) {
  // to do.
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
