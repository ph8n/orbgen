#ifndef OBJECTS_H
#define OBJECTS_H

#include "vec.h"

typedef struct {
  Vec2 pos;
  Vec2 vel;
  Vec2 acc;
  float mass;
  float radius;
  float color[3];
} Object2D;

#endif
