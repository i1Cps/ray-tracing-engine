<!-- ⚠️ This README has been generated from the file(s) "blueprint.md" ⚠️--><h1 align="center">ray-tracing-engine</h1>
<p align="center">
  <img src="images/picture.png" alt="Logo" width="550" height="auto" />
</p>


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#table-of-contents)

## ➤ Table of Contents

* [➤ ::pencil:: About The Project](#-pencil-about-the-project)
* [➤ Demonstration 1](#-demonstration-1)
* [➤ Demonstration 2](#-demonstration-2)
* [➤ Demonstration 3](#-demonstration-3)
* [➤ Demonstration 4](#-demonstration-4)
		* [Spherical Pillars](#spherical-pillars)
		* [Checkered Floor](#checkered-floor)
		* [Tea Pot](#tea-pot)
		* [Scene Inversion Through Glass Ball](#scene-inversion-through-glass-ball)
		* [Artistic Interpretation](#artistic-interpretation)
* [➤ :floppy_disk: Key Project File Descriptions](#-floppy_disk-key-project-file-descriptions)
	* [CORE FILES:](#core-files)
	* [Ray Tracing Files:](#ray-tracing-files)
	* [Materials](#materials)
* [➤ :rocket: Dependencies](#-rocket-dependencies)
* [➤ :coffee: Buy me a coffee](#-coffee-buy-me-a-coffee)
* [➤ :scroll: Credits](#-scroll-credits)
* [➤ License](#-license)



[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#pencil-about-the-project)

## ➤ ::pencil:: About The Project


The Ray Tracing Engine is an ambitious project that delves into the fascinating realm of advanced computer graphics. This project showcases an intricate interplay of mathematics, physics, and programming to create stunning visual effects using ray tracing techniques. It explores the fundamental concepts of reflection and refraction, implementing complex calculations based on Snell's law and the index of refraction to achieve realistic material interactions. The engine's capabilities extend to handling complex geometries, thanks to its support for Constructive Solid Geometry (CSG) and rendering detailed 3D models converted from .ply files into polygon meshes. Moreover, the project demonstrates an understanding of optical phenomena like total internal reflection, leveraging them to craft visually captivating scenes. Dive into the computer graphics world and explore this ray-tracing marvel's inner workings.


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#demonstration-1)

## ➤ Demonstration 1

![picture](/images/demonstration1.png)

This demonstration outputs a circle of 32 lines pointing away from the middle of the image at (256,256) on a 512x512 screen. Its primary focus is to showcase basic utility of the framebuffer class. Users can use the linedrawer.cpp file to output any length stroke to the FrameBuffer and thus draw nearly any 2D image. (The functionality is similar to the [HTML Canvas stroke method](https://www.w3schools.com/jsref/canvas_stroke.asp)). However, this is far from what the Ray Tracing Engine was designed for and should be viewed as nothing but a simple demonstration to visualise what the FrameBuffer does.

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#demonstration-2)

## ➤ Demonstration 2

![picture](/images/demonstration2.png)

This demonstration loads and draws a triangle mesh object from the `teapot_smaller.ply` file. It first creates a 1024x1024 framebuffer before defining a 4D homogeneous transform matrix. Next, the file reads in the .ply file and applies the transform matrix. Then, for each vertex on every triangle, it performs a projection from 3D space to 2D space, resulting in 2D screen coordinates (x,y). Lastly, it uses the draw_line function to draw each line connecting the points on each triangle to complete the mesh. This is a quick, simple demonstration of the polymesh class.

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#demonstration-3)

## ➤ Demonstration 3

![picture](/images/demonstration3.png)

This demonstration spawns 53 reflective shiny balls randomly in the scene using uniform distribution. The rays in this scene recursively reflect up to 5 times, meaning you can see up to 3 mirror worlds. The spheres themselves have a radius of 1 and are made using a [`compound_material`]() that includes the [`global_material`]() and the [`phong_material`](). The reflect weight of the `global_material` is set to 0.9, mimicking that of a mirror. While the RGB values from the `phong_material` are created randomly, using a uniform distribution. The scene contains 2 directional lights and a reflective white plane with a reflection weight of 0.3.

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#demonstration-4)

## ➤ Demonstration 4

![picture](/images/demonstration4.png)

This demonstration showcases the full capabilities of the [`polymesh_object`]() class using a PolyMesh of a pod of dolphins. The pod of dolphins are rendered twice. One set was created with a grey [`phong_material`]() and the other with a transparent glass [`global_material`](). The two side planes use the [`checkered_plane_material`]() class to add colour to the scene, while the floor plane is a reflective aqua using the [`compound_material`]() to amplify the enchanting ambience of the scene even more.

Two independent transform matrices are used on the two polymesh_objects. The first centers the grey dolphins towards the middle of the camera and pushes them back along the z-axis. While the second centers the glass dolphins but flips them along its y-axis to face the opposite direction, it brings them closer to the camera to better show off the transparency effect.

The transparent glass on the dolphins has a refractive weight of 0.9 with an [Index of Refraction](https://en.wikipedia.org/wiki/List_of_refractive_indices) of 1.5, representing real glass. I lowered its reflective weight to 0.1. But the [Fresnel Equation](https://en.wikipedia.org/wiki/Fresnel_equations) refactors the weight between refraction and reflection based on the [Index of Refraction](https://en.wikipedia.org/wiki/List_of_refractive_indices) anyway.

**## Demonstration 5**

![picture](/images/demonstration5.png)

  

This demonstration showcases 95% of the capabilities of the Ray Tracing Engine. The [`demonstration5`]() file has every feature offered by the Ray Tracing Engine coded down (making it quite messy), so please continue to read here to see how I generated this image.

#### Spherical Pillars
Lets start with the pillars. The pillars are generated with shiny reflective balls that alternate between aqua and white (they look grey because of the lighting). They all have a reflective weight of 0.9 and offset each other by 1 each pillar.

  
#### Checkered Floor
The floor plane is checkered aqua and white with a reflective weight of 0.3.

  
#### Tea Pot

The teapot PolyMesh is created with the smooth property (uses vertex normals instead of face normals). And is created with a [`compound_material`]() that contains a blue [`phong_material`]() and [`global_material`]() with a reflective weight of 0.9.


#### Scene Inversion Through Glass Ball

Lastly, we have a giant glass ball:


In the real world, when you look through a large glass sphere or any convex lens, the refraction of light can lead to the inversion or flipping of the image behind it. This intriguing phenomenon occurs because different rays of light from a single point on an object converge after passing through the lens, causing the brain to perceive the image as reversed.


I gave the glass ball an [Index of Refraction](https://en.wikipedia.org/wiki/List_of_refractive_indices) of 1.5. This number contributes to the [Total Inter Refraction](https://en.wikipedia.org/wiki/Total_internal_reflection) causing this beautiful effect.

#### Artistic Interpretation

I chose to name this scene "Open Your Eyes" to draw a parallel between reflections and the mesmerising visual illusion crafted by the spherical pillars on either side of the screen. These pillars conjure the sensation of gradually closing human eyes as they recede into the distance.


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#floppy_disk-key-project-file-descriptions)

## ➤ :floppy_disk: Key Project File Descriptions

  **Theres alot of C++ files in the engine so I wont cover all of them, but some key files include:**

### CORE FILES:

*  **[`framebuffer.cpp`](src/start_rl_environment/description/robot_core.xacro):** Contains the implementation of the `FrameBuffer` class, which is a fundamental part of the Ray Tracing Engine project. This class manages the pixel data used to create images. It provides various functions for setting pixel colours and depths, retrieving pixel information, and saving the rendered image to files in the PPM format.

*  **[`full_camera.cpp`](src/start_rl_environment/description/lidar.xacro):** Contains the implementation of the `FullCamera` class, a crucial component of the Ray Tracing Engine project. This class represents a virtual camera used to capture scenes from a specific viewpoint. The `FullCamera` class generates rays that simulate the path of light from the camera through each pixel on the screen to the scene objects. It accomplishes this by calculating camera coordinate vectors and using them to determine the direction of rays for each pixel. These rays are then used for rendering the scene via ray tracing.

* **[`scene.cpp`](...):** The scene file is another crucial component of the Ray Tracing Engine. It's responsible for managing the scene's objects and lights and enabling the rendering of realistic images. It handles tasks such as tracing rays through the scene to determine the closest intersections with objects, considering factors like shadows, materials, and lighting contributions. This module plays a pivotal role in the overall functionality of the engine, serving as the core scene management system that facilitates the creation of visually compelling images through the simulation of light-object interactions.

### Ray Tracing Files:

*  **[`hit.cpp`]():** This file encapsulates the functionality of the `Hit` class, which serves as a container to store and manipulate information about intersections between rays and objects within the scene. This file includes custom memory allocation and deallocation operators to efficiently manage memory for `Hit` objects. Each `Hit` has 6 crucial properties for rendering accurate models. 1. **`t`**, This value represents the intersection distance from the camera lens; the whole engine is built around the condition of this number. 2. **`entering`** This property lets us know whether a light ray is entering an object or leaving it. 3. **`next`** allows us to have a linked list of `Hits` for each ray we calculate. 4. **`position`** is the position of the intersection and is used to calculate reflection and refraction on materials. 5. The **`normal`** at the point of intersection is the most important vector whenever light is involved. (which is nearly always)

*  **[`polymesh_object.cpp`](src/start_rl_environment/launch/start_robots.launch.py):** This file is fundamental for working with complex 3D models. It reads [PLY](https://en.wikipedia.org/wiki/PLY_(file_format)) files, extracting vertex and triangle data, which can then be checked for intersections or `Hits` with input rays. Since poly meshes are made of triangles, we call this method `ray triangle intersection`, and we compute the properties of these `Hits` with [barycentric coordinates](https://en.wikipedia.org/wiki/Barycentric_coordinate_system). One important property of every `Hit` is it's **normal**. The accuracy of a `Hits` normal helps us output more realistic lighting models. The `polymesh_object` class also allows us to render smooth poly meshes, which can be achieved by calculating vertex normal's instead of face normal's.


### Materials

* **[`global_material`]():** This file defines the GlobalMaterial class, which handles reflection, refraction, and lighting computations. It provides 3 main functions: The first function is the refract_ray function, Which calculates a refraction ray and further calculates if [total inter reflection](https://en.wikipedia.org/wiki/Total_internal_reflection) occurs. This calculation involves a derivation of Snell's formula alongside the materials [index of refraction](https://en.wikipedia.org/wiki/List_of_refractive_indices). The second is the Fresnel function, which uses [Fresnels equation](https://en.wikipedia.org/wiki/Fresnel_equations) to calculate the ratio of reflected and refracted light for a ray on a transparent reflective material. Lastly, we have the compute_once function, a recursive function to handle reflected rays bouncing around the scene. It has a recurse variable which details the maximum number of times each ray can be reflected.

* **[`phong_material`]():** This file defines the PhongMaterial class. It's a simple Phong-based lighting model containing ambient, diffuse and specular lighting. The diffuse and specular properties are engineered to recursively reflect other light; Diffuse literally diffuses incoming light rays, independent of the viewing angle and proportional to the cosine of the angle of incidence,  before reflecting. Specular will only reflect light rays in a specific direction, meaning it can only be viewed when the reflection ray points towards the eye (camera in our case).



  


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#rocket-dependencies)

## ➤ :rocket: Dependencies

  
**Ray Tracing Engine was built using only:**

![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=for-the-badge)
 ## ➤ :hammer: Basic Installation

 **Download the workspace**

```
git clone https://github.com/i1Cps/ray-tracing-engine.git

cd ray-tracing-engine

```

**And your ready to start using the engine**


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#coffee-buy-me-a-coffee)

## ➤ :coffee: Buy me a coffee
Whether you use this project, have learned something from it, or just like it, please consider supporting it by buying me a coffee, so I can dedicate more time on open-source projects like this (҂⌣̀_⌣́)

<a href="https://www.buymeacoffee.com/i1Cps" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-violet.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>



[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#scroll-credits)

## ➤ :scroll: Credits

Theo Moore-Calters 


[![GitHub Badge](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/i1Cps) [![LinkedIn Badge](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](www.linkedin.com/in/theo-moore-calters)


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#license)

## ➤ License
	
Licensed under [MIT](https://opensource.org/licenses/MIT).
