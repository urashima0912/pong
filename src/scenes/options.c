#include "options.h"
#include "../../config.h"
#include "../global.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern Global globalData;

static bool finished = false;
static const int32_t FONTSIZE = 24;
static int32_t internalPto = 0;
static GlTheme internalTheme = -1;
static GlMode internalMode = -1;

static void resetValue(void);
static void drawTitle(void);
static void drawOptionPtos(const Options *const options, const int32_t posY);
static void drawOptionTheme(const Options *const options, const int32_t posY);
static void drawOptionGameMode(const Options *const options, const int32_t posY);
static void drawOptionFullScreen(const Options *const options, const int32_t posY);
static void updateItemSelected(Options *const options);
static void closeOptions(void);
static void changeValueItem(Options *const options);
static void changePtos(void);
static void updatePtos(void);
static void initPtos(void);
static void freePtos(void);
static void initTheme(void);
static void freeTheme(void);
static void updateTheme(const Options *const options);
static void updateThemeData(void);
static void updateMode(const Options *const options);
static void updateModeData(void);
static void initGameMode(void);
static void freeGameMode(void);
static void updateFullScreen(const Options *const options);

static char *ptoData = NULL;
static char *themeData = NULL;
static char *modeData = NULL;

const static char *LEFT = "< ";
const static char *RIGHT = " >";
const static int32_t DIFF_LEFT = 60;
const static int32_t DIFF_RIGHT = 60;

Options *initOptions(void) {
  resetValue();
  Options *options = malloc(sizeof(Options));
  if (options == NULL) {
    return NULL;
  }

  initPtos();
  initTheme();
  initGameMode();

  options->item = ITEM_PTOS;

  return options;
}

void updateOptions(Options *const options) {
  updateItemSelected(options);
  changeValueItem(options);
  updateTheme(options);
  updateThemeData();
  updateMode(options);
  updateModeData();
  updateFullScreen(options);
  closeOptions();
}

void drawOptions(const Options *const options) {
  int32_t posY = 100;
  drawTitle();
  drawOptionPtos(options, posY);
  posY += FONTSIZE + 10;
  drawOptionTheme(options, posY);
  posY += FONTSIZE + 10;
  drawOptionGameMode(options, posY);
  posY += FONTSIZE + 10;
  drawOptionFullScreen(options, posY);
  drawMenuInfo(globalData);
}

