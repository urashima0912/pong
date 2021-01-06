#ifndef PONG_OPTIONS_H
#define PONG_OPTIONS_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OptionItems {
  ITEM_PTOS = 0,
  ITEM_THEME,
  ITEM_GAME_MODE,
  ITEM_FULLSCREEN,
} OptionItems;

typedef struct Options {
  OptionItems item;
} Options;

Options *initOptions(void);

void updateOptions(Options *const options);

void drawOptions(const Options *const options);

void freeOptions(Options **options);

bool finishOptions(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_OPTIONS_H */
