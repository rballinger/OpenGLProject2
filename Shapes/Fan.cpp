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
	float depth = 0.0;

	vector<float> smallEndPoints = {-2.0,-1.0, 0.0, 1.0, 2.0, 2.0, 1.0, 0.0, -1.0};
	vector<float> largeEndPoints = {-4.0,-2.0, 0.0, 2.0, 4.0, 4.0, 2.0, 0.0, -2.0};


	for(int i = 0; i < smallEndPoints.size(); i++){
		if(i == 5){
			depth = -1.0;
		}
		vertices.push_back(smallEndPoints[i]);
		vertices.push_back(0.0);
		vertices.push_back(depth);
	}
	depth = 0.0;
	for(int i = 0; i < largeEndPoints.size(); i++){
		if(i == 5){
			depth = -1.0;
		}
		vertices.push_back(largeEndPoints[i]);
		vertices.push_back(30.0);
		vertices.push_back(depth);
	}

	int j = largeEndPoints.size();
	for(i = 0; i < 8; i++){
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(j + 1);
		indices.push_back(j);
		j++;
	}

	indices.push_back(8);
	indices.push_back(0);
	indices.push_back(9);
	indices.push_back(17);

	indices.push_back(8);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(9);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(17);
	/*float subDiv = 30;
	float interpFact = 1/subDiv;

	glm::vec3 frontCornerOne = {-2.0, 0.0, 0.0};
	glm::vec3 frontCornerTwo = {2.0, 0.0, 0.0};
	glm::vec3 frontCornerThree = {1.0, 0.0, -1.0};
	glm::vec3 frontCornerFour = {-2.0, 0.0, -1.0};

	glm::vec3 backCornerOne = {-4.0, 30.0, 0.0};
	glm::vec3 backCornerTwo = {4.0, 30.0, 0.0};
	glm::vec3 backCornerThree = {2.0, 30.0, -1.0};
	glm::vec3 backCornerFour = {-4.0, 30.0, -1.0};

	// lines between the back and front four corners
	glm::vec3 interpCornerOne = (backCornerOne - frontCornerOne)*interpFact;
	glm::vec3 interpCornerTwo = (backCornerTwo - frontCornerTwo)*interpFact;
	glm::vec3 interpCornerThree = (backCornerThree - frontCornerThree)*interpFact;
	glm::vec3 interpCornerFour = (backCornerFour - frontCornerFour)*interpFact;

	float currY = 0.0;
	float newXPoint = 0.0;

	for(int i = 0; i < 30; i++){
		for(int j = 0; j < smallEndPoints.size(); j++){
			if(j > 0 && j % 5 == 0){
				depth = -1.0;
			}else if(j > 0 && j % smallEndPoints.size() == 0){
				depth = 0.0;
			}
			newXPoint = smallEndPoints[j];
			vertices.push_back(newXPoint);
			vertices.push_back(currY);
			vertices.push_back(depth);
		}
		currY += 1.0;  // Fan will be 30.0 units long
		for(int k = 0; k < smallEndPoints.size(); k++){
			smallEndPoints[k] = smallEndPoints[k]*(1.0 + interpFact);
		}
	}

	int j = smallEndPoints.size();
	for(i = 0; i < subDiv*2; i++){
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(j + 1);
		indices.push_back(j);
		j++;

	}

	indices.push_back(8);
	indices.push_back(0);
	indices.push_back(9);
	indices.push_back(17);

	indices.push_back(8);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(9);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(17);*/

	// two normals for corner vertices of small end of fan blade
	glm::vec3 smallFaceNorm = glm::normalize(glm::vec3{0.0,-1.0,0.0});

	// two normals for corner vertices of large end of fan blade
	glm::vec3 largeFaceNorm = glm::normalize(glm::vec3{0.0,1.0,0.0});

	// two normals for corner vertices of large end of fan blade
	glm::vec3 bottomFaceNorm = glm::normalize(glm::vec3{0.0,0.0,-1.0});

	// two normals for corner vertices of large end of fan blade
	glm::vec3 topFaceNorm = glm::normalize(glm::vec3{0.0,0.0,1.0});

	// two normals for  vertices of slanted face of fan blade
	glm::vec3 sloped1 = glm::vec3{largeEndPoints[17], 30.0, -1.0} - glm::vec3{largeEndPoints[8], 0.0, -1.0};
	glm::vec3 sloped2 = glm::vec3{largeEndPoints[8], 0.0, -1.0} - glm::vec3{largeEndPoints[0], 0.0, 0.0};
	glm::vec3 gradientFaceNorm = glm::normalize(glm::cross(sloped1, sloped2));

	// two normals for vertices of face opposite of slanted face of fan blade
	glm::vec3 opposite1 = glm::vec3{largeEndPoints[14], 30.0, -1.0} - glm::vec3{largeEndPoints[5], 0.0, -1.0};
	glm::vec3 opposite2 = glm::vec3{largeEndPoints[13], 30.0, -1.0} - glm::vec3{largeEndPoints[14], 30.0, -1.0};
	glm::vec3 oppositeFaceNorm = glm::normalize(glm::cross(opposite1, opposite2));

	// add to normal buffer
	// point 0
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 1
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 2
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 3
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 4
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 5
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 6
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 7
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 8
    normals.push_back(gradientFaceNorm.x);
    normals.push_back(gradientFaceNorm.y);
    normals.push_back(gradientFaceNorm.z);


	// point 9
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 10
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 11
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 12
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 13
    normals.push_back(topFaceNorm.x);
    normals.push_back(topFaceNorm.y);
    normals.push_back(topFaceNorm.z);

	// point 14
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 15
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 16
    normals.push_back(bottomFaceNorm.x);
    normals.push_back(bottomFaceNorm.y);
    normals.push_back(bottomFaceNorm.z);

	// point 17
    normals.push_back(gradientFaceNorm.x);
    normals.push_back(gradientFaceNorm.y);
    normals.push_back(gradientFaceNorm.z);


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
		glRotatef(15, 0,1,0);
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


