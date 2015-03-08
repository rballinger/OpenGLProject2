/*
 * Car.cpp
 *
 *  Created on: Mar 7, 2015
 *      Author: Ryan
 */
#include "Car.h"

void Car::build() {
    elbow.build(8, 1.0, 40, 40, 180);
}

void Car::render() const {
    static float CHROME_AMBIENT[] = {0.250000, 0.250000, 0.250000, 1.000000};
    static float CHROME_DIFFUSE[] = {0.400000, 0.400000, 0.400000, 1.000000};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);


	{
		glRotatef (90, 0, 1, 0);
		glRotatef (90, 0, 0, 1);
		glTranslatef (24, -2, 0);
		elbow.render();
		glPopMatrix();
	}
};
