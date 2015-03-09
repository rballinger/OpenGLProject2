/*
 * Fan.cpp
 *
 *  Created on: Mar 7, 2015
 *      Author: dan
 */
#include "Fan.h"
#include <cmath>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

Fan::Fan()
{
	POINTS = 12;
    radius = 6.0;
}

Fan::~Fan()
{

}

void Fan::build (int numFans, float thickness) {
	LENGTH = thickness;
    const int NUM_SPOKES = 12;
    radius = 5.5;
    tire_thickness = 0.4;

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

	norm = glm::normalize(glm::vec3{-4.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 11
	vertices.push_back(-2.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{-2.0, 30.0, 0.0});
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

	norm = glm::normalize(glm::vec3{2.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 14
	vertices.push_back(4.0);
	vertices.push_back(30.0);
	vertices.push_back(0.0);

	norm = glm::normalize(glm::vec3{4.0, 30.0, 0.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 15
	vertices.push_back(4.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{4.0, 30.0, -1.0});
	normals.push_back(norm.x);
	normals.push_back(norm.y);
	normals.push_back(norm.z);

	// 16
	vertices.push_back(2.0);
	vertices.push_back(30.0);
	vertices.push_back(-1.0);

	norm = glm::normalize(glm::vec3{2.0, 30.0, -1.0});
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

	norm = glm::normalize(glm::vec3{-2.0, 30.0, -1.0});
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

    spoke = gluNewQuadric();

    list_id = glGenLists(1);
    glNewList (list_id, GL_COMPILE);
    glPushMatrix();
    glRotatef (90, 1, 0, 0);

//    glColor3ub (70,40, 40);
    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);
    /* make the spokes */
    for (int k = 0; k < NUM_SPOKES; k++)
    {
        float angle = k * 360.0 / NUM_SPOKES;
        glPushMatrix();
        glRotatef (angle, 0, 1, 0);
        gluCylinder(spoke, 0.75 * tire_thickness, 0.75 * tire_thickness, radius, 10, 3);
        glPopMatrix();
    }
    /* make the hub */
    glPushMatrix();
    glTranslatef (0, 0, -tire_thickness/2);
    glScalef (0.3 * radius, 0.3 * radius, tire_thickness);
//    spoke->draw();
    glPopMatrix();
    glPopMatrix();
    glEndList();

    glPushMatrix();
    vaneRim.build(17.0,17.0,2.0);
    glPopMatrix();

}

void Fan::render() const {

	glPushMatrix();
	//glRotatef (15, 1, 0, 0);

    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    static float COPPER_AMBIENT[] = {0.191250, 0.073500, 0.022500, 1.000000};
    static float COPPER_DIFFUSE[] = {0.703800, 0.270480, 0.082800, 1.000000};
    static float COPPER_SPECULAR[] = {0.256777, 0.137622, 0.086014, 1.000000};

    glMaterialfv(GL_FRONT, GL_AMBIENT, COPPER_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, COPPER_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, COPPER_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 12.800000);

    float angle = 0.0;
    float d_angle = 360/12.0;
	glPushMatrix();
	glRotatef (-90, 1, 0, 0);
    for(int i = 0; i < 12; i++){
		glPushMatrix();
		glRotatef(angle, 0,0,1);
		//glRotatef(15, 0,1,0);
		glTranslatef(0.0f,5.0f,0.0f);
		glDrawElements (GL_QUADS, 44, GL_UNSIGNED_SHORT, 0);		// goes by point in space!!!
		glPopMatrix();
		angle += d_angle;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();

    glCallList(list_id);

	glPushMatrix();
	//glTranslatef (0, 28, 8.0);
	vaneRim.render(false);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}


