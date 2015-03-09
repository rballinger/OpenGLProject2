/*
 * WeatherVaneBase.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: dan
 */
#include "WeatherVaneBase.h"

void WeatherVaneBase::build() {
	legOne.build(1.0,1.0,85.1);
	legTwo.build(1.0,1.0,85.1);
	legThree.build(1.0,1.0,85.1);
	legFour.build(1.0,1.0,85.1);

    smallSquareOne.build(1.0,1.0,15.1);
    smallSquareTwo.build(1.0,1.0,15.1);
    smallSquareThree.build(1.0,1.0,15.1);
    smallSquareFour.build(1.0,1.0,15.1);

    largeSquareOne.build(1.0,1.0,35.1);
    largeSquareTwo.build(1.0,1.0,35.1);
    largeSquareThree.build(1.0,1.0,35.1);
    largeSquareFour.build(1.0,1.0,35.1);
}

void WeatherVaneBase::render() const {
    static float CHROME_AMBIENT[] = {0.250000, 0.250000, 0.250000, 1.000000};
    static float CHROME_DIFFUSE[] = {0.400000, 0.400000, 0.400000, 1.000000};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);

	glPushMatrix();
	glTranslatef (0, 0, 0);
	glRotatef(-15.0,1,0,0);
	glRotatef(15.0,0,1,0);
	legOne.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef (0, 22, 0);
	glRotatef(15.0,1,0,0);
	glRotatef(15.0,0,1,0);
	legTwo.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef (22, 0, 0);
	glRotatef(-15.0,1,0,0);
	glRotatef(-15.0,0,1,0);
	legThree.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef (22, 22, 0);
	glRotatef(15.0,1,0,0);
	glRotatef(-15.0,0,1,0);
	legFour.render();
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef (-17.7, -11, 15.0);

		glPushMatrix();
		glTranslatef (22, 22, 0);
		glRotatef(90.0,1,0,0);
		smallSquareOne.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (28.7, 28.7, 0);
		glRotatef(90.0,0,0,1);
		glRotatef(90.0,1,0,0);
		smallSquareTwo.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (28.7, 15.3, 0);
		glRotatef(90.0,0,0,1);
		glRotatef(90.0,1,0,0);
		smallSquareThree.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (35.3, 22, 0);
		glRotatef(90.0,1,0,0);
		smallSquareFour.render();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef (-17.7, -11, -23.0);

		glPushMatrix();
		glTranslatef (11.5, 22, 0);
		glRotatef(90.0,1,0,0);
		largeSquareOne.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (28.7, 39.0, 0);
		glRotatef(90.0,0,0,1);
		glRotatef(90.0,1,0,0);
		largeSquareTwo.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (28.7, 5, 0);
		glRotatef(90.0,0,0,1);
		glRotatef(90.0,1,0,0);
		largeSquareThree.render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef (45.3, 22, 0);
		glRotatef(90.0,1,0,0);
		largeSquareFour.render();
		glPopMatrix();
	}
	glPopMatrix();

};
