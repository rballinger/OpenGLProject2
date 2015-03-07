/*
 * Island.h
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */

#ifndef ISLAND_H_
#define ISLAND_H_
#include <GL/glew.h>

/* Curb : cylinder  + partial disk */
class Island {
   public:
      /* default size is unit box */
      Island();
      void build();
      void render() const;
      GLfloat getOuterRadius() const { return outerRadius; }
      GLfloat getInnerRadius() const { return innerRadius; }
   private:
      GLfloat outerRadius;
      GLfloat innerRadius;
      GLUquadric *outerCurb;
      GLUquadric *innerCurb;
      GLUquadric *topCurb;
      GLUquadric *grass;	// partial disk
      GLint list_id;
};

#endif /* ISLAND_H_ */
