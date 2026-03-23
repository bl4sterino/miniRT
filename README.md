*This project has been created as part of the 42 curriculum by tpotier and pberne.*

# miniRT

A minimal Path Tracer developed in C

## Description

miniRT is a project from the 42 School Common Core that introduces the fundamental concepts of Ray Tracing and 3D computer graphics. The goal is to generate realistic images by simulating the physical behavior of light.

Unlike rasterization (used in most real-time games), this engine casts rays from a virtual camera through each pixel into a 3D scene, calculating intersections with objects and determining the final color based on:

* **Geometric Intersections:** Analytical solutions for Spheres, Planes, Quads, Triangles, Cylinders and Ellipsoids
* **The Phong Reflection Model:** Implementing Ambient, Diffuse, and Specular lighting.

* **Shadows:** Checking for obstructions between the hit point and light sources.

## Prerequistes

MiniLibX for Linux requires xorg, x11 and zlib, therefore you will need to install the following dependencies: xorg, libxext-dev and zlib1g-dev. Installing these dependencies on Ubuntu can be done as follows:

	sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev


## Features

### 🕯️ Rendering & Illumination

* **Path Traced Global Illumination:** Full support for indirect lighting, allowing light to bounce off surfaces and illuminate dark areas.
* **Multiple Importance Sampling (MIS):** A robust sampling strategy that combines BRDF sampling and Direct Light sampling to significantly reduce variance (noise) in scenes with both large area lights and small, bright points.
* **Emissive Surfaces:** Spheres and quads can be turned into light sources by assigning them a , allowing for realistic area lighting.
* **Point Lights:** Support for traditional point light sources.
* **Refraction & Reflection:** Accurate simulation of Fresnel effects, allowing for realistic glass (dielectrics) and polished metals (conductors).

### ⚡ Performance & Optimization
* **Bounding Volume Hierarchy (BVH):** Implemented a tree-based spatial partition to reduce ray-object intersection complexity. It uses Axis-Alligned Bounding Boxes to maximize the intersection speed, enabling the rendering of scenes with **tens of thousands** of primitives.
* **SIMD Vectorization:** Leveraged **SIMD (Single Instruction, Multiple Data)** instructions to process multiple floating-point calculations in parallel, specifically for ray-box intersection and vector math.
* **Multi-threading:** Implemented using `pthread` to distribute the rendering workload across all available CPU cores. By dividing the image into lines, the engine achieves near-linear scaling in performance.

## Ressources

* [Ray Tracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* [Coding Adventures - Ray Tracing](https://www.youtube.com/watch?v=Qz0KTGYJtUk&list=PLFt_AvWsXl0dlgwe4JQ0oZuleqOTjmox3)
* [The Algorithm That Makes Ray Tracing 10x Faster](https://youtu.be/p772XkEnEIU)
* [How to build a BVH](https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/)
* [Primitive Intersectors](https://iquilezles.org/articles/intersectors/)

## Use of AI

* LLMs were used as advanced search engines to help us discover some optimisation concepts and best practices used in ray tracing. It guided us towards very interesting research material that greatly contributed to this project.
* It assisted us in verifying / debugging for some calculations.
* AI was used to generate scripts that procedurally create complex scenes with thousands of object to test the BVH.
* It assisted us for the structure of this README.

# Usage

