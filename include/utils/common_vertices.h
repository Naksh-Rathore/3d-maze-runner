#pragma once

#include <vector>

struct CommonVertices
{
    static inline const std::vector<float> SquareVertices = {
        // pos                  // normal         // uv
        -0.5f, -0.5f, 0.0f,     0.f, 0.f, 1.f,     0.f, 0.f, // bottom-left
        0.5f, -0.5f, 0.0f,     0.f, 0.f, 1.f,     1.f, 0.f, // bottom-right
        0.5f,  0.5f, 0.0f,     0.f, 0.f, 1.f,     1.f, 1.f, // top-right
        -0.5f,  0.5f, 0.0f,     0.f, 0.f, 1.f,     0.f, 1.f  // top-left
    };

    static inline const std::vector<float> SquareVerticesNoNormals {
        // pos                // uv
        -0.5f, -0.5f, 0.0f,    0.f, 0.f, // bottom-left
        0.5f, -0.5f, 0.0f,    1.f, 0.f, // bottom-right
        0.5f,  0.5f, 0.0f,    1.f, 1.f, // top-right
        -0.5f,  0.5f, 0.0f,    0.f, 1.f  // top-left
    };

    static inline const std::vector<unsigned int> SquareIndices = {
        0, 1, 2,
        2, 3, 0
    };


    static inline const std::vector<float> CubeVertices = {
        // -------- Front (+Z) --------
        -0.5f, -0.5f,  0.5f,   0.f, 0.f, 1.f,   0.f, 0.f,
        0.5f, -0.5f,  0.5f,   0.f, 0.f, 1.f,   1.f, 0.f,
        0.5f,  0.5f,  0.5f,   0.f, 0.f, 1.f,   1.f, 1.f,
        -0.5f,  0.5f,  0.5f,   0.f, 0.f, 1.f,   0.f, 1.f,

        // -------- Back (-Z) --------
        0.5f, -0.5f, -0.5f,   0.f, 0.f,-1.f,   0.f, 0.f,
        -0.5f, -0.5f, -0.5f,   0.f, 0.f,-1.f,   1.f, 0.f,
        -0.5f,  0.5f, -0.5f,   0.f, 0.f,-1.f,   1.f, 1.f,
        0.5f,  0.5f, -0.5f,   0.f, 0.f,-1.f,   0.f, 1.f,

        // -------- Left (-X) --------
        -0.5f, -0.5f, -0.5f,  -1.f, 0.f, 0.f,   0.f, 0.f,
        -0.5f, -0.5f,  0.5f,  -1.f, 0.f, 0.f,   1.f, 0.f,
        -0.5f,  0.5f,  0.5f,  -1.f, 0.f, 0.f,   1.f, 1.f,
        -0.5f,  0.5f, -0.5f,  -1.f, 0.f, 0.f,   0.f, 1.f,

        // -------- Right (+X) --------
        0.5f, -0.5f,  0.5f,   1.f, 0.f, 0.f,   0.f, 0.f,
        0.5f, -0.5f, -0.5f,   1.f, 0.f, 0.f,   1.f, 0.f,
        0.5f,  0.5f, -0.5f,   1.f, 0.f, 0.f,   1.f, 1.f,
        0.5f,  0.5f,  0.5f,   1.f, 0.f, 0.f,   0.f, 1.f,

        // -------- Top (+Y) --------
        -0.5f,  0.5f,  0.5f,   0.f, 1.f, 0.f,   0.f, 0.f,
        0.5f,  0.5f,  0.5f,   0.f, 1.f, 0.f,   1.f, 0.f,
        0.5f,  0.5f, -0.5f,   0.f, 1.f, 0.f,   1.f, 1.f,
        -0.5f,  0.5f, -0.5f,   0.f, 1.f, 0.f,   0.f, 1.f,

        // -------- Bottom (-Y) --------
        -0.5f, -0.5f, -0.5f,   0.f,-1.f, 0.f,   0.f, 0.f,
        0.5f, -0.5f, -0.5f,   0.f,-1.f, 0.f,   1.f, 0.f,
        0.5f, -0.5f,  0.5f,   0.f,-1.f, 0.f,   1.f, 1.f,
        -0.5f, -0.5f,  0.5f,   0.f,-1.f, 0.f,   0.f, 1.f
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
