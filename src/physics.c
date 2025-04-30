#include "physics.h"

Vec2 forcesBetween2D(const Object2D a, const Object2D b) {
  Vec2 direction = vec2Sub(b.pos, a.pos);
  float distanceSq = vec2MagSq(direction);
  if (distanceSq < 1e-6) {
    return vec2(0.0, 0.0);
  }
  float forceMag = (G * a.mass * b.mass) / distanceSq;
  Vec2 force = vec2Scale(vec2Norm(direction), forceMag);
  return force;
}

void updateTwoBodyEuler(Object2D *A, Object2D *B, float dt) {
  // compute forces
  Vec2 fA = forcesBetween2D(*A, *B);
  Vec2 fB = vec2Scale(fA, -1);

  // compute accelerations a = F/m
  Vec2 aA = vec2Scale(fA, 1.0f / A->mass);
  Vec2 aB = vec2Scale(fB, 1.0f / B->mass);

  // update velocities v += a*dt
  A->vel = vec2Add(A->vel, vec2Scale(aA, dt));
  B->vel = vec2Add(B->vel, vec2Scale(aB, dt));

  // update positions p += v*dt
  A->pos = vec2Add(A->pos, vec2Scale(A->vel, dt));
  B->pos = vec2Add(B->pos, vec2Scale(B->vel, dt));
}
