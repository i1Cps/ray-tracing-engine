#include "quadratic_object.h"

#include <math.h>

// Constructor for Quadratic object
Quadratic::Quadratic(float a_, float b_, float c_, float d_, float e_, float f_,
                     float g_, float h_, float i_, float j_) {
  a = a_;
  b = b_;
  c = c_;
  d = d_;
  e = e_;
  f = f_;
  g = g_;
  h = h_;
  i = i_;
  j = j_;
}

// Calculate ray intersection with the quadratic object
Hit* Quadratic::intersection(Ray ray) {
  // define ray
  float ray_xpos = ray.position.x;
  float ray_ypos = ray.position.y;
  float ray_zpos = ray.position.z;

  float ray_xdir = ray.direction.x;
  float ray_ydir = ray.direction.y;
  float ray_zdir = ray.direction.z;
  // Calculate coefficients for the quadratic equation
  //    Aq = aD2x + 2bDxDy + 2cDxDz + eD2y + 2fDyDz + gD2z
  float Aq = a * pow(ray_xdir, 2) + 2 * b * ray_xdir * ray_ydir +
             2 * c * ray_xdir * ray_zdir + e * pow(ray_ydir, 2) +
             2 * f * ray_ydir * ray_zdir + h * pow(ray_zdir, 2);

  //    Bq =
  //    2(aPxDx+b(PxDy+DxPy)+c(PxDz+DxPz)+dDx+ePyDy+f(PyDz+DyPz)+gDy+hPzDz+iDz)
  float Bq = 2 * (a * ray_xpos * ray_xdir +
                  b * (ray_xpos * ray_ydir + ray_xdir * ray_ypos) +
                  c * (ray_xpos * ray_zdir + ray_xdir * ray_zpos) +
                  d * ray_xdir + e * ray_ypos * ray_ydir +
                  f * (ray_ypos * ray_zdir + ray_ydir * ray_zpos) +
                  g * ray_ydir + h * ray_zpos * ray_zdir + i * ray_zdir);

  //    Cq = aP2x + 2bPxPy + 2cPxPz + 2dPx + eP2y + 2fPyPz + 2gPy + hP2z + 2iPz
  //    + j
  float Cq = a * pow(ray_xpos, 2) + 2 * b * ray_xpos * ray_ypos +
             2 * c * ray_xpos * ray_zpos + 2 * d * ray_xpos +
             e * pow(ray_ypos, 2) + 2 * f * ray_ypos * ray_zpos +
             2 * g * ray_ypos + h * pow(ray_zpos, 2) + 2 * i * ray_zpos + j;

  // Calculate the discriminant to determine the number of intersections
  float discriminant = pow(Bq, 2) - 4 * Aq * Cq;
  // float t,t0,t1;
  Hit* hits = 0;

  // If Aq = 0 then there is only one intersection
  if (Aq == 0) {
    float t = -Cq / Bq;  // Calculate the intersetion point

    Hit* hit = new Hit();

    hit->t = t;
    hit->what = this;
    hit->next = 0;

    // Calculate intersection  position
    float x_pos = ray.position.x + t * ray.direction.x;
    float y_pos = ray.position.y + t * ray.direction.y;
    float z_pos = ray.position.z + t * ray.direction.z;
    Vertex position = Vertex(x_pos, y_pos, z_pos);
    hit->position = position;

    // Calculate normals
    float x_normal =
        (a * x_pos + b * y_pos + c * z_pos + d);  // xn = 2(axi + byi + czi + d)
    float y_normal =
        (b * x_pos + e * y_pos + f * z_pos + g);  // yn = 2(bxi + eyi + fzi + g)
    float z_normal =
        (c * x_pos + f * y_pos + h * z_pos + i);  // zn = 2(cxi + fyi + hzi + i)
    Vector normal = Vector(x_normal, y_normal, z_normal);
    hit->normal = normal;
    hit->normal.normalise();
    hits = hit;  // Update the hit pointer
    return hits;
  }
  // Case 2: No real intersections (discriminant < 0)
  else if (discriminant < 0) {
    // return
    return hits;
  }
  // Case 3: Two intersections
  else {
    Hit* first_hit = new Hit();

    // t0 is first intersection t1 is second intersection
    float t1 = (-Bq - sqrt(pow(Bq, 2) - 4 * Aq * Cq)) / 2 * Aq;
    float t2 = (-Bq + sqrt(pow(Bq, 2) - 4 * Aq * Cq)) / 2 * Aq;

    if (t1 == 0 && t2 == 0) {
      hits = 0;  // No intersections
      return hits;
    }

    // Handle the first intersection
    first_hit->t = t1;
    first_hit->what = this;

    // Calculate first intersection position
    float x_pos1 = ray.position.x + t1 * ray.direction.x;
    float y_pos1 = ray.position.y + t1 * ray.direction.y;
    float z_pos1 = ray.position.z + t1 * ray.direction.z;
    Vertex position1 = Vertex(x_pos1, y_pos1, z_pos1);
    first_hit->position = position1;

    // Calculate for first intersection normal
    float x_normal1 = (a * x_pos1 + b * y_pos1 + c * z_pos1 +
                       d);  // xn = 2(axi + byi + czi + d)
    float y_normal1 = (b * x_pos1 + e * y_pos1 + f * z_pos1 +
                       g);  // yn = 2(bxi + eyi + fzi + g)
    float z_normal1 = (c * x_pos1 + f * y_pos1 + h * z_pos1 +
                       i);  // zn = 2(cxi + fyi + hzi + i)
    Vector normal1 = Vector(x_normal1, y_normal1, z_normal1);
    first_hit->normal = normal1;
    first_hit->normal.normalise();

    if (first_hit->normal.dot(ray.direction) > 0.0f) {
      first_hit->normal.negate();
    }
    //
    // First hit is entering
    first_hit->entering = true;

    // Calculate second hit intersection -------
    Hit* second_hit = new Hit();
    second_hit->t = t2;
    second_hit->what = this;

    // Calculate second intersection position
    float x_pos2 = ray.position.x + t2 * ray.direction.x;
    float y_pos2 = ray.position.y + t2 * ray.direction.y;
    float z_pos2 = ray.position.z + t2 * ray.direction.z;
    Vertex position2 = Vertex(x_pos2, y_pos2, z_pos2);
    second_hit->position = position2;

    // Calculate normals for second intersection
    float x_normal2 = 2 * (a * x_pos2 + b * y_pos2 + c * z_pos2 +
                           d);  // xn = 2(axi + byi + czi + d)
    float y_normal2 = 2 * (b * x_pos2 + e * y_pos2 + f * z_pos2 +
                           g);  // yn = 2(bxi + eyi + fzi + g)
    float z_normal2 = 2 * (c * x_pos2 + f * y_pos2 + h * z_pos2 +
                           i);  // zn = 2(cxi + fyi + hzi + i)
    Vector normal2 = Vector(x_normal2, y_normal2, z_normal2);
    second_hit->normal = normal2;
    second_hit->normal.normalise();

    if (second_hit->normal.dot(ray.direction) > 0.0) {
      second_hit->normal.negate();
    }

    // Second hit is NOT entering its leaving
    second_hit->entering = false;

    first_hit->next = second_hit;
    second_hit->next = 0;
    hits = first_hit;  // Update the hit pointer
    return hits;
  }
}

// Apply a transformation to the quadratic object using a 4x4 transformation
// matrix
void Quadratic::apply_transform(Transform& trans) {
  // Compute the transpose of the transformation matrix
  Transform tt = trans.transpose();
  // Create a 4x4 matrix Q with the quadratic coefficients
  Transform Q = Transform(a, b, c, d, b, e, f, g, c, f, h, i, d, g, i, j);

  // Compute the new quadratic matrix by multiplying transposed(trans) * Q *
  // trans
  Transform Qt = Q * trans;
  Transform newQ = tt * Qt;
  // Update the quadratic coefficients with the values from the new matrix
  a = newQ.matrix[0][0];
  a = newQ.matrix[0][0];
  b = newQ.matrix[0][1];
  c = newQ.matrix[0][2];
  d = newQ.matrix[0][3];
  e = newQ.matrix[1][1];
  f = newQ.matrix[1][2];
  g = newQ.matrix[1][3];
  h = newQ.matrix[2][2];
  i = newQ.matrix[2][3];
  j = newQ.matrix[3][3];
}
