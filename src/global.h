#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

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
  int32_t maxPtos;
} Global;

Colors getPocketGB(void);
Colors getRusticGB(void);
Colors getMistGB(void);
Colors getCrimsonGB(void);

#endif /* PONG_GLOBAL_H */
