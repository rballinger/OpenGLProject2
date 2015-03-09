/*
 * Car.h
 *
 *  Created on: Mar 7, 2015
 *      Author: Ryan
 */

#ifndef CAR_H_
#define CAR_H_
#ifdef WIN32 /* only because I'm using CodeBlocks on Windows */
#define GLEW_STATIC
#include <GL/glew.h>
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
#include "Tire.h"

class Car {
private:
    GLuint v_buf, i_buf, n_buf;
    vector<glm::vec3> vertices, normals;
    vector<GLushort> index;
    const float CHASSIS_LEN = 20,
        CHASSIS_WIDTH = 8,
        CHASSIS_HEIGHT = 3,
        OFF_GROUND = 1.25,
        SUBDIV = 40,
        ROOF = 2,
        SECTION_LEN = CHASSIS_LEN / SUBDIV;
    int chassis_top_count,
        side_count;
    Tire *tire_fr, *tire_fl, *tire_rr, *tire_rl;
    glm::mat4 tire_fr_cf, tire_fl_cf, tire_rr_cf, tire_rl_cf;
public:
    ~Car();
    void build();
    void render() const;
    void rotate_wheels(float dis);
};
#endif /* CAR_H_ */
