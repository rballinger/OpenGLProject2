/*
 * Tire.h
 *
 *  Created on: Mar 6, 2015
 *      Author: dan
 */

#ifndef TIRE_H_
#define TIRE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include "Torus.h"
#include "Cylinder.h"
#include <vector>

using namespace std;

/* Tire : cyclinder + cylinders + torus */
class Tire {
   public:
      Tire();
      ~Tire();
      void build();
      void render() const;
      //GLfloat getDiskTopRadius() const { return diskTopRadius; }
      //GLfloat getDiskBottomRadius() const { return diskBottomRadius; }
      //GLfloat getCockPitRadius() const { return sphereRadius; };
   private:
      GLfloat rubberTopRadius;
      GLfloat rubberBottomRadius;
      GLfloat wallInnerRadius;
      GLfloat wallOuterRadius;
      Cylinder hub;				// cylinder

      float d_angle = 2*M_PI/5.0;
      Cylinder nut1;				// cylinder
      Cylinder nut2;				// cylinder
      Cylinder nut3;				// cylinder
      Cylinder nut4;				// cylinder
      Cylinder nut5;				// cylinder

      GLUquadric *rubber;		// cylinder
      GLUquadric *outRubberWall;
      GLUquadric *inRubberWall;
      std::vector<Cylinder> nuts;


      GLint list_id;
};

#endif /* TIRE_H_ */
