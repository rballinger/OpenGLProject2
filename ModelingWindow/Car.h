/*
 * Car.h
 *
 *  Created on: Mar 7, 2015
 *      Author: Ryan
 */

#ifndef CAR_H_
#define CAR_H_
#ifdef WIN32 /* only because I'm using CodeBlocks on Windows */
#include "Shapes/Cylinder.h"
#include "Shapes/Torus.h"
#include "Shapes/Sphere.h"
#else
#include "Cylinder.h"
#include "Torus.h"
#include "Sphere.h"
#endif
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

class Car {
private:
    Torus elbow;	// top curve of street light
public:
    void build();
    void render() const;

};
#endif /* CAR_H_ */
