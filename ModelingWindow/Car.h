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
    GLuint v_buf, i_buf, n_buf;
    vector<glm::vec3> vertices, normals;
    vector<GLushort> index;
    const float CHASSIS_LEN = 20,
        CHASSIS_WIDTH = 10,
        CHASSIS_HEIGHT = 5,
        OFF_GROUND = 3,
        SUBDIV = 10;
    int chassis_top_count,
        side_count;
public:
    ~Car();
    void build();
    void render() const;
};
#endif /* CAR_H_ */
