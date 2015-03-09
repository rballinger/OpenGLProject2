/*
 * Tire.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: dan and ryan
 */
#include "Tire.h"
const float WIDTH = 3.0;

Tire::Tire()
{
    rubberTopRadius = 5.0;
    rubberBottomRadius = 5.0;
    wallInnerRadius = 2.6;
    wallOuterRadius = 5.0;

    nuts.push_back(nut1);
    nuts.push_back(nut2);
    nuts.push_back(nut3);
    nuts.push_back(nut4);
    nuts.push_back(nut5);
}

Tire::~Tire()
{

}

void Tire::build ()
{
    const int NUM_SPOKES = 6;
    static float CHROME_AMBIENT[] = {0.25, 0.25, 0.25, 1};
    static float CHROME_DIFFUSE[] = {0.4, 0.4, 0.4, 1.0};
    static float CHROME_SPECULAR[] = {0.774597, 0.774597, 0.774597, 1.000000};

    static float RIM_AMBIENT[] = {0.135000, 0.222500, 0.157500, 0.950000};
    static float RIM_DIFFUSE[] = {0.540000, 0.890000, 0.630000, 0.950000};
    static float RIM_SPECULAR[] = {0.316228, 0.316228, 0.316228, 0.950000};

    static float RUBBER_AMBIENT[] = {0.02, 0.02, 0.02, 1.0};
    static float RUBBER_DIFFUSE[] = {0.01, 0.01, 0.01, 1.0};
    static float RUBBER_SPECULAR[] = {0.4, 0.4, 0.4, 1.0};

    //38.400002 obsidian
    /*static float PIT_AMBIENT[] = {0.053750, 0.050000, 0.066250, 0.820000};
    static float PIT_DIFFUSE[] = {0.182750, 0.170000, 0.225250, 0.820000};
    static float PIT_SPECULAR[] = {0.332741, 0.328634, 0.346435, 0.820000};

    // pearl
    static float PIT_AMBIENT[] = {0.250000, 0.207250, 0.207250, 0.922000};
    static float PIT_DIFFUSE[] = {1.000000, 0.829000, 0.829000, 0.922000};
    static float PIT_SPECULAR[] = {0.296648, 0.296648, 0.296648, 0.922000};*/

    rubber = gluNewQuadric();
    outRubberWall = gluNewQuadric();
    inRubberWall = gluNewQuadric();

    list_id = glGenLists(1);
    glNewList (list_id, GL_COMPILE);

    glPushMatrix();

    glRotatef (90, 1, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, RUBBER_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, RUBBER_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, RUBBER_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);

    glPushMatrix();
    glRotatef (90, 1, 0, 0);
    glTranslatef(0.0,0,-1.5);

    gluCylinder(rubber, rubberTopRadius, rubberBottomRadius, WIDTH, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glRotatef (-90, 1, 0, 0);
    glTranslatef(0.0,0,1.5);
    gluPartialDisk(outRubberWall, wallInnerRadius, wallOuterRadius, 24, 24, 0, 360);
    glPopMatrix();

    glPushMatrix();
    glRotatef (90, 1, 0, 0);
    glTranslatef(0.0,0,1.5);

    gluPartialDisk(inRubberWall, wallInnerRadius, wallOuterRadius, 24, 24, 0, 360);
    glPopMatrix();

    // change color for hub
    glMaterialfv(GL_FRONT, GL_AMBIENT, CHROME_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CHROME_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CHROME_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS,  	12.800000);

    hub.build(wallInnerRadius, wallInnerRadius, WIDTH);

    for(int i = 0; i < nuts.size(); i++){
    	nuts[i].build(0.4,0.4,WIDTH + 0.2, 3);
    }

    glPopMatrix();
    glEndList();
};

void Tire::render() const {
    glPushMatrix();
    hub.render();
    glPopMatrix();

    glPushMatrix();
    float currAngle = 0;
    for(int i = 0; i < nuts.size(); i++){
        glPushMatrix();
        glTranslatef(cos(currAngle)*(wallInnerRadius - 1.5),sin(currAngle)*(wallInnerRadius - 1.5),0.3);
    	nuts[i].render();
    	glPopMatrix();
    	currAngle += d_angle;
    }
    glPopMatrix();

    glCallList(list_id);
};
