#include "polymesh_object.h"

#include <math.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Contructs a polymesh object from .ply file, assumes .ply file has 3 lines of meta data (title, vertexCount, triangleCount)
PolyMesh::PolyMesh(char* file, bool smooth) {
#include <fstream>
  std::ifstream infile(file);

#include <sstream>
#include <string>
  std::string line;

  // File meta data
  std::string title;
  std::string word1;
  std::string word2;
  int vertexCount = 0;
  int triangleCount;
  smoothing = smooth;

  // Read the first 3 lines of the PLY file and extract relevant data
  for (int lineIndex = 0; lineIndex < 3; lineIndex++) {
    std::getline(infile, line);           // Read a line from the file
    std::istringstream lineStream(line);  // Create a stream for line parsing

    if (title.empty()) {
      lineStream >> title;  // Assign the PLY file title
    } else if (vertexCount == 0) {
      lineStream >> word1 >> word2 >>
          vertexCount;  // Assign vertex count
    } else {
      lineStream >> word1 >> word2 >>
          triangleCount;  // Assign triangle count
    }
  }

  // Store as Polymesh properties    
  vertex_count = vertexCount;
  triangle_count = triangleCount;

  std::cout << "vertex count: " << vertexCount << std::endl;
  std::cout << "face count: " << triangleCount << std::endl;

  // Initialise vertex array
  vertex = new Vertex[vertex_count];

  // Get the stored vertex values from the .ply file
  for (int i = 0; i < vertex_count + 3; i++) {
    // This makes sure to ignore the meta data in the .ply file
    if (i > 2) {
      std::getline(infile, line); // Read a line from the file
      std::istringstream iss(line); // Create a stream for line parsing
      // Process vertex numbers
      float x, y, z;
      iss >> x >> y >> z;
      vertex[i - 3].x = x;
      vertex[i - 3].y = y;
      vertex[i - 3].z = z;
    }
  }
  // prints vertex array
  /* if (false) {
    for (int a = 0; a < vertex_count; a++) {
      std::cout << vertex[a].x;
      std::cout << vertex[a].y;
      std::cout << vertex[a].z << std::endl;
    }
  } */
  // Initialise triangle array and face_normal array
  triangle = new TriangleIndex[triangle_count];
  face_normal = new Vector[triangle_count];

  // Get stored face values
  for (int i = 0; i < triangle_count + 3 + vertex_count; i++) {
    // Skip all the meta data and vertex data
    if (i > (2 + vertex_count)) {
      std::getline(infile, line); // Read a line from the file
      std::istringstream iss(line); // Create a stream for line parsing
      // Process face numbers
      float face;
      float x, y, z;
      iss >> face >> x >> y >> z;
      // Using the face value as the index of the triangle array, set the value to a new array of verticies defined in the .ply file
      triangle[i - 3 - vertex_count][0] = x;
      triangle[i - 3 - vertex_count][1] = y;
      triangle[i - 3 - vertex_count][2] = z;

      // Compute face normals
      int index = i - 3 - vertex_count;
      compute_face_normal(index, face_normal[index]);
    }
  }

  // Compute vertex normals to apply smoothing
  if (smoothing) {
    vertex_normals = new Vector[vertex_count];
    compute_vertex_normals();
  } else {
    vertex_normals = 0;
  }
  // prints triangles
  /* if (false) {
    for (int c = 0; c < triangle_count; c++) {
      std::cout << triangle[c][0] << " ";
      std::cout << triangle[c][1] << " ";
      std::cout << triangle[c][2] << " ";
      std::cout << std::endl;
    }
  } */
  next = 0;
}

// Calculates the normals of each vertex of each triangle
// Because the vertex normals are calcualted per triangle, we can append all the faces surrounding the vertex and normalise for a weighted average
void PolyMesh::compute_vertex_normals() {
  // Loop for each triangle
  for (int i = 0; i < triangle_count; i++) {
    // Loop for each vertex of triangle
    for (int j = 0; j < 3; j++) {
      // append face normal
      vertex_normals[triangle[i][j]] =
          vertex_normals[triangle[i][j]] + face_normal[i];
    }
  }

  // Loop over each vertex normals and normalise to get the weighted average
  for (int k = 0; k < vertex_count; k++) {
    vertex_normals[k].normalise();
  }
}

// Calculates the face normal
void PolyMesh::compute_face_normal(int triangle_num, Vector& normal) {
  // Get vertex index from triangle number
  int v0_index = triangle[triangle_num][0];
  int v1_index = triangle[triangle_num][1];
  int v2_index = triangle[triangle_num][2];

  // Get position vector for each vertex
  Vector v0 = vertex[v0_index];
  Vector v1 = vertex[v1_index];
  Vector v2 = vertex[v2_index];

  // Basic vector math to get normal
  Vector v0v1 = v1 - v0;
  Vector v0v2 = v2 - v0;
  normal = normal.better_cross(v0v1, v0v2);
  normal.normalise();
}

