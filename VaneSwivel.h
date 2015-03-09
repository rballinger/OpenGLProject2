/*
 * VaneSwivel.h
 *
 *  Created on: Mar 8, 2015
 *      Author: dan
 */

#ifndef VANESWIVEL_H_
#define VANESWIVEL_H_
#include <vector>
#ifdef WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shapes/Cylinder.h"
#else
#include "Cylinder.h"
#endif
using namespace std;

class VaneSwivel {
private:
    GLuint vertex_buffer, index_buffer, normal_buffer;
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;
    Cylinder smallSwivel;
    Cylinder largeSwivel;
public:

    VaneSwivel();
    ~VaneSwivel();

    void build();
    void render() const;
	int POINTS;
    GLfloat radius;
};

#endif /* VANESWIVEL_H_ */
