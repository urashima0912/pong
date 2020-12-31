#include "options.h"
#include "../../config.h"

#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

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
  DrawText("Options", 10, 10, 24, PONG_COLOR_3);
}

void freeOptions(Options **options) {
  if (*options != NULL) {
    free(*options);
    *options = NULL;
    #ifdef PONG_DEBUG
    printf("options deleted.\n");
    #endif
  }
}
