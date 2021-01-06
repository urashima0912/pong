#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

const static int32_t GL_MIN_PTO = 5;
const static int32_t GL_MAX_PTO = 10;

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
  Colors colors;
  bool showCollisionShape;
  int32_t ptos;
} Global;

Colors getPocketGB(void);
Colors getRusticGB(void);
Colors getMistGB(void);
Colors getCrimsonGB(void);

#endif /* PONG_GLOBAL_H */
