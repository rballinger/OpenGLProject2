/*
 * Ground.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: dan
 */

#include "Ground.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

Ground::Ground()
{

}

Ground::~Ground()
{

}


void Ground::build () {

	int i = 0;
	float depth = 0.0;

	// two normals for corner vertices of large end of fan blade
	glm::vec3 topFaceNorm = glm::normalize(glm::vec3{0.0,0.0,-1.0});

	int subDivY = 100;
	int subDivX = 100;

	float x = 0.0;
	float y = 0.0;

	for(int i = 0; i < subDivX; i += 1){
		for(int j = 0; j < subDivY; j += 1){
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0.0);
			normals.push_back(topFaceNorm.x);
			normals.push_back(topFaceNorm.y);
			normals.push_back(topFaceNorm.z);
			y += 0.005;
		}
		y = 0.0;
		x += 0.005;
	}

	int j = 0, k = 0;
	for(int i = 0; i < subDivX - 1; i++){
		for(int y = 0; y < subDivY - 1; y++){
			indices.push_back(j + subDivY);
			indices.push_back(j + subDivY + 1);
			indices.push_back(k + 1);
			indices.push_back(k);
			j++;
			k++;
		}
	}

	cout << indices.size() << " " << vertices.size() << " " << endl;

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

void Ground::render() const {

	glPushMatrix();
	glRotatef(0.0, 1,0,0);
	glTranslatef(-300.0,-330.0,-5.0);
	glScalef(1000.0f,1000.0f,1.0f);
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    static float CHROME_AMBIENT[] = {0.20, 0.20, 0.20, 1};
    static float CHROME_DIFFUSE[] = {0.4, 0.4, 0.4, 1.0};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 100.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	glDrawElements (GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, 0);		// goes by point in space!!!
	glPopMatrix();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
