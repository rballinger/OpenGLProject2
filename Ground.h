/*
 * Ground.h
 *
 *  Created on: Mar 12, 2015
 *      Author: dan
 */

#ifndef GROUND_H_
#define GROUND_H_
#include <GL/glew.h>
#include <vector>
using namespace std;

class Ground {
private:
    GLuint vertex_buffer, index_buffer, normal_buffer;
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;
public:

    Ground();
    ~Ground();

    void build();
    void render() const;

};

#endif /* GROUND_H_ */
