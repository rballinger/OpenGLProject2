#ifndef MY_SPHERE_H
#define MY_SPHERE_H
#include <vector>
#ifdef WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GL/glew.h>
#endif
using namespace std;

class Sphere {
private:
    GLuint vertex_buffer, index_buffer, normal_buffer;
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;
    int numLongitudeRings, numLatitudeRings;
    int start_of_northpole;

public:
    void build(int latRings, int lonRings);
    void render(float,float,float) const;
};
#endif
