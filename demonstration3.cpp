// This is the main demonstration incooperates all the main functionality of my
// ray tracing engine.

// Required files: framebuffer.cpp scene.cpp polymesh_object.cpp
// sphere_object.cpp plane_object.cpp quadratic_object.cpp  csg.cpp
// compound_material.cpp directional_light.cpp phong_material.cpp
// falsecolour_material.cpp global_material.cpp checkered_plane_material.cpp
// checkered_sphere_material.cpp simple_camera.cpp full_camera.cpp hit.cpp
// demonstration3.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// These are core raytracing classes
#include "framebuffer.h"
#include "scene.h"

// Classes that contain our objects to be rendered, all derived from Object
#include "csg.h"
#include "plane_object.h"
#include "polymesh_object.h"
#include "quadratic_object.h"
#include "sphere_object.h"

// Classes that contain our lights, all derived from Light
#include "directional_light.h"

// Classes that contain the materials applied to an object, all derived from
// Material
#include "checkered_plane_material.h"
#include "checkered_sphere_material.h"
#include "compound_material.h"
#include "falsecolour_material.h"
#include "global_material.h"
#include "phong_material.h"

// Classes that contain cameras, all derived from Camera
#include <cstdlib>
#include <random>

#include "full_camera.h"
#include "simple_camera.h"

// Using namespace std;

// This function creates and adds to the scene a sphere with random coordinates
// in the space x(-5.0,5.0), y(-2.0,6.0), z(3.0,6.0) as well as a random rgb
// colour all spheres have radius 1
void spawn_sphere(Scene& scene) {
  random_device rd;
  mt19937 gen(rd());

  // uniform_real_distribution<> x(-3,3.0);
  uniform_real_distribution<> x(-9.0, 9.0);
  float x_pos = x(gen);
  // uniform_real_distribution<> y(0,3.0);
  uniform_real_distribution<> y(-2, 8.0);
  float y_pos = y(gen);
  // uniform_real_distribution<> z(4,5.0);
  uniform_real_distribution<> z(1, 10.0);
  float z_pos = z(gen);

  Sphere* sphere = new Sphere(Vertex(x_pos, y_pos, z_pos), 1);

  // Generate random RGB colour
  uniform_real_distribution<> rgb(0, 0.2);
  float r = rgb(gen) * 8;
  float g = rgb(gen) * 8;
  float b = rgb(gen) * 8;

  // Compound material (combines multiple materials) for sphere
  CompoundMaterial* sphere_material = new CompoundMaterial(2);

  // Phong adds ambient, diffuse and specular lighting
  Phong* phong_material =
      new Phong(Colour(r, g, b), Colour(r * 2, g * 2, b * 2),
                Colour(0.5f, 0.5f, 0.5f), 40.f);
  sphere_material->include_material(phong_material);

  // Global material that adds reflection and refraction, ior set to 0.0 meaning
  // no refraction
  GlobalMaterial* global_material = new GlobalMaterial(
      &scene, Colour(0.9f, 0.9f, 0.9f), Colour(0.5f, 0.5f, 0.5f), 0.0f);
  sphere_material->include_material(global_material);

  sphere->set_material(sphere_material);
  scene.add_object(sphere);
}

void build_scene(Scene& scene) {
  // Several Template colours

  Colour red = Colour(1.0f, 0.0f, 0.0f);
  Colour green = Colour(0.0f, 1.0f, 0.0f);
  Colour blue = Colour(0.0f, 0.0f, 1.0f);
  Colour yellow = Colour(1.0f, 1.0f, 0.0f);
  Colour aqua = Colour(0.0f, 1.0f, 1.0f);
  Colour purple = Colour(1.0f, 0.0f, 1.0f);
  // Not perfectly white
  Colour white = Colour(0.9f, 0.9f, 0.9f);
  // Not perfectly black
  Colour black = Colour(0.1, 0.1, 0.1);
  Colour orange = Colour(0.92, 0.504, 0.136);
  Colour gold = Colour(1.0f, 0.78f, 0.0f);
  Colour silver = Colour(0.39, 0.39, 0.39);
  Colour duron_opera_glass = Colour(0.9647f, 0.9961f, 1.0f);

  // Loop which generate x amount of currently reflective spheres
  for (int x = 0; x < 53; x++) {
    spawn_sphere(scene);
  }

  // Creates a plane
  Plane* plane = new Plane(0, 1, 0, 2);

  // Directional light
  DirectionalLight* dl = new DirectionalLight(Vector(0.0f, -1.0f, 0.0f),
                                              Colour(1.0f, 1.0f, 1.0f, 0.0f));
  DirectionalLight* dl2 = new DirectionalLight(Vector(1.0f, -1.0f, 0.0f),
                                               Colour(1.0f, 1.0f, 1.0f, 0.0f));
  scene.add_light(dl);
  scene.add_light(dl2);

  // Ambient Scale
  // float ambient_scale = 0.5;

  // Below is a white phong

  Phong* white_phong =
      new Phong(white * 1.5, white * 0.9, Colour(0.5f, 0.5f, 0.5f), 80.0f);

  // Compound Checkered plane material with reflection
  CompoundMaterial* reflective_plane = new CompoundMaterial(2);

  // relfective plane material
  GlobalMaterial* plane_reflective_material = new GlobalMaterial(
      &scene, Colour(0.3f, 0.3f, 0.3f), Colour(0.1f, 0.1f, 0.1f), 0.0f);

  reflective_plane->include_material(white_phong);
  reflective_plane->include_material(plane_reflective_material);

  // Add materials to objects then add those objects to the scene

  plane->set_material(reflective_plane);
  scene.add_object(plane);
}

// This is the entry point function to the program.
int main(int argc, char* argv[]) {
  // ADJUST PIXEL NUMBER AND THUS QUALITY HERE-----------------------------
  // Slow computers should use 512x512, ok computers 1024x1024, high end
  // computers; do your thing
  int height = 2048;
  int width = 2048;
  //  Create a framebuffer
  FrameBuffer* fb = new FrameBuffer(width, height);

  // Create a scene
  Scene scene;
  // Setup the scene
  build_scene(scene);

  // Declare a camera
  // my suttin dey
  // Vertex camPos = Vertex(-1.0f, 0.0f, 0.0f);
  Vertex camPos = Vertex(0.0f, 0.0f, -4.0f);
  Vector camLookAt = Vector(0.0f, 0.0f, 1.0f);
  Vector camUp = Vector(0.0f, 1.0f, 0.0f);
  Camera* camera = new FullCamera(0.5f, camPos, camLookAt, camUp);

  // Camera generates rays for each pixel in the framebuffer and records colour
  // + depth.
  camera->render(scene, *fb);

  // Output the framebuffer colour and depth as two images
  fb->writeRGBFile((char*)"demonstration3.ppm");
  fb->writeDepthFile((char*)"demonstration3_depth.ppm");

  cerr << "\nDone.\n" << flush;

  // a debug check to make sure we don't leak hits.
  cerr << "Hit Pool " << Hit::pool_size << " Allocated " << Hit::allocated
       << "\n"
       << flush;
  return 0;
}
