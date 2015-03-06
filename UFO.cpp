/*
 * UFO.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */

#include "UFO.h"

UFO::UFO()
{
    sphereRadius = 11.0;
    diskTopRadius = 4.0;
    diskBottomRadius = 41.0;
}

UFO::~UFO()
{

}

void UFO::build (float x, float y, float z)
{
	init_x = x;
	init_y = y;
    init_z = z;
    const int NUM_SPOKES = 6;
    static float CHROME_AMBIENT[] = {0.25, 0.25, 0.25, 1};
    static float CHROME_DIFFUSE[] = {0.4, 0.4, 0.4, 1.0};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    static float RIM_AMBIENT[] = {0.135000, 0.222500, 0.157500, 0.950000};
    static float RIM_DIFFUSE[] = {0.540000, 0.890000, 0.630000, 0.950000};
    static float RIM_SPECULAR[] = {0.316228, 0.316228, 0.316228, 0.950000};

    //38.400002 obsidian
    /*static float PIT_AMBIENT[] = {0.053750, 0.050000, 0.066250, 0.820000};
    static float PIT_DIFFUSE[] = {0.182750, 0.170000, 0.225250, 0.820000};
    static float PIT_SPECULAR[] = {0.332741, 0.328634, 0.346435, 0.820000};*/

    // pearl
    static float PIT_AMBIENT[] = {0.250000, 0.207250, 0.207250, 0.922000};
    static float PIT_DIFFUSE[] = {1.000000, 0.829000, 0.829000, 0.922000};
    static float PIT_SPECULAR[] = {0.296648, 0.296648, 0.296648, 0.922000};

    topDisk = gluNewQuadric();
    bottomDisk = gluNewQuadric();
    bottomDiskInside = gluNewQuadric();
    midRim = gluNewQuadric();
    cockPit = gluNewQuadric();

    list_id = glGenLists(1);
    glNewList (list_id, GL_COMPILE);

    glPushMatrix();
    glRotatef (90, 1, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 76.800003);

    glPushMatrix();
    glTranslatef(0.0 + init_x,42.5 + init_y,45.0  + init_z);
    glRotatef (90, 1, 0, 0);
    gluCylinder(topDisk, diskTopRadius, diskBottomRadius, 8, 24, 36);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0 + init_x,24.0 + init_y,45.0  + init_z);
    glRotatef (-90, 1, 0, 0);
    gluCylinder(bottomDisk, diskTopRadius, diskBottomRadius, 8, 24, 36);
    glPopMatrix();

    // change color
    glMaterialfv(GL_FRONT, GL_AMBIENT, RIM_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, RIM_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, RIM_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS,  	12.800000);

    glPushMatrix();
    glTranslatef(0.0,31.5,45.0  + init_z);
    glRotatef (-90, 1, 0, 0);
    gluCylinder(midRim, diskBottomRadius, diskBottomRadius, 3, 24, 18.5);
    glPopMatrix();

    // change color for cock pit
    glMaterialfv(GL_FRONT, GL_AMBIENT, PIT_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, PIT_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, PIT_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS,  	11.264000);

    glPushMatrix();
    glTranslatef(0.0,35,45.0  + init_z);
    glScalef(1.5,0.8,1.5);
    gluSphere(cockPit, sphereRadius, 24, 14);
    glPopMatrix();

    glPopMatrix();
    glEndList();
};

void UFO::render() const {
    glCallList(list_id);
};

