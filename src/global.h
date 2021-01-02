#ifndef PONG_GLOBAL_H
#define PONG_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

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
