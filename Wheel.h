#ifndef HANS_WHEEL_H
#define HANS_WHEEL_H

#ifdef WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shapes/Torus.h"
#else
#include <GL/glew.h>
#include "Torus.h
#endif

/* Wheel : torus  + spokes */
class Wheel {
   public:
      /* default size is unit box */
      Wheel();
      void build();
      void render() const;
      GLfloat getRadius() const { return radius; }
      GLfloat getThickness() const { return tire_thickness; }
   private:
      GLfloat radius;
      GLfloat tire_thickness;
      GLUquadric *spoke;
      GLUquadric *curb;
      GLint list_id;
      Torus t;
};
#endif
