/*
 * WeatherVaneBase.h
 *
 *  Created on: Mar 8, 2015
 *      Author: dan
 */

#ifndef WEATHERVANEBASE_H_
#define WEATHERVANEBASE_H_
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

class WeatherVaneBase {
private:
    Cylinder legOne;  // post of street light
    Cylinder legTwo;	// base of street light
    Cylinder legThree;	// shade of street light
    Cylinder legFour;	// shade of street light

    Cylinder smallSquareOne;  // post of street light
    Cylinder smallSquareTwo;	// base of street light
    Cylinder smallSquareThree;	// shade of street light
    Cylinder smallSquareFour;	// shade of street light

    Cylinder largeSquareOne;  // post of street light
    Cylinder largeSquareTwo;	// base of street light
    Cylinder largeSquareThree;	// shade of street light
    Cylinder largeSquareFour;	// shade of street light
public:
    void build();
    void render() const;
};

#endif /* WEATHERVANEBASE_H_ */