void freeOptions(Options **options) {
  if (*options != NULL) {
    freePtos();
    freeTheme();
    freeGameMode();
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
  if (options->item == ITEM_PTOS) {
    updatePtos();
  }
  Color selected = options->item == ITEM_PTOS ? globalData.colors.color3 : globalData.colors.color1;
  DrawText(PONG_OPTION_MAX_PTOS, DIFF_LEFT, posY, FONTSIZE, selected);
  DrawText(ptoData, GetScreenWidth() - MeasureText(ptoData, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}

static void drawOptionTheme(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_THEME ? globalData.colors.color3 : globalData.colors.color1;
  DrawText(PONG_OPTION_THEME, DIFF_LEFT, posY, FONTSIZE, selected);
  DrawText(themeData, GetScreenWidth() - MeasureText(themeData, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}

static void drawOptionGameMode(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_GAME_MODE ? globalData.colors.color3 : globalData.colors.color1;
  DrawText(PONG_OPTION_GAME_MODE, DIFF_LEFT, posY, FONTSIZE, selected);
  DrawText(modeData, GetScreenWidth() - MeasureText(modeData, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}

static void drawOptionFullScreen(const Options *const options, const int32_t posY) {
  Color selected = options->item == ITEM_FULLSCREEN ? globalData.colors.color3 : globalData.colors.color1;
  DrawText(PONG_FULLSCREEN, DIFF_LEFT, posY, FONTSIZE, selected);

  const char *value = !globalData.fullScreen ? "FALSE >" : "< TRUE";
  DrawText(value, GetScreenWidth() - MeasureText(value, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}

static void updateItemSelected(Options *const options) {
  const int32_t min = (int32_t) ITEM_PTOS;
  const int32_t max = (int32_t) ITEM_FULLSCREEN;
  if (IsKeyPressed(KEY_UP)) {
    PlaySound(globalData.leftSound);
    const int32_t value = options->item - 1;
    if (value >= min) {
      options->item--;
    } else {
      options->item = max;
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    PlaySound(globalData.leftSound);
    const int32_t value = options->item + 1;
    if (value <= max) {
      options->item++;
    } else {
      options->item = min;
    }
  }
}

static void closeOptions(void) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    finished = true;
  }
}

static void changeValueItem(Options *const options) {
  const OptionItems item = options->item;
  if (item == ITEM_PTOS) {
    changePtos();
  }
}

static void changePtos(void) {
  const int32_t ptos = globalData.ptos;
  if (IsKeyPressed(KEY_LEFT) && ptos > GL_MIN_PTO) {
    PlaySound(globalData.rightSound);
    globalData.ptos--;
  } else if (IsKeyPressed(KEY_RIGHT) && ptos < GL_MAX_PTO) {
    PlaySound(globalData.rightSound);
    globalData.ptos++;
  }
}

static void updatePtos(void) {
  if (internalPto != globalData.ptos) {
    internalPto = globalData.ptos;
    strcpy(ptoData, "");
    const char *num = TextFormat("%d", internalPto);
    if (internalPto > GL_MIN_PTO) {
      strcat(ptoData, LEFT);
    }
    strcat(ptoData, num);
    if (internalPto < GL_MAX_PTO) {
      strcat(ptoData, RIGHT);
    }
  }
}

static void initPtos(void) {
  const int32_t size = 5;
  ptoData = malloc(sizeof(char) * size);
  ptoData[size - 1] = '\0';
}

static void freePtos(void) {
  internalPto = 0;
  free(ptoData);
  ptoData = NULL;
  #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, "->\t deleted ptoData.");
  #endif
}

static void initTheme(void) {
  const int32_t size = 20;
  themeData = malloc(sizeof(char) * size);
  themeData[size - 1] = '\0';
}
static void freeTheme(void) {
  free(themeData);
  themeData = NULL;
  internalTheme = -1;
  #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, "->\t deleted themeData.");
  #endif
}

static void initGameMode(void) {
  const int32_t size = 4;
  modeData = malloc(sizeof(char) * size);
  modeData[size - 1] = '\0';
}

static void freeGameMode(void) {
  free(modeData);
  modeData = NULL;
  internalMode = -1;
  #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, "->\t deleted modeData.");
  #endif
}

static void updateTheme(const Options *const options) {
  if (options->item == ITEM_THEME) {
    const int32_t minTheme = (int32_t) THEME_POCKET_GB;
    const int32_t maxTheme = (int32_t) THEME_CRIMSON_GB;
    const int32_t theme = (int32_t) globalData.theme;
    if (IsKeyPressed(KEY_LEFT) && theme > minTheme) {
      PlaySound(globalData.rightSound);
      globalData.theme--;
    } else if (IsKeyPressed(KEY_RIGHT) && theme < maxTheme) {
      PlaySound(globalData.rightSound);
      globalData.theme++;
    }
  }
}

static void updateThemeData(void) {
  if (internalTheme != globalData.theme) {
    internalTheme = globalData.theme;
    const int32_t minTheme = (int32_t) THEME_POCKET_GB;
    const int32_t maxTheme = (int32_t) THEME_CRIMSON_GB;

    strcpy(themeData, "");
    if ((int32_t)internalTheme > minTheme) {
      strcat(themeData, LEFT);
    }

    switch (internalTheme) {
      case THEME_POCKET_GB:
        strcat(themeData, PONG_THEME_POCKET_GB);
        break;
      case THEME_RUSTIC_GB:
        strcat(themeData, PONG_THEME_RUSTIC_GB);
        break;
      case THEME_MIST_GB:
        strcat(themeData, PONG_THEME_MIST_GB);
        break;
      case THEME_CRIMSON_GB:
        strcat(themeData, PONG_THEME_CRIMSON_GB);
        break;
    }

    if ((int32_t)internalTheme < maxTheme) {
      strcat(themeData, RIGHT);
    }
  }
}

static void updateMode(const Options *const options) {
  if (options->item == ITEM_GAME_MODE) {
    const int32_t mode = (int32_t)globalData.mode;
    if (IsKeyPressed(KEY_LEFT) && mode == MODE_PVP) {
      PlaySound(globalData.rightSound);
      globalData.mode = MODE_CPU;
    } else if (IsKeyPressed(KEY_RIGHT) && mode == MODE_CPU) {
      PlaySound(globalData.rightSound);
      globalData.mode = MODE_PVP;
    }
  }
}


static void updateModeData(void) {
  if (internalMode != globalData.mode) {
    internalMode = globalData.mode;
    strcpy(modeData, "");
    switch (internalMode) {
      case MODE_CPU:
        strcat(modeData, PONG_OPTION_GAME_MODE_CPU);
        strcat(modeData, RIGHT);
        break;
      case MODE_PVP:
        strcat(modeData, LEFT);
        strcat(modeData, PONG_OPTION_GAME_MODE_PVP);
        break;
    }
  } 
}

static void updateFullScreen(const Options *const options) {
  if (options->item == ITEM_FULLSCREEN) {
    if (IsKeyPressed(KEY_LEFT) && globalData.fullScreen) {
      PlaySound(globalData.rightSound);
      globalData.fullScreen = false;
    } else if (IsKeyPressed(KEY_RIGHT) && !globalData.fullScreen) {
      PlaySound(globalData.rightSound);
      globalData.fullScreen = true;
    }
  }
}
