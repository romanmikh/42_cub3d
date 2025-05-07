# 42 Cub3D 🧊

A **1993 Doom**-inspired basic 3D rendering engine using raycasting developed entirely in C.

![](./cub3d.gif)

## Features

- **Raycasting Engine**: Implements a first-person perspective using raycasting.
- **Textured Walls & Floor Casting**: Supports wall textures and basic floor and ceiling rendering.
- **Player Movement**: Includes rotation and movement with collision detection.
- **Configurable Map Parsing**: Reads `.cub` files defining walls, textures, and player spawn.

## Installation and Usage

1. Clone the repository:
   ```sh
   git clone https://github.com/romanmikh/42_cub3d.git cub3D
   cd cub3D
   make
   ./cub3D ./maps/pass/corridors.cub
   ```

3. Valgrind output saved in valgrind_out.txt after:
   ```sh
   ulimit -n 1024 # necessary once only, to address 'file descriptor too high' error
   make valgrind
   ```

## Helpful Resources
1. https://www.youtube.com/watch?v=8gIhNSAXYcQ&ab_channel=AndrePrihodko (quick intuition)
2. https://www.youtube.com/watch?v=W5P8GlaEOSI&ab_channel=AbdulBari (detailed introduction)
3. https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/ (code example)
4. https://harm-smits.github.io/42docs/projects/cub3d (detailed explanation)
5. https://store.steampowered.com/app/2280/DOOM__DOOM_II/ (the OG game)
6. https://www.youtube.com/watch?v=_SvLXy74Jr4&ab_channel=ModPunchtree (**minecraft-built** CPU running Doom!!!)

## Documentation

![Full Code Map](https://i.imgur.com/cn2NjKc.png)
