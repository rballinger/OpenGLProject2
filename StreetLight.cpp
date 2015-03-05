/*
 * StreetLight.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */
#include "StreetLight.h"

void StreetLight::build() {
	post.build(1.0,1.0,35.1);
	base.build(5.0,5.0,8.1);
    elbow.build(8, 1.0, 40, 40, 180);
    shade.build(1.0,5.0,4.1);
    lamp.build(35, 40);
}

void StreetLight::render() const {
    static float CHROME_AMBIENT[] = {0.250000, 0.250000, 0.250000, 1.000000};
    static float CHROME_DIFFUSE[] = {0.400000, 0.400000, 0.400000, 1.000000};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);

    glPushMatrix();
	glTranslatef(0.0f,-3.99f,12.0f);
	glPushMatrix();
	{
		glRotatef (90, 0, 1, 0);
		glRotatef (90, 0, 0, 1);
		glTranslatef (24, -2, 0);
		elbow.render();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef (0, 12, -22.5);
	base.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef (0, 12, -6.5);
	post.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef (0, 28, 8.0);
	shade.render();
	glPopMatrix();
};
