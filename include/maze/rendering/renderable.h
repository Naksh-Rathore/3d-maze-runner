#pragma once

#include "rendering/geometry/mesh.h"
#include "rendering/material/material.h"

namespace Rendering {
    struct Renderable {
        Mesh m_mesh;
        Material m_material;
    
        Renderable(const Renderable&) = delete;
        Renderable& operator=(const Renderable&) = delete;

        Renderable(Renderable&&) = default;
        Renderable& operator=(Renderable&&) = default;
    };
}