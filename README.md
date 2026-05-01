# Atari-Game

`Atari-Game` contains `IslandPlat`, a 2D platformer written in C for an Atari ST programming course. The project focuses on low-level graphics, frame timing, collision handling, and modular game logic rather than modern engine tooling.

## Overview

The final playable build lives in `IslandPlat/stages5-7`. It targets the Atari ST environment and uses Atari-specific screen, timing, and input routines, so it should be treated as a retro systems project rather than a portable desktop game.

## Gameplay

- Move left with `A`
- Move right with `D`
- Jump with `W`
- Quit with `Q`

The goal is to reach the coin before the timer expires while avoiding spiders and staying alive.

## Features

- 640x400 Atari ST style rendering
- Custom bitmap drawing routines
- Double-buffered screen updates
- Platforming movement with jump and gravity handling
- Enemy patrol logic for spiders
- Timer, UI, and collectible win condition
- Separation between input, model, event, and render code

## Build

This project expects an Atari ST compatible C toolchain with `cc68x` available.

```bash
cd IslandPlat/stages5-7
make
```

The build produces an executable named `anim`.

## Run

Run the generated executable in an Atari ST compatible environment or emulator configured for the same toolchain/runtime used during development.

## Repository Layout

- `IslandPlat/stages5-7`: final integrated version of the game
- Earlier stage folders inside `IslandPlat`: milestone work from earlier course checkpoints
- `island.c`: main game loop and double-buffer setup
- `events.c`: collision checks, timer logic, and win/loss conditions
- `model.c`: movement updates and shared game state behavior
- `render.c`: sprite and UI rendering
- `RASTER.C`: low-level raster operations
- `bitmaps.c`: sprite and UI bitmap data

## Notes

Because the code depends on Atari-specific headers and system calls, it is not expected to compile unchanged with a modern desktop C compiler.
You would need Steem running TOS 