// Calculate whether ray intersects a triangle on mesh using barycentric coordinate system
bool PolyMesh::ray_triangle_intersect(Ray ray, Vector v0, Vector v1, Vector v2,
                                      float& t, float& beta, float& gamma) {
  float a = v0.x - v1.x, b = v0.x - v2.x, c = ray.direction.x,
        d = v0.x - ray.position.x;
  float e = v0.y - v1.y, f = v0.y - v2.y, g = ray.direction.y,
        h = v0.y - ray.position.y;
  float i = v0.z - v1.z, j = v0.z - v2.z, k = ray.direction.z,
        l = v0.z - ray.position.z;

  float m = (f * k) - (g * j), n = (h * k) - (g * l), p = (f * l) - (h * j);
  float q = (g * i) - (e * k), s = (e * j) - (f * i);
  float inv_denom = 1.0 / ((a * m) + (b * q) + (c * s));

  float e1 = (d * m) - (b * n) - (c * p);
  beta = e1 * inv_denom;

  if (beta < 0.0) {
    return false;
  }

  float r = e * l - h * i;

  float e2 = a * n + d * q + c * r;
  gamma = e2 * inv_denom;

  if (gamma < 0.0) {
    return false;
  }
  if (beta + gamma > 1.0) {
    return false;
  }

  float e3 = a * p - b * r + d * s;
  t = e3 * inv_denom;

  if (t < 0) {
    return false;
  }

  // If we reach this point it means the intersection is within the triangle
  return true;
}

// Calculate the hit properties of the intersection if it exists within a triangle
Hit* PolyMesh::triangle_intersect(int triangle_num, Ray ray) {
  float ndotdir = face_normal[triangle_num].dot(ray.direction);
  if (fabs(ndotdir) < 0.000000001f) {
    // Ray is parallel to triangle so does not intersect
    return 0;
  }

  float t, gamma, beta;
  bool flag = ray_triangle_intersect(
      ray, vertex[triangle[triangle_num][0]], vertex[triangle[triangle_num][1]],
      vertex[triangle[triangle_num][2]], t, beta, gamma);
  if (flag == false) return 0;

  Hit* hit = new Hit();
  // The t property is the distance variable for the hit
  hit->t = t;
  // The what property is the object thats been hit
  hit->what = this;
  // The position property is....
  hit->position = ray.position + t * ray.direction;

  // If smoothing is availableuse beta and gamma from the barycentric coordinate system to calculate the hit normal based on the vertex normals
  if (smoothing) {
    hit->normal =
        (1 - beta - gamma) * vertex_normals[triangle[triangle_num][0]] +
        beta * vertex_normals[triangle[triangle_num][1]] +
        gamma * vertex_normals[triangle[triangle_num][2]];
  } else {
    hit->normal = face_normal[triangle_num];
  }

  hit->normal.normalise();

  // Make sure ray direction and hit normal are not pointing the same direction
  if (hit->normal.dot(ray.direction) > 0.0) {
    hit->normal.negate();
  }

  return hit;
}

// Checks for hits from an input ray
Hit* PolyMesh::intersection(Ray ray) {
  Hit* hits = 0;
  // Loop through every triangle and check for hits
  float kEpsilon = 0.01;
  for (int z = 0; z < triangle_count; z++) {
    Hit* hit = triangle_intersect(z, ray);

    // If there exists a hit on trinagle z
    if (hit != 0) {
      // If hit array is not empty
      if (hits != 0) {
        // Basic double linked list array logic, order is based on t property of the hit
        Hit* step = hits;
        Hit* prev = 0;
        while (step != 0) {
          if (hit->t < step->t) {
            // if the new hit is in front of the current step, it inserts before
            // it.
            hit->next = step;
            if (prev != 0) {
              prev->next = hit;
            } else {
              hits = hit;
            }
            break;
          }
          prev = step;
          step = step->next;
        }

        if (step == 0) {
          // Hit if bigger than step, insert it afterwards
          prev->next = hit;
          hit->next = 0;
        }
      } else {
        hit->next = 0;
        hits = hit;
      }
    }
  }

  Hit* temp = hits;
  bool entering = true;

  // Assert correct enetering property on all the hits in the hit array
  while (temp != 0) {
    temp->entering = entering;
    entering = !entering;
    temp = temp->next;
  }

  return hits;
}

// Applies 3D transformation matrix to polymesh using 4D homogenous coordinates
void PolyMesh::apply_transform(Transform& trans) {
  // Transform the vertex points
  for (int a = 0; a < vertex_count; a++) {
    trans.apply(vertex[a]);
  }

  // We compute transformed normals by applying inverse transpose matrix
  Transform ti = trans.inverse().transpose();

  // Smoothing is enabled on polymesh object, transform the vertex_normals
  if (smoothing) {
    for (int i = 0; i < vertex_count; i += 1) {
      ti.apply(vertex_normals[i]);
    }
  }

  // Else just transform the face normals
  for (int i = 0; i < triangle_count; i += 1) {
    ti.apply(face_normal[i]);
  }
  return;
}
