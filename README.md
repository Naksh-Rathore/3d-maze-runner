# 3D Maze Runner

<img width="400" height="400" alt="Screenshot From 2026-02-15 16-53-54" src="https://github.com/user-attachments/assets/f7c4ad40-231e-4833-be34-3e734adc01c0" />


## Overview
3D Maze Runner is a real-time 3D maze exploration game inspired by classic titles like Doom. It features:

- **Runtime Map Generation**: Player editable mazes (in `assets/levels`) to have endless replayability.
- **Phong Lighting**: Realistic lighting and shading.
- **Chests & Timed Challenges**: Collect chests within a time limit to win the game.
- **Intuitive HUDs**: Clear heads-up displays for player status and progress.

This project is licensed under the **MIT License**. Contributions are welcome and encouraged!

---

## Dependencies
- `C++` Compiler
- `CMake` utility
- Only tested on Windows and Fedora Linux (other OSes have a chance of not working)
- All dependencies must be in your system PATH

---

## Cloning & Building

Clone the repository:

```
git clone --recurse-submodules https://github.com/Naksh-Rathore/3d-maze-runner.git
cd 3d-maze-runner
```


Build the project using:

```
cmake -S . -B build/
cmake --build build/
```

and run the binary with:

```
./build/3d-maze-runner/3d-maze-runner
```

Play!

---

## Contributing
- Report issues
- Submit pull requests
- Suggest new features

Please follow code style consistency and use meaningful commit messages.

---

## License
This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.
