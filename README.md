# Meteor Rush

Meteor Rush is a 2D arcade space game written in C++ with SFML.  
You pilot a ship, avoid incoming meteors, and shoot for the highest score.

## Features
- Fast-paced asteroid-dodging gameplay
- Two playable ship variants (heavy and light)
- Animated sprites and effects (explosions, flames, galaxy background)
- Sound effects and looping soundtrack
- Persistent high score stored in `score.txt`

## Controls
- **Arrow keys**: move the ship
- **Space**: fire missile
- **Mouse (left click)**: interact with menu buttons

## Tech Stack
- C++17
- [SFML 2.5.1](https://www.sfml-dev.org/)
- qmake / Qt project file (`meteorrush.pro`)

## Build Requirements
- SFML headers and libraries installed
- A qmake-compatible toolchain

> The project file currently uses Windows paths:
> - `C:/SFML-2.5.1/include`
> - `C:/SFML-2.5.1/lib`
>
> Update these paths in `/home/runner/work/Meteor-Rush/Meteor-Rush/meteorrush.pro` if your SFML installation is elsewhere.

## Build and Run
From the repository root:

1. Open `/home/runner/work/Meteor-Rush/Meteor-Rush/meteorrush.pro` in Qt Creator  
   **or** run qmake from the terminal.
2. Build the project in Debug or Release mode.
3. Run the generated executable.

Ensure runtime assets (`graphics`, `sounds`, `fonts`, and `score.txt`) are available in the working directory expected by the executable.

## Project Structure
- `main.cpp` – game loop, UI states, asset loading, collision/score logic
- `spaceship.*` – player movement, acceleration, missile firing
- `rock.*` – meteor motion and rotation
- `animatedsprite.*` – reusable animation + sound helper
- `button.*` – menu button behavior
- `meteorrush.pro` – build configuration
