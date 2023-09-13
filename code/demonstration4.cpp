// This demonstration showcases the polymesh_object class on a set of dolphins, the dolphin
// pod mesh is rendered twice, one set with a grey material and one with a
// transparent glass material Please note the floor is also a reflective aqua,
// meaning you can see the glass and grey dolphins in the floor

// Required files: framebuffer.cpp scene.cpp polymesh_object.cpp
// sphere_object.cpp plane_object.cpp quadratic_object.cpp  csg.cpp
// compound_material.cpp directional_light.cpp phong_material.cpp
// falsecolour_material.cpp global_material.cpp checkered_plane_material.cpp
// checkered_sphere_material.cpp simple_camera.cpp full_camera.cpp hit.cpp
// demonstration4.cpp

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

  // This transform translates the grey set of dolphins to the middle left of
  // the screen and places them behind the glass dolphins
  Transform* translateTransform1 =
      new Transform(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  // This transform translates the glass set of dolphin to the middle right of
  // the screen
  Transform* translateTransform2 =
      new Transform(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

  // This transform scales the dolphins down in size
  float scale_factor = 0.01f;  // Adjust the scale factor as needed
  Transform* scale_matrix = new Transform(
      scale_factor, 0.0f, 0.0f, 0.0f, 0.0f, scale_factor, 0.0f, 0.0f, 0.0f,
      0.0f, scale_factor, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  // This transform flips the glass dolphins along the x-axis so they face the
  // opposite way from teh grey dolphins
  Transform* reflectionMatrix =
      new Transform(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  // Grey dolphins combined transform
  Transform* combined_transform1 = new Transform();
  *combined_transform1 = (*translateTransform1) * (*scale_matrix);

  // Glass dolhpins combined transform
  Transform* combined_transform2 = new Transform();
  *combined_transform2 =
      (*translateTransform2) * (*scale_matrix) * (*reflectionMatrix);

  //  Read in the grey dolphin model.
  PolyMesh* pm = new PolyMesh("dolphins.ply", true);
  pm->apply_transform(*combined_transform1);

  //  Read in the glass dolphin model.
  PolyMesh* pm2 = new PolyMesh("dolphins.ply", true);
  pm2->apply_transform(*combined_transform2);

  // Creates a 3 planes,  left right and bottom.
  Plane* plane = new Plane(0, 1, 0, 2);
  Plane* side_left_plane = new Plane(1, 0, 0, 5.5);
  Plane* side_right_plane = new Plane(1, 0, -0., -5.5);

  // Directional light
  DirectionalLight* dl = new DirectionalLight(Vector(0.0f, -1.0f, 0.0f),
                                              Colour(1.0f, 1.0f, 1.0f, 0.0f));
  DirectionalLight* dl2 = new DirectionalLight(Vector(1.0f, -1.0f, 0.0f),
                                               Colour(1.0f, 1.0f, 1.0f, 0.0f));
  scene.add_light(dl);
  scene.add_light(dl2);

  Phong* silver_phong =
      new Phong(silver * 0.7, silver * 0.6, Colour(0.6, 0.7, 0.8), 40.0f);

  // Checkered plane material with reflection
  CompoundMaterial* reflective_plane_checker = new CompoundMaterial(2);
  // Reflection
  GlobalMaterial* plane_reflective_material = new GlobalMaterial(
      &scene, Colour(0.3f, 0.3f, 0.3f), Colour(0.1f, 0.1f, 0.1f), 0.0f);
  // Checkered plane material
  Checkered_Plane_Material* grey_aqua_square =
      new Checkered_Plane_Material(2.0f, white, aqua, white, white, 40.f);
  reflective_plane_checker->include_material(grey_aqua_square);
  reflective_plane_checker->include_material(plane_reflective_material);

  // Glass compound material
  CompoundMaterial* glass = new CompoundMaterial(2);

  // For my transparent glass material it has a refractive weight of 0.9 which
  // means you will be able to almost perfectly fully see through it and it has
  // a IOR value of 1.5f which is the IOR of glass
  GlobalMaterial* transparent_glass = new GlobalMaterial(
      &scene, Colour(0.1f, 0.1f, 0.1f), Colour(0.9f, 0.9f, 0.9f), 1.5f);

  // Reflective phong has a scaled down silver colour for its ambient and
  // diffuse colours, this prevents light sources, from interfering with
  // reflections and is a appropriate phong material to match with both
  // reflective and refractive materials
  Phong* reflective_phong =
      new Phong(Colour(0.1f, 0.1f, 0.1f), Colour(0.15f, 0.15f, 0.15f),
                Colour(0.5f, 0.5f, 0.5f), 40.f);

  glass->include_material(reflective_phong);
  glass->include_material(transparent_glass);

  // Reflection aqua material
  CompoundMaterial* aqua_reflect_plane = new CompoundMaterial(2);

  // Reflective weight of 0.9, means its not perfectly
  // reflective and importanly a IOR value of 0 Which means it has no refraction
  // (Cant see through it)
  GlobalMaterial* reflective_material = new GlobalMaterial(
      &scene, Colour(0.9f, 0.9f, 0.9f), Colour(0.5f, 0.5f, 0.5f), 0.0f);

  // Aqua Phong plane material
  Phong* aqua_phong =
      new Phong(Colour(0.0f, 1.0f, 1.0f) * 0.4, Colour(0.0f, 1.0f, 1.0f),
                Colour(0.5f, 0.5f, 0.5f), 40.0f);

  aqua_reflect_plane->include_material(reflective_material);
  aqua_reflect_plane->include_material(aqua_phong);

  // Add materials to objects then add those objects to the scene
  pm->set_material(silver_phong);
  scene.add_object(pm);

  pm2->set_material(glass);
  scene.add_object(pm2);

  plane->set_material(aqua_reflect_plane);
  scene.add_object(plane);

  side_left_plane->set_material(reflective_plane_checker);
  scene.add_object(side_left_plane);

  side_right_plane->set_material(reflective_plane_checker);
  scene.add_object(side_right_plane);
}

// This is the main function that generates the Framebuffer, and camera
int main(int argc, char* argv[]) {
  // ADJUST PIXEL NUMBER AND THUS QUALITY HERE <--------------------------------
  // Slow computers should use 512x512, ok computers 1024x1024, high end
  // computers; do your thing
  int height = 512;
  int width = 512;

  // Create a Framebuffer
  FrameBuffer* fb = new FrameBuffer(width, height);

  // Create a scene
  Scene scene;
  // Setup the scene
  build_scene(scene);

  // Declare a camera
  Vertex camPos = Vertex(0.0f, 0.0f, -4.0f);
  Vector camLookAt = Vector(0.0f, 0.0f, 1.0f);
  Vector camUp = Vector(0.0f, 1.0f, 0.0f);
  Camera* camera = new FullCamera(0.5f, camPos, camLookAt, camUp);

  // Camera generates rays for each pixel in the framebuffer and records colour
  // + depth.
  camera->render(scene, *fb);

  // Output the framebuffer colour
  fb->writeRGBFile((char*)"demonstration4.ppm");

  cerr << "\nDone.\n" << flush;

  // a debug check to make sure we don't leak hits.
  cerr << "Hit Pool " << Hit::pool_size << " Allocated " << Hit::allocated
       << "\n"
       << flush;
  return 0;
}
