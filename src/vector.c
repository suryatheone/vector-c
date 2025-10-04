#include "vector.h"
#include <math.h>

Vector2D createVector(float x, float y) {
  Vector2D result;
  result.x = x;
  result.y = y;
  return result;
}

Vector2D additionVector(Vector2D a, Vector2D b) {
  Vector2D result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return result;
}

Vector2D subtractVector(Vector2D a, Vector2D b) {
  Vector2D result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return result;
}

Vector2D linearCombination(Vector2D a, float scalar_a, Vector2D b,
                           float scalar_b) {
  Vector2D result;
  result.x = (scalar_a * a.x) + (scalar_b * b.x);
  result.y = (scalar_a * a.y) + (scalar_b * b.y);
  return result;
}

Vector2D normalizeVector(Vector2D v) {
    float norm = normVector(v);
    Vector2D result;

    if (norm == 0.0f) {
        return createVector(0.0f, 0.0f);
    }

    result.x = v.x / norm;
    result.y = v.y / norm;
    return result;
}

float dotProduct(Vector2D a, Vector2D b) { return (a.x * b.x) + (a.y * b.y); }

Vector2D scaleVector(Vector2D v, float scalar) {
  Vector2D result;
  result.x = v.x * scalar;
  result.y = v.y * scalar;
  return result;
}

float angleBetwen(Vector2D a, Vector2D b) {
  float radiant_angle =
      acosf(dotProduct(a, b) / (normVector(a) * normVector(b)));
  return radiant_angle * (180.0f / M_PI);
}

float normVector(Vector2D v) { return (float)sqrtf((v.x * v.x) + (v.y * v.y)); }

// --- New geometric operations ---

float crossProduct2D(Vector2D a, Vector2D b) {
  return (a.x * b.y) - (a.y * b.x);
}

Vector2D projectVector(Vector2D a, Vector2D b) {
  float dot = dotProduct(a, b);
  float norm_sq = (b.x * b.x) + (b.y * b.y);

  if (norm_sq == 0.0f) {
    return createVector(0.0f, 0.0f); // Cannot project onto a zero vector
  }

  float scale = dot / norm_sq;
  return scaleVector(b, scale);
}

Vector2D rotateVector(Vector2D v, float angle_degrees) {
  float angle_rad = angle_degrees * (M_PI / 180.0f);
  float cos_a = cosf(angle_rad);
  float sin_a = sinf(angle_rad);

  Vector2D result;
  result.x = v.x * cos_a - v.y * sin_a;
  result.y = v.x * sin_a + v.y * cos_a;
  return result;
}

float distanceVector(Vector2D a, Vector2D b) {
  Vector2D diff = subtractVector(a, b);
  return normVector(diff);
}

