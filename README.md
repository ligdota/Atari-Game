IslandPlat is a small 2D platformer built in C for my schools low level programming class. The game targets the Atari ST environment and was developed in stages, starting with low-level raster drawing and building up to a playable platforming game with movement, collision, enemies, a timer, and collectible win condition.

Project Overview
The final version of the game is in stages5-7. Earlier folders show the project as it was built throughout the course:

stage1 - original game specification document
stage2 - raster drawing functions and raster tests
stage3 - model and event logic tests
stage4 - rendering system and render tests
stages5-7 - final integrated game
Gameplay
The player controls a stickman moving across floating platforms. The goal is to reach the coin before the timer runs out while avoiding spiders and staying on screen.

Controls:

Key	Action
W	Jump
A	Move left
D	Move right
Q	Quit
The game ends when the player collects the coin, runs out of time, touches an enemy, or leaves the screen.

Features
640x400 Atari ST-style graphics
Custom bitmap rendering routines
Double buffering for smoother screen updates
Keyboard input handling
Platform collision detection
Gravity and jump state logic
Moving spider enemies
Timer and heart UI rendering
Coin pickup win condition
Technologies
C
Atari ST system calls through osbind.h
cc68x compiler toolchain
Makefile-based builds
Building
The final game is built from the stages5-7 directory:

cd stages5-7
make
The makefile builds the game executable as anim.

This project depends on an Atari ST-compatible C toolchain with cc68x available. It is not intended to compile directly with a modern desktop C compiler without porting the Atari-specific graphics, input, screen, and supervisor-mode calls.

Running
Run the generated anim executable in an Atari ST-compatible environment or emulator configured for the same toolchain/runtime used by the class.

./anim
Code Structure
The final game is organized into small C modules:

File	Purpose
island.c	Main game loop, model setup, timing, double buffering
model.c / model.h	Game object data structures and movement updates
events.c / events.h	Collision checks, jump requests, timer logic, end-game checks
render.c / render.h	Draws platforms, player, enemies, timer, heart, and coin
RASTER.C / RASTER.H	Low-level bitmap plotting and screen clearing
bitmaps.c / bitmaps.h	Bitmap data for game sprites and UI
input.c / input.h	Keyboard polling and control helpers
psg.c / psg.h	Atari ST programmable sound generator helpers
music.c / music.h	Basic music playback logic
TYPES.H	Shared constants, type aliases, and game configuration
What I Learned
This project was created as part of a class and focuses on lower-level game programming concepts, including:

Working with frame buffers and bitmap data
Structuring game state with C structs
Separating rendering, input, model, and event logic
Handling collisions manually
Timing gameplay updates around system ticks
Building a project incrementally across multiple development stages
Notes
Some compiled object files and generated executables are included because this repository reflects the original school project folder. The source files are the main reference for the implementation.
