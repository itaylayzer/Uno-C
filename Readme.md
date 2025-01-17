# Uno

uno c player vs computer game build with raylib using heuristic algorithm.

## start the game

first of all git clone this repository. then you can compile and run with gcc. for shortcuts i made a `Makefile`:

| MAKE          | commands                              |
| ------------- | ------------------------------------- |
| `make`        | to build the project into binary file |
| `make run`    | to build and run the binary file      |
| `make single` | to run the binary file                |

## to build & run
This project uses CMake.

### Building project
1. Creating build folder
2. CD to build folder
3. Run CMake 
4. Run Makefile

here a script to do so 
```bash
mkdir -p build
cd build
cmake ..
make
```

### Runnning
now after building we have Uno-C binary file. so in linux do `./Uno-C`

## Keys:

| UI     | keys              |
| ------ | ----------------- |
| f/f11: | Toggle FullScreen |

| MOVEMENT   | keys                |
| ---------- | ------------------- |
| g:         | 5 steps back        |
| left/a/h:  | step back           |
| right/d/j: | step forward        |
| k:         | 5 steps forwards    |
| 1-9:       | moving in direction |
| -/+:       | changing direction  |

| GAMEPLAY    | keys                |
| ----------- | ------------------- |
| m/b/c/down: | take card from bank |
| space/x/up: | pieck to put        |

## Images & Gameplay:

click on the image to watch the gameplay
[![Watch the video](/images/2.png)](https://itaylayzer.github.io/Uno-C/)
