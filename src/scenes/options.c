#include "options.h"
#include "../../config.h"
#include "../global.h"
#include <stdlib.h>
#include <stdint.h>

extern Global globalData;

static bool finished = false;
static const int32_t FONTSIZE = 24;

static void resetValue(void);
static void drawTitle(void);
static void drawOptionPtos(const Options *const options, const int32_t posY);
static void drawOptionTheme(const Options *const options, const int32_t posY);
static void drawOptionGameMode(const Options *const options, const int32_t posY);
static void updateItemSelected(Options *const options);


Options *initOptions(void) {
  resetValue();
  Options *options = malloc(sizeof(Options));
  if (options == NULL) {
    return NULL;
  }

  options->item = ITEM_PTOS;

  return options;
}

void updateOptions(Options *const options) {
  updateItemSelected(options);
  if (IsKeyPressed(KEY_ESCAPE)) {
    finished = true;
  }
}

void drawOptions(const Options *const options) {
  int32_t posY = 100;
  drawTitle();
  drawOptionPtos(options, posY);
  posY += FONTSIZE;
  drawOptionTheme(options, posY);
  posY += FONTSIZE;
  drawOptionGameMode(options, posY);
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
  const int32_t middle = GetScreenWidth() / 2;
  const int32_t posX = middle - TextLength(PONG_OPTIONS_TITLE) * (FONTSIZE / 2) / 2; 

  DrawText(PONG_OPTIONS_TITLE, posX, 10, FONTSIZE, globalData.colors.color2);
}

static void drawOptionPtos(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_PTOS ? globalData.colors.color3 : globalData.colors.color1;
  const char *value = TextFormat("< %d >", globalData.maxPtos);

  DrawText(PONG_OPTION_MAX_PTOS, 10, posY, 24, selected);
  DrawText(value, GetScreenWidth() - 24 * TextLength(value), posY, 24,selected);
}

static void drawOptionTheme(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_THEME ? globalData.colors.color3 : globalData.colors.color1;
  const char *value = TextFormat("POCKET", globalData.maxPtos);

  DrawText("THEME:", 10, posY, 24, selected);
  DrawText(value, GetScreenWidth() - 24 * TextLength(value), posY, 24,selected);
}


static void drawOptionGameMode(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_GAME_MODE ? globalData.colors.color3 : globalData.colors.color1;
  const char *value = PONG_OPTION_GAME_MODE_CPU;
  
  DrawText(PONG_OPTION_GAME_MODE, 10, posY, 24, selected);
  DrawText(value, GetScreenWidth() - 24 * TextLength(value), posY, 24, selected);
}

static void updateItemSelected(Options *const options) {
  const int32_t min = (int32_t) ITEM_PTOS;
  const int32_t max = (int32_t) ITEM_GAME_MODE;
  if (IsKeyPressed(KEY_UP)) {
    const int32_t value = options->item - 1;
    if (value >= min) {
      options->item--;
    } else {
      options->item = ITEM_GAME_MODE;
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    const int32_t value = options->item + 1;
    if (value <= max) {
      options->item++;
    } else {
      options->item = ITEM_PTOS;
    }
  }
}
