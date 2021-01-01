#ifndef PONG_PIVOT_H
#define PONG_PIVOT_H

#include <raylib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static const int32_t SEGMENT_SIZE = 10;
static const Color VERTICAL_COLOR = GREEN;
static const Color HORIZONTAL_COLOR = RED;

void drawPivot(Vector2 center);

#ifdef __cplusplus
}
#endif

#endif // PONG_PIVOT_H
