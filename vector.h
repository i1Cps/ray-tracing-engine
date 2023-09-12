// A three element vector class with lots of operators and common functions

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>

class Vertex;

class Vector {
 public:
  float x;
  float y;
  float z;

  // Constructor with x, y, and z values: Initializes a vector with specified
  // components.
  Vector(float px, float py, float pz) {
    x = px;
    y = py;
    z = pz;
  }

  // Default constructor: Initializes a vector at the origin
  Vector() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  // Normalize the vector, making it a unit vector.
  void normalise() {
    float len = (float)sqrt((double)(x * x + y * y + z * z));
    x = x / len;
    y = y / len;
    z = z / len;
  }

  // Calculate the squared length of the vector.
  float len_sqr() { return (x * x + y * y + z * z); }

  // Calculate the length of the vector.
  float length() { return (float)sqrt((double)(x * x + y * y + z * z)); }

  // Calculate the dot product of two vectors.
  float dot(Vector other) { return x * other.x + y * other.y + z * other.z; }

  // Calculate the dot product of two vectors, provided as arguments.
  float better_dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  // Calculate the refraction of a vector given a normal, index of refraction,
  // incident vector, refracted vector and whether there is total internal
  // reflection.
  void refraction(Vector& normal, float ior, Vector w0, Vector& refract_ray,
                  bool tir) {
    // Initialise n with index of reflection (indicates how much the light
    // behaves when passing from one atmosphere to another)
    float n = ior;
    float cos_theta_i = -normal.dot(w0);
    float cos_theta_t =
        sqrt(1.0f - ((1.0f / pow(n, 2)) * (1.0f - pow(cos_theta_i, 2))));

    // Check for TIR, if so return incident vector
    if (cos_theta_t < 0.0f) {
      // Tir return true
      // cos_theta_i = -cos_theta_i;
      // normal = -normal;
      // normal.negate();
      // n = 1.0 / n;
      refract_ray = w0;
      return;
    }
    // If no TIR calculate refracted vector using Snell's law
    refract_ray =
        (1 / n * w0) - ((((1 / n) * cos_theta_i) - cos_theta_t) * normal);
    return;
  }

  // Calculate the reflection of a vector given an incident vector and the
  // resulting reflected vector.
  void reflection(Vector initial, Vector& reflect) {
    float d;

    d = dot(initial);
    d = d * 2.0f;

    reflect.x = initial.x - d * x;
    reflect.y = initial.y - d * y;
    reflect.z = initial.z - d * z;
  }

  // Negate all components of the vector.
  void negate() {
    x = -x;
    y = -y;
    z = -z;
  }

  // Calculate the cross product of two vectors, storing the result in 'result'.
  void cross(Vector& other, Vector& result) {
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
  }

  // Returns a new vector that is the result of the cross product between
  // vectors 'a' and 'b'
  Vector better_cross(Vector& a, Vector& b) {
    Vector result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
  }

  // Calculate the cross product of this vector and another vector 'other'
  void cross(Vector& other) {
    Vector result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    x = result.x;
    y = result.y;
    z = result.z;
  }

  // Assignment operator for assigning one vector to another.
  Vector& operator=(const Vector& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
  }

  // Multiply two vectors component-wise.
  Vector operator*(const Vector& b) {
    Vector r;
    r.x = this->x * b.x;
    r.y = this->y * b.y;
    r.z = this->z * b.z;

    return r;
  }

  // Subtract two vectors component-wise and return the result.
  friend Vector operator-(const Vector& a, const Vector& b) {
    Vector r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;

    return r;
  }

  // Add two vectors component-wise and return the result.
  friend Vector operator+(const Vector& a, const Vector& b) {
    Vector r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;

    return r;
  }

  // Add a vector to this vector component-wise and return the result.
  Vector operator+(const Vector& b) {
    Vector r;
    r.x = this->x + b.x;
    r.y = this->y + b.y;
    r.z = this->z + b.z;

    return r;
  }

  // Multiply this vector by a scalar value and return the result.
  Vector operator*(float& b) {
    Vector r;
    r.x = this->x * b;
    r.y = this->y * b;
    r.z = this->z * b;

    return r;
  }

  // Multiply a scalar value by a vector and return the result.
  friend Vector operator*(const float a, const Vector& b) {
    Vector t;
    t.x = a * b.x;
    t.y = a * b.y;
    t.z = a * b.z;
    return t;
  }

  // Negation operator for negating all components of a vector.
  Vector operator-() { return Vector(-this->x, -this->y, -this->z); }

  // Assignment operator for assigning a Vertex to a Vector.
  Vector& operator=(Vertex& other) {
    Vector* v;
    v = (Vector*)&other;
    this->x = v->x;
    this->y = v->y;
    this->z = v->z;
    return *this;
  }
};

#endif
