# Cub3D

A 3D maze game inspired by Wolfenstein 3D, built using raycasting.

## About

This project implements a first-person 3D graphical representation of a maze using raycasting principles and the MLX42 graphics library. This is a team project from the 42 School curriculum that serves as an introduction to computer graphics, mathematics in game development, and low-level graphics programming.

## Features

- Real-time 3D rendering using raycasting
- Textured walls (different textures for N/S/E/W sides)
- Customizable floor and ceiling colors
- Player movement and camera rotation
- Minimap system (2D overhead map with player position and rays)

## Requirements

- MLX42 library (automatically cloned during compilation)
- C compiler (gcc/clang)

## Installation

```bash
git clone https://github.com/an-tran-p/cub3D.git
cd cub3d
make
```

## Usage

```bash
./cub3D maps/map.cub
```

## Controls

- `W` `A` `S` `D` - Move through the maze
- `←` `→` - Look left/right
- `ESC` - Exit the game

## Map Format

Maps use `.cub` extension with the following characters:
- `0` - Empty space
- `1` - Wall
- `N/S/E/W` - Player starting position and orientation

Map must be surrounded by walls.

---

*42 School Project - 2025*
