# cub3D

A graphical 3D game engine using raycasting techniques, developed as part of the 42 Network curriculum.  
Created by **Abdellatif Aghla** and **Salaheddine Rachidi**.

> We truly enjoyed every moment of working on this project.

---


https://github.com/user-attachments/assets/ea9d0cc2-2cdc-4eae-8426-7ae0aefdc1e2

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#✨-features)
   - [Mandatory Part](#✅-mandatory-part)
   - [Bonus Features](#🌟-bonus-features-beyond-requirements)
3. [Game Controls](#game-controls)
4. [Map Format (.cub file)](#map-format-cub-file)
5. [How to Build](#how-to-build)
   - [For macOS](#for-macos)
   - [For Linux](#for-linux)
6. [Authors](#authors)
7. [Final Note](#final-note)

---

## Overview

cub3D is inspired by the early era of 3D games such as *Wolfenstein 3D*.  
It uses **raycasting** to project a 2D map into a pseudo-3D environment and provides an immersive first-person view inside a maze-like structure.

The project relies on the **MLX42** graphics library to handle rendering, input, and window management.

---

## ✨ Features

### ✅ Mandatory Part
- Raycasting engine rendering walls in pseudo-3D
- Textured walls
- Map parsing with full format validation
- Smooth player movement & rotation
- Collision detection
- Mouse toggle (optional)
- Ceiling and floor coloring
- Clean exit and resource management

### 🌟 Bonus Features (Beyond Requirements)
- 🗺️ **Minimap**: Displays the player's current position and orientation
- 🗺️ **Big Map (Q Key)**: Expands a large, detailed map and *pauses player movement* while it's open
- 🔥 **Lighter Animation**: A hand toggles a lighter. When lit, the world is bright; when off, it darkens
- 🚪 **Interactive Doors**: Doors open when you step into them
- 🖱️ **Mouse Control (M Key)**: Toggle mouse input to turn the player's view

---

## Game Controls

Here are the controls you can use to navigate and interact with the game:

- **W**: Move forward
- **S**: Move backward
- **A**: Move left
- **D**: Move right
- **Left Arrow**: Turn left
- **Right Arrow**: Turn right
- **L**: Turn the light on and off (when turned on, the world becomes brighter)
- You can also click on the lighter icon in the window to toggle the light.
- **M**: Toggle using mouse instead of arrow keys (enables/disables mouse control for turning).
- **Q**: Toggle showing the big map.
- You can also click on the minimap in the window to show the large map.
- You can move around the large map using arrows.
- **Esc** or closing the window: Exit the game and close the window.

---

## Map Format (.cub file)

A valid `.cub` file includes:

1. **Texture paths for walls**
   - NO ./textures/wall_north.xpm  
   - SO ./textures/wall_south.xpm  
   - WE ./textures/wall_west.xpm  
   - EA ./textures/wall_east.xpm  

2. **RGB values for floor and ceiling**
   - F 220,100,0  
   - C 225,30,0  

3. **2D map layout** (must be closed/surrounded by walls)

   Example:
  ```text
    111111111
  1110001001011
  100000100001
   1101000001
     1 11111
```

---

## How to Build

### For macOS

1. **Install Dependencies**:
   First, you need to have the required dependencies installed. On macOS, you can use **Homebrew** to install the necessary packages.

   ```bash
   # Install Homebrew (if not already installed)
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

   # Install dependencies
   brew install cmake glfw
   ```
2. **Clone the Repository**: Clone the cub3D project repository to your local machine:

    ```bash
    git clone git@github.com:AghlaAbdo/42_Cub3D.git
    cd 42_Cub3D
    ```

3. **Build the Project**: The `Makefile` is set up to compile the project. Simply run the following command to build the project:

   ```bash
   make
   # For bonus part
   make bonus
   ```
   This will compile the program and generate the executable (`cub3D` or `cub3D_bonus` for the bonus version). For macOS, the compilation uses the following command:
   ```bash
   $(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(LIBFT)
   ```

4. **Run the Program**: After successfully building the project, you can run the cub3D program with:

    ```bash
    ./cub3D path_to_map.cub
    # For bonus part
    ./cub3D_bonus path_to_map.cub
    ```
    Replace `path_to_map.cub` with the path to your `.cub` map file.

### For Linux

1. **Install Dependencies**: On Linux, you need to install CMake and GLFW for the project to work properly. You can use your package manager to install these dependencies.

    ```bash
    sudo apt update
    sudo apt install cmake libglfw3-dev
    ```

2. **Clone the Repository**: Clone the cub3D project repository to your local machine:

    ```bash
    git clone git@github.com:AghlaAbdo/42_Cub3D.git
    cd 42_Cub3D
    ```

3. **Build the Project**: The `Makefile` is set up to compile the project. Simply run the following command to build the project:

   ```bash
   make
   # For bonus part
   make bonus
   ```
   This will build the cub3D executable. For Linux, the compilation uses the following command:
   ```bash
   $(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -ldl -lm -lX11 -lpthread -lXrandr -lXi $(LIBFT)
   ```

4. **Run the Program**: After successfully building the project, you can run the cub3D program with:

    ```bash
    ./cub3D path_to_map.cub
    # For bonus part
    ./cub3D_bonus path_to_map.cub
    ```
    Replace `path_to_map.cub` with the path to your `.cub` map file.

---

## Authors

  - [Abdellatif Aghla](https://github.com/AghlaAbdo)
  - [Salaheddine Rachidi](https://github.com/salahrachidi)

  Made with ❤️ @ 1337.

---

## Final Note

  This project was a great experience, not only in terms of technical skills but also creativity and teamwork.  
  From raycasting and textures to animation and polish — we genuinely enjoyed building every part of it.
  
  We welcome feedback and contributions from the community! If you have suggestions for improvements, find bugs, or have any questions, please feel free to open an issue or submit a pull request.
