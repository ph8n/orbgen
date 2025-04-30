#ifndef PHYSICS_H
#define PHYSICS_H

#define G 6.67430e-11f // Gravitational constant

#include "objects.h"
#include "vec.h"

Vec2 forcesBetween2D(const Object2D a, const Object2D b);
void updateTwoBodyEuler(Object2D *A, Object2D *B, float dt);

#endif
