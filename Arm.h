//
//  Arm.h
//  Animation
//
//  Created by Hans Dulimarta on 02/18/13.
//
//

#ifndef __Animation__Arm__
#define __Animation__Arm__
#include <iostream>
#ifdef WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shapes/Cylinder.h"
#else
#include <GL/glew.h>
#include "Cylinder.h"
#endif
class Arm  {
public:
    Arm();
    ~Arm();
    void build();
    void render() const;
    float length() const;
private:
    Cylinder cyl;
};
#endif /* defined(__Animation__Arm__) */
