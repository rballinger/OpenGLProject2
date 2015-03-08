/*
 * Car.cpp
 *
 *  Created on: Mar 7, 2015
 *      Author: Ryan
 */
#include <iostream>
#include "Car.h"

using glm::vec3;

Car::~Car() {
    glDeleteBuffers(1, &v_buf);
    glDeleteBuffers(1, &i_buf);
    glDeleteBuffers(1, &n_buf);
}

void Car::build() {
    glGenBuffers(1, &v_buf);
    glGenBuffers(1, &i_buf);
    glGenBuffers(1, &n_buf);
    vec3 v1, v2, v3, v4, n1, t1;

    // build chassis

    /* chassis for car, simple box */
    // top
    float section_h = CHASSIS_HEIGHT + OFF_GROUND;
    float section_len = CHASSIS_LEN / SUBDIV;
    n1 = {0, 0, 1};
    for(int i = 0; i < SUBDIV; i++){
        v1 = {0, i * section_len, section_h};
        v2 = {CHASSIS_WIDTH, i * section_len, section_h};
        index.push_back(vertices.size());
        vertices.push_back(v1);
        normals.push_back(n1);
        index.push_back(vertices.size());
        vertices.push_back(v2);
        normals.push_back(n1);
    }

    chassis_top_count = index.size();

    // bottom
    n1 = {0, 0, -1};
    for(int i = 0; i < chassis_top_count; i++){
        t1 = vertices[i];
        t1.z -= CHASSIS_HEIGHT;
        index.push_back(vertices.size());
        vertices.push_back(t1);
        normals.push_back(n1);
    }

    // sides
    // -y side
    n1 = {0, -1, 0};
    for(int i = 0; i < vertices.size() / 2; i++){
        if(i % 2 == 0){
            index.push_back(i);
            normals.push_back(n1);
            index.push_back(i + chassis_top_count);
            normals.push_back(n1);
        }
    }
    // -x side
    n1 = {-1, 0, 0};
    index.push_back(chassis_top_count - 2);
    normals.push_back(n1);
    index.push_back((chassis_top_count * 2) - 2);
    normals.push_back(n1);
    index.push_back(chassis_top_count - 1);
    normals.push_back(n1);
    index.push_back((chassis_top_count * 2) - 1);
    normals.push_back(n1);
    // +y side
    n1 = {0, 1, 0};
    for(int i = vertices.size() / 2 - 1; i >= 0; i--){
        if(i % 2 == 1){
            index.push_back(i);
            normals.push_back(n1);
            index.push_back(i + chassis_top_count);
            normals.push_back(n1);
        }
    }
    // +x side
    n1 = {1, 0, 0};
    index.push_back(0);
    normals.push_back(n1);
    index.push_back(chassis_top_count);
    normals.push_back(n1);
    index.push_back(1);
    normals.push_back(n1);
    index.push_back(chassis_top_count + 1);
    normals.push_back(n1);


    side_count = index.size() - chassis_top_count * 2;




    glBindBuffer(GL_ARRAY_BUFFER, v_buf);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    float *ptr = vertex_ptr;
    for(auto v : vertices){
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, n_buf);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *normal_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    ptr = normal_ptr;
    for(auto n : normals){
        ptr[0] = n.x;
        ptr[1] = n.y;
        ptr[2] = n.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLushort),
        index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    for(auto v : vertices){
        cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    }
    for(auto i : index){
        vec3 v = vertices[i];
        cout << i << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    }

}

void Car::render() const {
    static float CHROME_AMBIENT[] = {0.250000, 0.250000, 0.250000, 1.000000};
    static float CHROME_DIFFUSE[] = {0.400000, 0.400000, 0.400000, 1.000000};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);

    glPushAttrib(GL_ENABLE_BIT);
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, v_buf);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, n_buf);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buf);

    glDrawElements(GL_QUAD_STRIP, chassis_top_count, GL_UNSIGNED_SHORT, 0);
    glFrontFace(GL_CW);
    glDrawElements(GL_QUAD_STRIP, chassis_top_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * chassis_top_count));
    glDrawElements(GL_QUAD_STRIP, side_count, GL_UNSIGNED_SHORT, (void *) (sizeof(GLushort) * chassis_top_count * 2));
    glFrontFace(GL_CCW);

    glPopAttrib();

};
