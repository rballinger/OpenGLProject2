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

	// NORMALS AT 45 DEGREE ANGLE (4)
	glm::vec3 one45 = glm::normalize(glm::vec3{-1.0, 0.0, 3.0} );
	glm::vec3 two45 = glm::normalize(glm::vec3{1.0, 0.0, 3.0} );
	glm::vec3 three45 = glm::normalize(glm::vec3{1.0, 0.0, -3.0} );
	glm::vec3 four45 = glm::normalize(glm::vec3{-1.0, 0.0, -3.0} );

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

			if(j == 0){
				normals.push_back(one45.x);
				normals.push_back(one45.y);
				normals.push_back(one45.z);
			}else if(j == 4){
				normals.push_back(two45.x);
				normals.push_back(two45.y);
				normals.push_back(two45.z);
			}else if(j == 5){
				normals.push_back(three45.x);
				normals.push_back(three45.y);
				normals.push_back(three45.z);
			}/*else if(j == 8){
				normals.push_back(four45.x);
				normals.push_back(four45.y);
				normals.push_back(four45.z);
			}*/

			/*if(j == 4){
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
			}*/

			// top face of fan blade
			if(j > 0 && j < 4){
				normals.push_back(topFaceNorm.x);
				normals.push_back(topFaceNorm.y);
				normals.push_back(topFaceNorm.z);
			}else if (j > 5 && j <= 8){ // bottom face of fan blade
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
		glDrawElements (GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, 0);		// goes by point in space!!!
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


