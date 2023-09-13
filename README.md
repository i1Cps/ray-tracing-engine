<!-- ⚠️ This README has been generated from the file(s) "blueprint.md" ⚠️--><h1 align="center">ray-tracing-engine</h1>
<p align="center">
  <img src="images/picture.png" alt="Logo" width="550" height="auto" />
</p>


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/solar.png)](#table-of-contents)

## ➤ Table of Contents

* [➤ ::pencil:: About The Project](#-pencil-about-the-project)
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

  
**Ray Tracing Engine was built using only C++**
![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=for-the-badge)
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
