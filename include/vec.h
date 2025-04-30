#ifndef VEC_H
#define VEC_H

typedef struct {
  float x, y;
} Vec2;

Vec2 vec2(float x, float y);
Vec2 vec2Add(const Vec2 a, const Vec2 b);
Vec2 vec2Sub(const Vec2 a, const Vec2 b);
Vec2 vec2Scale(const Vec2 v, const float s);
Vec2 vec2Dot(const Vec2 a, const Vec2 b);
float vec2Mag(const Vec2 v);
float vec2MagSq(const Vec2 v);
Vec2 vec2Norm(const Vec2 v);
float vec2dist(const Vec2 a, const Vec2 b);
float vec2distSq(const Vec2 a, const Vec2 b);

// typedef struct {
//   float x, y, z;
// } Vec3;
//
// inline Vec3 vec3(float x, float y, float z);
// inline Vec3 vec3Add(Vec3 a, Vec3 b);
// inline Vec3 vec3Sub(Vec3 a, Vec3 b);
// inline Vec3 vec3Scale(Vec3 v, float s);
// inline Vec3 vec3Dot(Vec3 a, Vec3 b);
// inline Vec3 vec3Cross(Vec3 a, Vec3 b);
// inline float vec3Len(Vec3 v);
// inline Vec3 vec3Norm(Vec3 v);

#endif
