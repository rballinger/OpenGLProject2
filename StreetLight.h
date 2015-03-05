/*
 * StreetLight.h
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */

#ifndef STREETLIGHT_H_
#define STREETLIGHT_H_
#include "Cylinder.h"
#include "Torus.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

class StreetLight {
private:
    Cylinder post;  // post of street light
    Cylinder base;	// base of street light
    Torus elbow;	// top curve of street light
    Cylinder shade;	// shade of street light
    Sphere lamp;	// the actual light bulb
public:
    void build();
    void render() const;

};
#endif /* STREETLIGHT_H_ */
