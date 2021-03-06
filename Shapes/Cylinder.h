#ifndef MY_CYLINDER_H
#define MY_CYLINDER_H

#include <vector>
#ifdef WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GL/glew.h>
#endif
using namespace std;

class Cylinder {
private:
    GLuint v_buf, i_buf, n_buf;
    vector<float> vertices, normals;
    vector<GLushort> index;

public:
    ~Cylinder();
    int N_POINTS;
    void build(float topRad = 0.8f, float botRad = 0.8f, float height = 1.5, int faces=30);
    void render(bool showTop = true) const;
};
#endif
