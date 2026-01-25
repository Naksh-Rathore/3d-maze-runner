#pragma once

#include <vector>

struct CommonVertices
{
    // -------- Vertex layout --------
    // vec3 position, vec2 uv
    static inline const std::vector<float> SquareVertices = {
        // pos              // uv
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top-left
    };

    static inline const std::vector<unsigned int> SquareIndices = {
        0, 1, 2,
        2, 3, 0
    };

    // -------- Cube --------
    // 6 faces * 4 vertices (no sharing to allow correct UVs)
    static inline const std::vector<float> CubeVertices = {
        // ---- Front ----
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // ---- Back ----
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // ---- Left ----
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // ---- Right ----
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // ---- Top ----
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // ---- Bottom ----
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f
    };

    static inline const std::vector<unsigned int> CubeIndices = {
        0,  1,  2,  2,  3,  0,   // front
        4,  5,  6,  6,  7,  4,   // back
        8,  9, 10, 10, 11,  8,   // left
       12, 13, 14, 14, 15, 12,   // right
       16, 17, 18, 18, 19, 16,   // top
       20, 21, 22, 22, 23, 20    // bottom
    };
};
