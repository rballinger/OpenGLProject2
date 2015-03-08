/*
 * Fan.h
 *
 *  Created on: Mar 7, 2015
 *      Author: dan
 */

#ifndef FAN_H_
#define FAN_H_
#include <vector>
#include <GL/glew.h>
using namespace std;
#include "Cylinder.h"

class Fan {
private:
    GLuint vertex_buffer, index_buffer, normal_buffer;
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;
    Cylinder vaneRim;	// shade of street light
public:

    Fan();
    ~Fan();

    void build(int,float);
    void render() const;
	float LENGTH;
	int POINTS;
    GLUquadric *spoke;
    GLint list_id;
    GLfloat radius;
    GLfloat tire_thickness;

};

#endif /* FAN_H_ */
