CUDA Path Tracer
================

**University of Pennsylvania, CIS 565: GPU Programming and Architecture, Project 3**

* Janet Wang [website](https://xchennnw.github.io/en.github.io/)
* Tested on: Windows 11, i7-12700H @ 2.30GHz 16GB, Nvidia Geforce RTX 3060 Ti  8054MB

Sample scene

<img width="600" alt="1" src="img/4.png">


Open Scene

<img width="600" alt="1" src="img/1.png">

Closed scene

<img width="600" alt="2" src="img/2.png">


## Features
* Materials (Diffuse, Perfect Specular, Refraction, Glass, Plastic)
* Direct lighting (A full lighting Integrator)
* OBJ mesh loading & BVH
* Stratified sampling for random number sequences

### Materials
<img width="600" alt="3" src="img/3.png">

| Diffuse             | Perfect Specular    | Pure refraction   |    Plastic        |        Glass      |
| ------------------- | ------------------- | ----------------- | ----------------- |------------------ |
| ![](img/diff.png)   | ![](img/spec.png)   | ![](img/refr.png) | ![](img/plas.png) | ![](img/glass.png)|

Glass = 50% chance of refraction + 50% chance of reflection (With Fresnel dielectric evaluation).

Plastic = 50% chance of diffuse + 50% chance of reflection (With Fresnel dielectric evaluation).




###  Direct lighting (A full lighting Integrator)
At first, I added a kernal to compute the direct lighting for each bounce in each path. And then I added a full integrator which combines the direct lighting and global illumination. For optimization, I added Russian roulette to give some chance to terminate the paths that have relatively low light throughput. Compared with the naive method, it renders a more converged image in a shorter period of time. 

In the future, implementing an MIS sampling would further improve the performance of this part, especially if a more complex material system with various roughness is added.
| Only direct lighting    | Full lighting       |
| ----------------------- | ------------------- |
| ![](img/dl.png)         |   ![](img/full.png) |

Same scene at 30 iterations:
| Naive Integrator        | Full lighting Integrator|
| ----------------------- | ----------------------- |
| ![](img/dl_off.png) | ![](img/dl_on.png)     |




### Obj Mesh Loading (with bounding box or BVH)
I use the tinyObj for parsing and loading the obj format meshes. After meshed are loaded, a list containing all the triangles in the scene is transported to GPU for intersection computing.
To accelerate the intersection process, I added a BVH structure. It is constructed on CPU, and then a list of BVH nodes and a list of index of triangles used by BVH nodes are transported to GPU. As expected, it improves some of the intersection performance. If BVH is turned off, the meshes will still be culled by bounding boxes.
This test was under VS Debug mode and thus it was quite slow. (I just realized I should use VS Release mode, but exceptions occured when transfering to Release mode and still working on fixing it...)

<img width="400" alt="1" src="img/bvh_test.png">

<img width="300" alt="1" src="img/bvh.png">

|                                  | Without BVH             |With BVH                 |
| -----------------------          | ----------------------- | ----------------------- |
|     Average Time Per Frame (ms)  | ~59000              |~43000                       |




### Stratified sampling
Images below show the 1st iteration of the wahoo scene. Actually the improvement is not quite obvious.
| Without Stratified sampling | With Stratified sampling (20 x 20)|
| --------------------------- | --------------------------------- |
| ![](img/no_stra.png)        | ![](img/stra.png)                 |




## Reference
* [PBRT book] (https://www.pbr-book.org/3ed-2018/contents)
* CIS 461 Homeworks
* https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/
