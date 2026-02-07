#pragma once

namespace GameObject {
    struct Timer {
        float ratio;
        float duration;

        Timer(float r, float d);

        void tick();
    };
};