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
	float depth = 0.0;

	vector<float> smallEndPoints = {-2.0,-1.0, 0.0, 1.0, 2.0, 2.0, 1.0, 0.0, -1.0};

	// two normals for corner vertices of large end of fan blade
	glm::vec3 bottomFaceNorm = glm::normalize(glm::vec3{0.0,0.0,-1.0});

	// two normals for corner vertices of large end of fan blade
	glm::vec3 topFaceNorm = glm::normalize(glm::vec3{0.0,0.0,1.0});

	// two normals for corner vertices of small end of fan blade
	glm::vec3 smallFaceNorm = glm::normalize(glm::vec3{0.0,-1.0,0.0});

	// two normals for corner vertices of large end of fan blade
	glm::vec3 largeFaceNorm = glm::normalize(glm::vec3{0.0,1.0,0.0});

	// two normals for  vertices of slanted face of fan blade
	glm::vec3 sloped1 = glm::vec3{0.0, 0.0, 0.0} - glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 sloped2 = glm::vec3{0.0, 0.0, 0.0} - glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 gradientFaceNorm = glm::normalize(glm::cross(sloped1, sloped2));

	// two normals for vertices of face opposite of slanted face of fan blade
	glm::vec3 opposite1 = glm::vec3{0.0, 0.0, 0.0} - glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 opposite2 = glm::vec3{0.0, 0.0, 0.0} - glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 oppositeFaceNorm = glm::normalize(glm::cross(opposite1, opposite2));

	float subDiv = 30;
	float interpFact = 1/subDiv;
	float currY = 0.0;
	float newXPoint = 0.0;

	float prev_currY = 0.0;
	float prev_newXPoint = 0.0;

	int j = 0;

	for(int i = 0; i < subDiv; i++){
		for(j = 0; j < smallEndPoints.size(); j++){
			if(j > 0 && j % 5 == 0){
				depth = -2.0;
			}else if(j > 0 && j % smallEndPoints.size() -1 == 0){
				depth = 0.0;
			}
			newXPoint = smallEndPoints[j];
			vertices.push_back(newXPoint);
			vertices.push_back(currY);
			vertices.push_back(depth);

			if(j == 4){
				if(j == 4  || j == 5){
					// thin face (not sloped)
					// two normals for vertices of face opposite of slanted face of fan blade
					opposite1 = glm::vec3{newXPoint, currY, depth} - glm::vec3{smallEndPoints[j + 1], currY, depth};
					opposite2 = glm::vec3{newXPoint*(1.0+interpFact), currY + 1.0, depth} - glm::vec3{newXPoint, currY, depth};
					oppositeFaceNorm = glm::normalize(glm::cross(opposite1, opposite2));
				}
				//normals.push_back(oppositeFaceNorm.x);
				//normals.push_back(oppositeFaceNorm.y);
				//normals.push_back(oppositeFaceNorm.z);
			}

			// top face of fan blade
			if(j >= 0 && j <= 4){
				normals.push_back(topFaceNorm.x);
				normals.push_back(topFaceNorm.y);
				normals.push_back(topFaceNorm.z);
			}else if (j >= 5){ // bottom face of fan blade
				normals.push_back(bottomFaceNorm.x);
				normals.push_back(bottomFaceNorm.y);
				normals.push_back(bottomFaceNorm.z);
			}

			//cout << "(" << newXPoint << ", " << currY << ", " << depth << ")";
		}
		prev_currY = currY;
		prev_newXPoint = newXPoint;
		//cout << endl;
		currY += 1.0;  // Fan will be 190.0 units long
		for(int k = 0; k < smallEndPoints.size(); k++){
			smallEndPoints[k] = smallEndPoints[k]*(1.0 + interpFact);
		}
		depth = 0.0;
	}

	j = smallEndPoints.size();
	for(i = 0; i < subDiv*9 - smallEndPoints.size(); i++){
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(j + 1);
		indices.push_back(j);
		j++;

	}

	int temp1 = 9;
	int temp2 = 1;
	// large end cap (4 squares)
	for(int i = 0; i < 4; i++){
		indices.push_back(j - temp1);
		indices.push_back(j - temp1 + 1);
		indices.push_back(j - temp2);
		indices.push_back(j - temp2 + 1);
		temp1--;
		temp2++;
		for(int j = 0; j < 4; j++){
			normals.push_back(largeFaceNorm.x);
			normals.push_back(largeFaceNorm.y);
			normals.push_back(largeFaceNorm.z);
		}
	}

	temp1 = 8;
	temp2 = 0;
	// small end cap (4 squares)
	for(int i = 0; i < 4; i++){
		indices.push_back(temp1 + 1);
		indices.push_back(temp1);
		indices.push_back(temp2 + 1);
		indices.push_back(temp2);
		temp1--;
		temp2++;
		for(int j = 0; j < 4; j++){
			normals.push_back(smallFaceNorm.x);
			normals.push_back(smallFaceNorm.y);
			normals.push_back(smallFaceNorm.z);
		}
	}


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
	glDrawElements (GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, 0);		// goes by point in space!!!
	glPopMatrix();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
