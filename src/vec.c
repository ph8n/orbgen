#include "vec.h"
#include <math.h>

// Vec2 Operations
Vec2 vec2(float x, float y) {
  Vec2 v = {x, y};
  return v;
}

Vec2 vec2Add(const Vec2 a, const Vec2 b) {
  return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 vec2Sub(const Vec2 a, const Vec2 b) {
  return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 vec2Scale(const Vec2 v, const float s) { return (Vec2){v.x * s, v.y * s}; }

Vec2 vec2Dot(const Vec2 a, const Vec2 b) {
  return (Vec2){a.x * b.x, a.y * b.y};
}

float vec2Mag(const Vec2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

float vec2MagSq(const Vec2 v) { return v.x * v.x + v.y * v.y; }

Vec2 vec2Clone(const Vec2 v) { return (Vec2){v.x, v.y}; }

Vec2 vec2Norm(const Vec2 v) {
  float length = vec2Mag(v);
  if (length > 1e-6) {
    return (Vec2){v.x / length, v.y / length};
  } else {
    return (Vec2){0.0f, 0.0f};
  }
}

float vec2dist(const Vec2 a, const Vec2 b) {
  return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float vec2distSq(const Vec2 a, const Vec2 b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// Vec3 operations
// Vec3 vec3(float x, float y, float z);
// Vec3 vec3Add(Vec3 a, Vec3 b);
// Vec3 vec3Sub(Vec3 a, Vec3 b);
// Vec3 vec3Scale(Vec3 a, float s);
// Vec3 vec3Dot(Vec3 a, Vec3 b);
// Vec3 vec3Cross(Vec3 a, Vec3 b);
// float vec3Len(Vec3 v);
// Vec3 vec3Norm(Vec3 v);
