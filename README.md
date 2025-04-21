# [Orbgen] - A High-Performance N-Body Gravity Simulation Engine

## Project Overview

This project is an ambitious endeavor to create a performant and complex N-body gravity simulation engine using the C programming language and the Vulkan graphics API. The goal is to dynamically simulate the gravitational interactions of multiple celestial bodies (planets, stars, etc.) and visualize their movements with a high degree of graphical detail and performance.

Unlike simpler simulations that might use less performant methods or higher-level graphics APIs, this project aims to leverage the low-level control and performance capabilities of Vulkan to handle a large number of bodies and render stunning visualizations.

## Goals

* **Accurate N-Body Simulation:** Implement accurate numerical integration methods (e.g., Leapfrog, Runge-Kutta) to simulate the gravitational forces and resulting movements of multiple bodies based on Newton's Law of Universal Gravitation.
* **High-Performance Rendering with Vulkan:** Utilize the Vulkan graphics API to render the celestial bodies and their trajectories efficiently. This includes:
  * Optimizing buffer management and memory usage on the GPU.
  * Implementing efficient rendering pipelines.
  * Leveraging Vulkan's asynchronous capabilities for better performance.
* **Support for a Large Number of Bodies:** Design the simulation and rendering pipeline to handle a significant number of celestial bodies without significant performance degradation.
* **Dynamic Interactions:** Accurately simulate the complex gravitational interactions between all simulated bodies.
* **Visualization:** Create a compelling visual representation of the simulation, potentially including:
  * Rendering of planets, stars, and other celestial objects.
  * Drawing orbital trails.
  * Basic ambient lighting or shading.
  * Camera controls (zoom, pan, orbit).
* **Modularity and Extensibility:** Structure the code in a modular way to allow for future expansion, such as adding different celestial body types, physical effects, or visualization features.

## Technical Stack

* **Core Language:** C
* **Graphics API:** Vulkan
* **Windowing and Input:** SDL2 (for window creation, event handling, and Vulkan surface integration)
* **Build System:** CMake (for managing the build process and finding dependencies like Vulkan and SDL2)
* **Shader Language:** GLSL (compiled to SPIR-V)
* **(Optional) Memory Allocator:** VMA (Vulkan Memory Allocator) - planning to integrate for more efficient GPU memory management.

## Why Vulkan?

Vulkan was chosen for this project despite its complexity because it offers:

* **Explicit Control:** Greater control over GPU hardware for fine-tuned performance optimizations.
* **Lower Overhead:** Reduced CPU overhead compared to higher-level APIs.
* **Access to Modern Hardware Features:** Ability to leverage the latest features of modern graphics cards.
* **Scalability:** Designed to scale well to multi-core CPUs and complex rendering scenarios.

While the learning curve is steep, the performance potential of Vulkan is crucial for achieving the project's goal of simulating and rendering a large number of interacting bodies smoothly.
