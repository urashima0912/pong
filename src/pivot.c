#include "pivot.h"

void drawPivot(Vector2 center) {
  DrawLine(
    center.x - SEGMENT_SIZE,
    center.y,
    center.x + SEGMENT_SIZE,
    center.y,
    RED
  );
  DrawLine(
    center.x,
    center.y - SEGMENT_SIZE,
    center.x,
    center.y + SEGMENT_SIZE,
    GREEN
  );
}