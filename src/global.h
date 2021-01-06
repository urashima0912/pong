#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

const static int32_t GL_MIN_PTO = 5;
const static int32_t GL_MAX_PTO = 10;


typedef enum GlMode {
  MODE_PVP = 0,
  MODE_CPU
} GlMode;
typedef enum GlTheme {
  THEME_POCKET_GB = 0,
  THEME_RUSTIC_GB,
  THEME_MIST_GB,
  THEME_CRIMSON_GB,
} GlTheme;

typedef enum OptionEvent {
  OPT_EMPTY = -1,
  OPT_START = 0,
  OPT_OPTIONS,
  OPT_EXIT
} OptionEvent;

typedef struct Colors {
  Color color0;
  Color color1;
  Color color2;
  Color color3;
} Colors;

typedef struct Global {
  GlMode mode;
  GlTheme theme;
  Colors colors;
  bool showCollisionShape;
  int32_t ptos;
} Global;

Colors getPocketGB(void);
Colors getRusticGB(void);
Colors getMistGB(void);
Colors getCrimsonGB(void);

void initGlobal(Global *const globalData);
void drawMenuInfo(Global globalData);

#endif /* PONG_GLOBAL_H */
