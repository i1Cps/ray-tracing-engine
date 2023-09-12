// This is the main demonstration incooperates all the main functionality of my
// ray tracing engine.

// Required files: framebuffer.cpp scene.cpp polymesh_object.cpp
// sphere_object.cpp plane_object.cpp quadratic_object.cpp  csg.cpp
// compound_material.cpp directional_light.cpp phong_material.cpp
// falsecolour_material.cpp global_material.cpp checkered_plane_material.cpp
// checkered_sphere_material.cpp simple_camera.cpp full_camera.cpp hit.cpp
// demonstration5.cpp

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
  uniform_real_distribution<> x(-5.0, 5.0);
  float x_pos = x(gen);
  // uniform_real_distribution<> y(0,3.0);
  uniform_real_distribution<> y(-2, 6.0);
  float y_pos = y(gen);
  // uniform_real_distribution<> z(4,5.0);
  uniform_real_distribution<> z(4, 7.0);
  float z_pos = z(gen);

  Sphere* sphere = new Sphere(Vertex(x_pos, y_pos, z_pos), 1);

  // Generate random RGB colour
  uniform_real_distribution<> rgb(0, 0.2);
  float r = rgb(gen);
  float g = rgb(gen);
  float b = rgb(gen);

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

// Creates a pillar of spheres scene in image
void pillar_sphere(Scene& scene, int amount, float x, float y, float z) {
  for (int i = -1; i < amount; i++) {
    if (i % 3 == 0) {
      Sphere* sphere = new Sphere(Vertex(x, i - 1, z), 1);
      // Generate random RGB colour
      random_device rd;
      mt19937 gen(rd());
      uniform_real_distribution<> rgb(0, 0.2);
      float r = rgb(gen);
      float g = rgb(gen);
      float b = rgb(gen);
      // Create a compound material of global material and either aqua phong or
      // white phong
      CompoundMaterial* sphere_material = new CompoundMaterial(2);
      // Global material with reflection and refraction properties (IOR = 0 sp
      // no refraction)
      GlobalMaterial* global_material = new GlobalMaterial(
          &scene, Colour(0.9f, 0.9f, 0.9f), Colour(0.5f, 0.5f, 0.5f), 0.0f);
      // Phong material for white and aqua colours
      Phong* aqua_phong =
          new Phong(Colour(0.0f, 1.0f, 1.0f) * 0.4, Colour(0.0f, 1.0f, 1.0f),
                    Colour(0.5f, 0.5f, 0.5f), 40.0f);
      Phong* white_phong =
          new Phong(Colour(0.9f, 0.9f, 0.9f) * 0.4, Colour(0.9f, 0.9f, 0.9f),
                    Colour(0.5f, 0.5f, 0.5f), 40.0f);
      Phong* phong_material =
          new Phong(Colour(r, g, b), Colour(r * 2, g * 2, b * 2),
                    Colour(0.5f, 0.5f, 0.5f), 40.f);
      // Alternate pillar spheres so that every other is aqua or white, with an
      // offset per pillar
      sphere_material->include_material(global_material);
      if (i % 2 == 0) {
        if (amount % 20 == 0) {
          sphere_material->include_material(aqua_phong);
        } else {
          sphere_material->include_material(white_phong);
        }
      } else {
        if (amount % 20 == 0) {
          sphere_material->include_material(white_phong);

        } else {
          sphere_material->include_material(aqua_phong);
        }
      }
      sphere->set_material(sphere_material);
      scene.add_object(sphere);
    }
  }
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

  // The following transform allows 4D homogeneous coordinates to be
  // transformed.It moves the supplied teapot model to somewhere visible.
  Transform* transform =
      new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -2.7f, 0.0f, 1.0f,
                    0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

  //  Read in the teapot model. (If your rendering it)
  PolyMesh* pm = new PolyMesh("teapot_smaller.ply", true);
  pm->apply_transform(*transform);

  // Scene objects
  Sphere* sphere1 = new Sphere(Vertex(-4.5f, -1.0f, 3.0f), 1.0f);
  Sphere* sphere2 = new Sphere(Vertex(0.0f, -1.0f, 3.0f), 1.0f);
  Sphere* sphere3 = new Sphere(Vertex(4.5f, -1.0f, 3.0f), 1.0f);
  Sphere* sphere4 = new Sphere(Vertex(0.0f, 2.3f, 5.0f), 2.0f);

  Sphere* big_sphere = new Sphere(Vertex(-1.0f, -1.0f, 3.0f), 3.0f);
  Sphere* big_sphere2 = new Sphere(Vertex(0.0f, -1.0f, 0.0f), 2.0f);

  Sphere* csg_sphere1 = new Sphere(Vertex(-1.0f, 1.0f, 3.0f), 1.8f);
  Sphere* csg_sphere2 = new Sphere(Vertex(0.0f, 1.0f, 3.0f), 1.8f);

  // Loop which generate x amount of currently reflective spheres
  for (int x = 0; x < 0; x++) {
    spawn_sphere(scene);
  }

  // Creates a plane
  Plane* plane = new Plane(0, 1, 0, 2);
  Plane* top_plane = new Plane(0, -1, 0, 10);
  Plane* side_left_plane = new Plane(1, 0, 0, 5.5);
  Plane* side_right_plane = new Plane(1, 0, -0., -5.5);

  // Creates a quadratic object
  Quadratic* quad =
      new Quadratic((1.0f / 9.0f), 0.0f, 0.0f, 0.0f, (1.0f / 16.0f), 0.0f, 0.0f,
                    (1.0f / 25.0f), 0.0f, -0.09);

  // Creates a constructive solid geometry object
  // 0: Union, 1: Difference and 2: Interesection
  Csg* csg = new Csg(csg_sphere1, csg_sphere2, 1);

  // Directional light
  DirectionalLight* dl = new DirectionalLight(Vector(0.0f, -1.0f, 0.0f),
                                              Colour(1.0f, 1.0f, 1.0f, 0.0f));
  // DirectionalLight* dl2 = new DirectionalLight(Vector(1.0f, -1.0f, 0.0f),
  // Colour(1.0f, 1.0f, 1.0f, 0.0f));
  scene.add_light(dl);
  // scene.add_light(dl2);

  // Scene object materials

  // Ambient Scale
  float ambient_scale = 0.5;

  // Below are some example phong materials with different specular colours, for
  // users to try out white specular colour value
  Phong* green_phong =
      new Phong(green * ambient_scale, green, Colour(0.4f, 0.4f, 0.4f), 40.f);
  Phong* white_phong = new Phong(white * ambient_scale * 0.2, white * 0.2,
                                 Colour(0.5f, 0.5f, 0.5f), 40.0f);
  Phong* purple_phong = new Phong(purple * ambient_scale, purple,
                                  Colour(0.5f, 0.5f, 0.5f), 40.0f);
  Phong* orange_phong =
      new Phong(orange * ambient_scale, orange, Colour(0.5f, 0.5f, 0.5f), 40.f);
  Phong* blue_phong = new Phong(blue * ambient_scale * 0.2, blue * 0.2,
                                Colour(0.5f, 0.5f, 0.5f), 40.f);
  // Reflective phong has a scaled down silver colour for its ambient and
  // diffuse colours, this prevents light sources, from interfering with
  // reflections and is a appropriate phong material to match with both
  // reflective and refractive materials
  Phong* reflective_phong =
      new Phong(Colour(0.1f, 0.1f, 0.1f), Colour(0.15f, 0.15f, 0.15f),
                Colour(0.5f, 0.5f, 0.5f), 40.f);
  Phong* glass_phong =
      new Phong(duron_opera_glass * ambient_scale, duron_opera_glass,
                Colour(0.5f, 0.5f, 0.5f), 40.f);

  // The following phong material has a white ambient and diffuse colour, but
  // the specular colour is aqua.
  Phong* white_with_aqua_spec =
      new Phong(white * ambient_scale, white, aqua, 40.f);

  // Below are two global materials, The first ones is a reflective material
  // while the other is a refractive material with some reflection which user
  // can control

  // Here I give mirror a reflective weight of 0.9, means its not perfectly
  // reflective and importanly a IOR value of 0 Which means it has no refraction
  // (Cant see through it)
  GlobalMaterial* reflective_material = new GlobalMaterial(
      &scene, Colour(0.9f, 0.9f, 0.9f), Colour(0.1f, 0.1f, 0.1f), 0.0f);
  // For my transparent glass material it has a refractive weight of 0.9 which
  // means you will be able to almost perfectly fully see through it and it has
  // a IOR value of 1.5f which is the IOR of glass
  GlobalMaterial* transparent_glass = new GlobalMaterial(
      &scene, Colour(0.1f, 0.1f, 0.1f), Colour(0.9f, 0.9f, 0.9f), 1.5f);

  // Create a compound material to add the global and phong materials together
  CompoundMaterial* blue_mirror = new CompoundMaterial(2);
  // Add blue phong material and mirror global material
  blue_mirror->include_material(blue_phong);
  blue_mirror->include_material(reflective_material);


  // Checkered plane material with reflection
  CompoundMaterial* reflective_plane_checker = new CompoundMaterial(2);
  // Checkered plane material
  Checkered_Plane_Material* grey_aqua_square =
      new Checkered_Plane_Material(2.0f, white, aqua, white, white, 40.f);
  // Reflective material

  GlobalMaterial* plane_reflective_material = new GlobalMaterial(
      &scene, Colour(0.3f, 0.3f, 0.3f), Colour(0.1f, 0.1f, 0.1f), 0.0f);
  reflective_plane_checker->include_material(grey_aqua_square);
  reflective_plane_checker->include_material(plane_reflective_material);

  CompoundMaterial* reflective_plane = new CompoundMaterial(2);
  reflective_plane->include_material(white_phong);
  reflective_plane->include_material(plane_reflective_material);

  CompoundMaterial* glass = new CompoundMaterial(2);
  glass->include_material(reflective_phong);
  glass->include_material(transparent_glass);

  // Checkered sphere material
  Checkered_Sphere_Material* sc = new Checkered_Sphere_Material(
      0.05f, black, Colour(0.0f, 0.4f, 0.0f), Colour(0.5f, 0.5f, 0.5f),
      Colour(0.5f, 0.5f, 0.5f), 40.f);
  Checkered_Sphere_Material* sc2 = new Checkered_Sphere_Material(
      0.05f, black, red, white, Colour(0.5f, 0.5f, 0.5f), 40.f);
  Phong* plane_material =
      new Phong(Colour(0.1, 0.1f, 0.1f), Colour(0.1f, 0.1f, 0.1f),
                Colour(0.5f, 0.5f, 0.5f), 40.f);

  for (int i = 0; i < 50; i++) {
    if (i % 10 == 0) {
      pillar_sphere(scene, i * 5, -4.5f, -1.0f, 3.0f + (i - 10));
    }
  }

  for (int i = 0; i < 50; i++) {
    if (i % 10 == 0) {
      pillar_sphere(scene, i * 5, 4.5f, -1.0f, 3.0f + (i - 10));
    }
  }

  // Add materials to objects then add those objects to the scene

  pm->set_material(blue_mirror);
  scene.add_object(pm);

  quad->set_material(purple_phong);
  // scene.add_object(quad);

  sphere1->set_material(orange_phong);
  // scene.add_object(sphere1);

  sphere2->set_material(sc);
  // scene.add_object(sphere2);

  sphere3->set_material(blue_mirror);
  // scene.add_object(sphere3);

  sphere4->set_material(glass);
  scene.add_object(sphere4);

  plane->set_material(reflective_plane_checker);
  scene.add_object(plane);

  side_left_plane->set_material(white_phong);
  scene.add_object(side_left_plane);

  side_right_plane->set_material(white_phong);
  scene.add_object(side_right_plane);

  top_plane->set_material(white_phong);
  // scene.add_object(top_plane);

  csg->set_material(green_phong);
  // scene.add_object(csg);
}

// This is the entry point function to the program.
int main(int argc, char* argv[]) {

  // ADJUST PIXEL NUMBER AND THUS QUALITY HERE-----------------------------
	// Slow computers should use 512x512, ok computers 1024x1024, high end computers; do your thing
  int height = 512;
  int width = 512;
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
  fb->writeRGBFile((char*)"demonstration5.ppm");

  cerr << "\nDone.\n" << flush;

  // a debug check to make sure we don't leak hits.
  cerr << "Hit Pool " << Hit::pool_size << " Allocated " << Hit::allocated
       << "\n"
       << flush;
  return 0;
}
