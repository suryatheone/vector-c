#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} Vector2D;

Vector2D createVector(float x, float y);
Vector2D additionVector(Vector2D a, Vector2D b);
Vector2D subtractVector(Vector2D a, Vector2D b);
Vector2D scaleVector(Vector2D v, float scalar);
Vector2D normalizeVector(Vector2D v);
Vector2D linearCombination(Vector2D a, float scalar_a, Vector2D b,
                           float scalar_b);
float dotProduct(Vector2D a, Vector2D b);
float angleBetwen(Vector2D a, Vector2D b);
float normVector(Vector2D v);

// New geometric operations
float crossProduct2D(Vector2D a, Vector2D b);
Vector2D projectVector(Vector2D a, Vector2D b);
Vector2D rotateVector(Vector2D v, float angle_degrees);
float distanceVector(Vector2D a, Vector2D b);

#endif
