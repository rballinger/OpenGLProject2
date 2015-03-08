//
//  Arm.cpp
//
//  Created by Hans Dulimarta on 02/18/13.
//
//
#ifdef WIN32
#include "Shapes/Cylinder.h"
#else
#include "Cylinder.h"
#endif
#include "Arm.h"
const float LENGTH = 20.0;
Arm::Arm()
{

}

Arm::~Arm()
{
    //gluDeleteQuadric(cyl_quad);
}

void Arm::build()
{
    cyl.build(0.2, 0.2, LENGTH);
    //gluCylinder(cyl_quad, 0.2, 0.2, LENGTH, 20, 25);
    //glEndList();
}

void Arm::render() const
{
    glPushMatrix();
    glTranslatef (0, 0, -LENGTH/2);
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    cyl.render();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, +0.5, 0);
    cyl.render();
    glPopMatrix();
    glPopMatrix();
}

float Arm::length() const {
    return LENGTH;
}
