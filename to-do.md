# To Do

- Work on collision animation with chests (a spring up animation)

Pseudocode for the animation:

```cpp
glm::mat4 model(1.0f);

// Do whatever translation you want
// ...

amplitude = isCollected ? 4.0f : 2.0f

// Do the sine math
// ...

float yThreshold = 100.0f

// model.pos is pseudocode, i will do it a way actually
if (model.pos.y >= yThreshold)
    disappear();
```

- For debug view, just move the camera's y axis up
