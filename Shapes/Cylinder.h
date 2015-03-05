#ifndef MY_CYLINDER_H
#define MY_CYLINDER_H

#include <vector>
#include <GL/glew.h>
using namespace std;

class Cylinder {
private:
    const int N_POINTS = 60;
    GLuint v_buf, i_buf, n_buf;
    vector<float> vertices, normals;
    vector<GLushort> index;

public:
    ~Cylinder();
    void build(float topRad = 0.8f, float botRad = 0.8f, float height = 1.5);
    void render() const;
};
#endif
