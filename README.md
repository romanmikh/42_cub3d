# 42 Cub3D 🧊

**Cub3D** is a **Wolfenstein/Doom 3D-inspired** raycasting project developed entirely in C as part of the 42 curriculum. It provides a **basic 3D rendering engine** using **raycasting**

![](./cub3d.gif)

## Features

- **Raycasting Engine**: Implements a first-person perspective using raycasting.
- **Textured Walls & Floor Casting**: Supports wall textures and basic floor and ceiling rendering.
- **Player Movement**: Includes rotation and movement with collision detection.
- **Configurable Map Parsing**: Reads `.cub` files defining walls, textures, and player spawn.

## Installation and Usage

1. Clone the repository:
   ```sh
   git clone https://github.com/romanmikh/cub3d.git
   cd cub3d
   make
   ./cub3d ./maps/nature.cub
   ```

3. Valgrind output saved in valgrind_out.txt after:
   ```sh
   ulimit -n 2014 # necessary once only, to address 'file descriptor too high' error
   make valgrind
   ```

## Helpful Resources
1. https://www.youtube.com/watch?v=8gIhNSAXYcQ&ab_channel=AndrePrihodko (quick intuition)
2. https://www.youtube.com/watch?v=W5P8GlaEOSI&ab_channel=AbdulBari (detailed introduction)
3. https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/ (code example)
4. https://harm-smits.github.io/42docs/projects/cub3d (detailed explanation)

## Documentation
   ```sh
   /local/path/to/cub3d/html/index.html  # > Files > main.c (in browser)
   ```
Opens the interactive function graph, which can help illustrate the function call hierarchy.

Full code map (almost):

![Full Code Map](./html/main_8c_a3c04138a5bfe5d72780bb7e82a18e627_cgraph.png)
