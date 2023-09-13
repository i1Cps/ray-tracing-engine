// The PolyMesh Object reads and intersects with triangle meshes

#pragma once

#include "object.h"

typedef int TriangleIndex[3];

class PolyMesh : public Object {
 public:
  int vertex_count;
  int triangle_count;
  Vertex *vertex;
  TriangleIndex *triangle;
  bool smoothing;
  Vector *face_normal;
  Vector *vertex_normals;

  Hit *triangle_intersect(int triangle_num, Ray ray);

  void compute_face_normal(int triangle_num, Vector &normal);
  void compute_vertex_normals();
  bool ray_triangle_intersect(Ray ray, Vector v0, Vector v1, Vector v2,
                              float &t, float &beta, float &gamma);

  Hit *intersection(Ray ray);
  void apply_transform(Transform &trans);

  PolyMesh(char *file, bool smooth);
  ~PolyMesh() {}
};
