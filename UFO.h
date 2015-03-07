/*
 * UFO.h
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */

#ifndef UFO_H_
#define UFO_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#ifdef WIN32 /* only because I'm using CodeBlocks on Windows */
#include "Shapes/Sphere.h"
#else
#include "Sphere.h"
#endif

/* UFO : cyclinder  + partial disk + sphere */
class UFO {
   public:
      /* default size is unit box */
      UFO();
      ~UFO();
      void build(float,float,float,float);
      void render() const;
      GLfloat getDiskTopRadius() const { return diskTopRadius; }
      GLfloat getDiskBottomRadius() const { return diskBottomRadius; }
      GLfloat getCockPitRadius() const { return sphereRadius; };
   private:
      GLfloat sphereRadius;
      GLfloat diskTopRadius;
      GLfloat diskBottomRadius;
      GLUquadric *topDisk;		// cylinder
      GLUquadric *bottomDisk;  	// cylinder
      GLUquadric *bottomDiskInside;  	// cylinder
      GLUquadric *midRim;		// partial disk
      GLUquadric *cockPit;		// sphere

      float init_x;
      float init_y;
      float init_z;

      GLint list_id;
};
#endif /* UFO_H_ */
