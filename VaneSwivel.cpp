/*
 * VaneSwivel.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: dan
 */
#include "VaneSwivel.h"
#include <cmath>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

VaneSwivel::VaneSwivel()
{
	POINTS = 12;
    radius = 6.0;
}

VaneSwivel::~VaneSwivel()
{

}

void VaneSwivel::build () {

	smallSwivel.build(2.0,2.0,21.1);
	largeSwivel.build(4.0,4.0,11.1);

    static float CHROME_AMBIENT[] = {0.25, 0.25, 0.25, 1};
    static float CHROME_DIFFUSE[] = {0.4, 0.4, 0.4, 1.0};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

	float end = 0.0;
	float scaler = 1.0;
	float z = 0.0;
	float x = -POINTS/2;

	int i = 0;

	// 0
	vertices.push_back(-2.0);
	vertices.push_back(0.0);
	vertices.push_back(0.0);

	glm::vec3 norm = glm::normalize(glm::vec3{-2.0, 0.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 1
	vertices.push_back(-1.0);
	vertices.push_back(0.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{-1.0, 0.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 2
	vertices.push_back(0.0);
	vertices.push_back(0.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{0.0, 0.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 3
	vertices.push_back(1.0);
	vertices.push_back(0.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{1.0, 0.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 4
	vertices.push_back(2.0);
	vertices.push_back(0.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{2.0, 0.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 5
	vertices.push_back(2.0);
	vertices.push_back(0.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{2.0, 0.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 6
	vertices.push_back(1.0);
	vertices.push_back(0.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{1.0, 0.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 7
	vertices.push_back(0.0);
	vertices.push_back(0.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{0.0, 0.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 8
	vertices.push_back(-1.0);
	vertices.push_back(0.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{-1.0, 0.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 9
	vertices.push_back(-2.0);
	vertices.push_back(0.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{-2.0, 0.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 10
	vertices.push_back(-4.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{-24.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 11
	vertices.push_back(-2.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{-12.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 12
	vertices.push_back(0.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{0.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 13
	vertices.push_back(2.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{12.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 14
	vertices.push_back(4.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{24.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 15
	vertices.push_back(4.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{24.0, 30.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 16
	vertices.push_back(2.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{12.0, 30.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 17
	vertices.push_back(0.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{0.0, 30.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 18
	vertices.push_back(-1.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{-12.0, 30.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(11);
	indices.push_back(10);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(12);
	indices.push_back(11);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(13);
	indices.push_back(12);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(14);
	indices.push_back(13);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(15);
	indices.push_back(14);

	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(16);
	indices.push_back(15);

	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(17);
	indices.push_back(16);

	indices.push_back(7);
	indices.push_back(8);
	indices.push_back(18);
	indices.push_back(17);

	indices.push_back(8);
	indices.push_back(0);
	indices.push_back(10);
	indices.push_back(18);

	indices.push_back(8);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(10);
	indices.push_back(14);
	indices.push_back(15);
	indices.push_back(18);


    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
            vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat),
            normals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort),
            indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VaneSwivel::render() const {

	glPushMatrix();
	glRotatef (-90, 1, 0, 0);
	glTranslatef (0, 0.0, 9.0);
	smallSwivel.render();
	glPopMatrix();

	glPushMatrix();
	glRotatef (-90, 1, 0, 0);

	largeSwivel.render();
	glPopMatrix();

    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0.0f,5.0f,0.0f);
	glDrawElements (GL_QUADS, 44, GL_UNSIGNED_SHORT, 0);		// goes by point in space!!!
	glPopMatrix();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
