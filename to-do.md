# To Do

- Implement a bobbing player camera that bobs when still (like in DOOM)

Pseudo code:

```cpp
void Game::processInput(GLFWwindow *window) {
    // Keyboard input
    // ....

    // If no keyboard input is given
    m_world.bobCamera();
}
```

- Create a chest collection HUD

- For debug view, just move the camera's y axis up
