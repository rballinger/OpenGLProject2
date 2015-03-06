/*
 * Island.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: dan
 */

#include "Island.h"

Island::Island()
{
    outerRadius = 24.0;
    innerRadius = 19.0;
}

void Island::build ()
{
    const int NUM_SPOKES = 6;
    static float CHROME_AMBIENT[] = {0.25, 0.25, 0.25, 1};
    static float CHROME_DIFFUSE[] = {0.4, 0.4, 0.4, 1.0};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    static float GRASS_AMBIENT[] = {0.021500, 0.174500, 0.021500, 0.550000};
    static float GRASS_DIFFUSE[] = {0.075680, 0.614240, 0.075680, 0.550000};
    static float GRASS_SPECULAR[] = {0.633000, 0.727811, 0.633000, 0.550000};

    grass = gluNewQuadric();
    innerCurb = gluNewQuadric();
    outerCurb = gluNewQuadric();
    topCurb = gluNewQuadric();

    list_id = glGenLists(1);
    glNewList (list_id, GL_COMPILE);

    glPushMatrix();
    glRotatef (90, 1, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 9.846150);

    glPushMatrix();
    glTranslatef(0.0,-22.0,-12.0);
    glRotatef (90, 1, 0, 0);
    glRotatef (45, 0, 0, 1);
    gluCylinder(innerCurb, innerRadius, innerRadius, 3, 4, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-22.0,-12.0);
    glRotatef (90, 1, 0, 0);
    glRotatef (45, 0, 0, 1);
    gluCylinder(outerCurb, outerRadius, outerRadius, 3, 4, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-22.0,-12.0);
    glRotatef (-90, 1, 0, 0);
    glRotatef (45, 0, 0, 1);
    gluPartialDisk(topCurb, innerRadius, outerRadius, 4, 14, 0, 360);
    glPopMatrix();

    // change color to green for grass
    glMaterialfv(GL_FRONT, GL_AMBIENT, GRASS_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, GRASS_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, GRASS_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 9.846150);

    glPushMatrix();
    glTranslatef(0.0,-23.5,-12.0);
    glRotatef (-90, 1, 0, 0);
    glRotatef (45, 0, 0, 1);
    gluPartialDisk(grass, 0.0, innerRadius + 0.1, 4, 14, 0, 360);
    glPopMatrix();

    glPopMatrix();
    glEndList();
};

void Island::render() const {
    glCallList(list_id);
};
