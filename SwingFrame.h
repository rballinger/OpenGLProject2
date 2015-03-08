#ifndef SWING_FRAME_H
#define SWING_FRAME_H
#ifdef WIN32
#include "Shapes/Cylinder.h"
#include "Shapes/Torus.h"
#endif

class SwingFrame {
private:
    Cylinder pipe;
    Torus elbow;

public:
    void build();
    void render() const;
};
#endif
