/**
 * Example of 3D object animation
 *
 * Hans Dulimarta
 * dulimar@cis.gvsu.edu
 */

#ifdef WIN32    /* in windows I'm using the static library */
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shapes/Cylinder.h"    /* using C::B in windows, must be named with directory */
#include "Shapes/Sphere.h"
#include "Shapes/Fan.h"
#else
#include <GL/glew.h>
#include "Cylinder.h"
#include "Sphere.h"
#include "Fan.h"
#endif
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <cstdlib>
#include <cstdio>
#include "StreetLight.h"
#include "Island.h"
#include "UFO.h"
#include "Car.h"
#include "WeatherVaneBase.h"
#include "VaneSwivel.h"
#include "Ground.h"

using namespace std;
void displayCallback(GLFWwindow*);

/* define global variables here */
//Tire* tire;
Sphere sphere, light;
StreetLight streetLight;
Sphere lamp;
Island island;
UFO *ufo;
UFO *miniUFO1;
UFO *miniUFO2;

Car car;

Fan *fan;
WeatherVaneBase vaneBase;
VaneSwivel *swivel;

Ground *ground;

glm::mat4 wheel_cf;
glm::mat4 lamp_cf;
glm::mat4 ufo_cf, minUfo1_cf, minUfo2_cf;
glm::mat4 car_cf;
glm::mat4 vaneBase_cf, fan_cf, swivel_cf, swivel_and_fan_cf;
glm::mat4 frame_cf;
glm::mat4 camera_cf, light0_cf;
glm::mat4 *active;

float x_prev = 0.0;
float y_prev = 0.0;

// mini ufos
float min_x1_prev = 0.0;
float min_y1_prev = 0.0;
float min_x2_prev = 0.0;
float min_y2_prev = 0.0;

float ellipse_angle = 0.0;
float min1_ellipse_angle = 0.0;
float min2_ellipse_angle = 2.0;

// these are here to control the speed of ufos when selected
float ellipse_angle_change = 1.0;
float min1_ellipse_angle_change = 1.0;
float min2_ellipse_angle_change = 1.0;

const float INIT_SWING_ANGLE = 35.0f; /* degrees */
const float GRAVITY = 9.8;   /* m/sec^2 */
bool is_anim_running = true;

// weathervane swivel speed
float SWIVEL_SPEED = 0;
float d_swiv_speed = 70.0;

// weathvane fan speed
float FAN_SPEED = 44; /* in degrees per second */

float car_speed = 0;

/* light source setting */
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
GLfloat light1_color[] = {0.0, 3.0, 0.0, 1.0};   /* green color */
GLfloat black_color[] = {0.0, 0.0, 0.0, 1.0};   /* color */

/*--------------------------------*
 * GLUT Reshape callback function *
 *--------------------------------*/
void reshapeCallback (GLFWwindow *win, int w, int h)
{
    glViewport (0, 0, w, h);

    /* switch to Projection matrix mode */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    gluPerspective (60, (float) w / (float) h, 5.0, 2000.0);

    /* switch back to Model View matrix mode */
    glMatrixMode (GL_MODELVIEW);
    //camera_cf = glm::lookAt(glm::vec3(260,90,180), glm::vec3(0,0,0), glm::vec3(0,0,1));

    camera_cf = glm::lookAt(glm::vec3(110,140,90), glm::vec3(0,0,0), glm::vec3(0,0,1));

}

/*================================================================*
 * Idle Callback function. This is the main engine for simulation *
 *================================================================*/
void updateCoordFrames()
{
    static double last_timestamp = 0;
    static float swivel_angle = 0;
    static float fan_angle = 0;
    static int deg = 0;
    float delta, swivel_delta, current;


    static float majAxis = 180.0;
    static float minorAxis = 60.0;

    static float min1_majAxis = 60.0;
    static float min1_minorAxis = 19.0;

    // ellipse x = a cos t
    // 		   y = b sin t
    current = glfwGetTime();
    if (is_anim_running) {
        delta = (current - last_timestamp);
        swivel_delta = (current - last_timestamp);
        fan_angle = FAN_SPEED * delta;
        fan_cf *= glm::rotate(glm::radians(fan_angle), glm::vec3{0.0f, 1.0f, 0.0f});

        if(SWIVEL_SPEED >= 100){
        	d_swiv_speed = -70.0;
        }else if( SWIVEL_SPEED <= -100){
        	d_swiv_speed = 70.0;
        }

        SWIVEL_SPEED += d_swiv_speed*delta;

        swivel_angle = SWIVEL_SPEED * swivel_delta;
        swivel_cf *= glm::rotate(glm::radians(swivel_angle),glm::vec3{0.0f, 0.0f, 1.0f});

        float x = majAxis*cos(ellipse_angle);
        float y = minorAxis*sin(ellipse_angle);

        if(ellipse_angle == 0.0){
        	x = y = 0.0;
        }

        ellipse_angle += ellipse_angle_change*delta;

        ufo_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{x - x_prev,0.0,0.0});
        ufo_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,y - y_prev,0.0});

        x_prev = x;
        y_prev = y;

        // min orbiting ufos handled here
        // ONE
        float min1_x = min1_majAxis*cos(min1_ellipse_angle);
        float min1_y = min1_minorAxis*sin(min1_ellipse_angle);

        if(min1_ellipse_angle == 0.0){
        	min1_x = min1_y = 0.0;
        }

        min1_ellipse_angle += min1_ellipse_angle_change*delta;

        minUfo1_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,min1_x - min_x1_prev,0.0});
        minUfo1_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,0.0, min1_y - min_y1_prev});

        min_x1_prev = min1_x;
        min_y1_prev = min1_y;

        // TWO
        float min2_x = min1_majAxis*cos(min2_ellipse_angle);
        float min2_y = min1_minorAxis*sin(min2_ellipse_angle);

        if(min2_ellipse_angle == 0){
        	min2_ellipse_angle= 0;
        }

        min2_ellipse_angle += min2_ellipse_angle_change*delta;

    	minUfo2_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{min2_x - min_x2_prev, 0.0,0.0});
    	minUfo2_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,0.0, min2_y - min_y2_prev});

        min_x2_prev = min2_x;
        min_y2_prev = min2_y;
    }
    last_timestamp = current;
}

void myGLInit ()
{
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f); /* black background */

    /* fill front-facing polygon */
    glPolygonMode (GL_FRONT, GL_FILL);
    /* draw outline of back-facing polygon */
    glPolygonMode (GL_BACK, GL_LINE);

    /* Enable depth test for hidden surface removal */
    glEnable (GL_DEPTH_TEST);

    /* enable back-face culling */
    glEnable (GL_CULL_FACE);
    //glCullFace (GL_BACK);

    /* Enable shading */
    glEnable (GL_LIGHTING);
    glEnable (GL_NORMALIZE); /* Tell OpenGL to renormalize normal vector
                              after transformation */
    // sun
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0_color);

    // street lamp light
    glEnable (GL_LIGHT2);
    glLightfv (GL_LIGHT2, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT2, GL_SPECULAR, light0_color);
    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, 80);

    glEnableClientState(GL_VERTEX_ARRAY);
}

/*--------------------------------*
 * GLUT display callback function *
 *--------------------------------*/
void displayCallback (GLFWwindow *win)
{
    /* clear the window */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadMatrixf(glm::value_ptr(camera_cf));

    glBegin (GL_LINES);
    glColor3ub (255, 0, 0);
    glVertex3i (0, 0, 0);
    glVertex3i (5, 0, 0);
    glColor3ub (0, 255, 0);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 25, 0);
    glColor3ub (0, 0, 255);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 0, 15);
    glEnd();

    /* Specify the reflectance property of the ground using glColor
       (instead of glMaterial....)
     */
    glEnable (GL_COLOR_MATERIAL);
    glColor3ub (30, 30, 30);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColorMaterial(GL_FRONT, GL_SPECULAR);

    const float GROUND_SIZE = 500.0;

    /*glPushMatrix();
    glTranslatef(-GROUND_SIZE / 1.5, -GROUND_SIZE / 1.5, 0);

    for(float i = 0; i < GROUND_SIZE; i = i + 5){
        glBegin (GL_QUAD_STRIP);
        for(float j = 0; j < GROUND_SIZE; j = j + 5){
            glNormal3f (0.0f, 0.0f, 1.0f); // normal vector for the ground
            glVertex2f (i, j);
            glNormal3f (0.0f, 0.0f, 1.0f); // normal vector for the ground
            glVertex2f (i + 5, j);
        }
        glEnd();
    }
    glPopMatrix();
    glDisable (GL_COLOR_MATERIAL);
*/

    // ground class
    glPushMatrix();
    glTranslatef(0, 0.0f,5.0);
    ground->render();
    glPopMatrix();

    glDisable (GL_COLOR_MATERIAL);

    glLightfv (GL_LIGHT2, GL_POSITION, glm::value_ptr(glm::column(lamp_cf, 3)));
    glLightfv (GL_LIGHT2, GL_SPOT_DIRECTION, glm::value_ptr(glm::vec3(0, 0, -1.0f)));

    /* place the light source in the scene. */
    glLightfv (GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::column(light0_cf, 3)));

    glTranslatef(0, -30.0f, 0);
    /* the curly bracket pairs below are only for readability */
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(light0_cf));

        /* Render light-0 as an emmisive object */
        if (glIsEnabled(GL_LIGHT0))
            glMaterialfv(GL_FRONT, GL_EMISSION, light0_color);

        glPushMatrix();
        glTranslatef(-190.0f,-190.0f,7.0f);
        sphere.render(16.0f, 16.0f, 15.0f);
        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_EMISSION, black_color);
    }
    glPopMatrix();

    /* the curly bracket pairs below are only for readability */
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(lamp_cf));

        /* Render light-0 as an emmisive object */
        if (glIsEnabled(GL_LIGHT2))
            glMaterialfv(GL_FRONT, GL_EMISSION, light0_color);
        glPushMatrix();
        glTranslatef(0.0f,28.0f,22.0f);
        lamp.render(2.0f, 2.0f, 2.0f);
        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_EMISSION, black_color);
    }
    glPopMatrix();

    /* render static objects: streetLight and island **/
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(frame_cf));
        streetLight.render();
        island.render();
    }
    glPopMatrix();

    /* the curly bracket pairs below are only for readability */
    glPushMatrix();
    {
    	glMultMatrixf(glm::value_ptr(ufo_cf));
        ufo->render();
        glPushMatrix();
        {
        	glMultMatrixf(glm::value_ptr(minUfo1_cf));
        	miniUFO1->render();
        }
        glPopMatrix();

        glPushMatrix();
        {
        	glMultMatrixf(glm::value_ptr(minUfo2_cf));
        	miniUFO2->render();
        }
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    {
    	glMultMatrixf(glm::value_ptr(vaneBase_cf));
    	vaneBase.render();

        glPushMatrix();
        {
			glMultMatrixf(glm::value_ptr(swivel_and_fan_cf));
			glPushMatrix();
			{
				glMultMatrixf(glm::value_ptr(swivel_cf));
				swivel->render();
				glPushMatrix();
				{
					glMultMatrixf(glm::value_ptr(fan_cf));
					fan->render();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
    }
    glPopMatrix();

    // place car
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(car_cf));
        car.render();
    }
    glPopMatrix();

    /* to make smooth transition between frame */
    glfwSwapBuffers(win);
}

void myModelInit ()
{
    sphere.build(35, 20);

    fan = new Fan();
    fan->build(1,20.0);

    swivel = new VaneSwivel();
    swivel->build();

    vaneBase.build();

    ufo = new UFO();
    ufo->build(0.0, 0.0,100.0,1.0);
    miniUFO1 = new UFO();
    miniUFO1->build(0.0, 120.0,700.0,0.2);

    miniUFO2 = new UFO();
    miniUFO2->build(100.0, 120.0,790.0,0.2);

    light.build(35, 40);
    island.build();

    ufo_cf = glm::translate(glm::vec3{0.0f, 70.0f, 50.0f});
    minUfo1_cf = glm::translate(glm::vec3{0.0f, 0.0f, 0.0f});
    minUfo2_cf = glm::translate(glm::vec3{-25.0f, 20.0f, 0.0f});

    fan_cf = glm::translate(glm::vec3{0.0f, 19.0f, 0.0f});
    fan_cf *= glm::rotate(glm::radians(5.0f), glm::vec3{1,0,0});
    swivel_cf = glm::translate(glm::vec3{10.0f, 10.5f, 42.0f});

    swivel_and_fan_cf = glm::translate(glm::vec3{0.0f, 0.0f, 0.0f});

    vaneBase_cf = glm::translate(glm::vec3{0.0f, -260.0f, 39.5f});

    streetLight.build();

    lamp.build(35, 40);

    car.build();
    car_cf = glm::translate(glm::vec3(20, 35, 0));

    frame_cf = glm::translate(glm::vec3{0, 0 , 25});
    active = &camera_cf;		// camera frame is initially active

    light0_cf = glm::translate(glm::vec3{-450, -30, 106});

    lamp_cf = glm::translate(glm::vec3{0, 0, 10});

    ground = new Ground();
    ground->build();
}

void keyCallback (GLFWwindow *win, int key, int scan_code, int action, int mods) {
    if (action == GLFW_RELEASE){
        // stop car instantly once forward or reverse key is released
        if(key == GLFW_KEY_W || key == GLFW_KEY_S)
            car_speed = 0;
        return; /* ignore key release action */
    }

    // 6 degrees of freedom for camera frame
    if (mods == GLFW_MOD_SHIFT) {
        switch (key) {
        	// x axis
            case GLFW_KEY_UP: /* tilt */
                *active *= glm::rotate(glm::radians(-3.0f), glm::vec3{1.0f, 0.0f, 0.0f});
                break;
            case GLFW_KEY_DOWN: /* tilt */
                *active *= glm::rotate(glm::radians(+3.0f), glm::vec3{1.0f, 0.0f, 0.0f});
                break;

            // y axis
            case GLFW_KEY_LEFT: /* pan left */
                *active *= glm::rotate(glm::radians(-3.0f), glm::vec3{0.0f, 1.0f, 0.0f});
                break;
            case GLFW_KEY_RIGHT: /* pan right */
                *active *= glm::rotate(glm::radians(+3.0f), glm::vec3{0.0f, 1.0f, 0.0f});
                break;

            // z axis
            case GLFW_KEY_L: /* roll left */
                *active *= glm::rotate(glm::radians(-3.0f), glm::vec3{0.0f, 0.0f, 1.0f});
                break;
            case GLFW_KEY_R: /* roll right */
                *active *= glm::rotate(glm::radians(+3.0f), glm::vec3{0.0f, 0.0f, 1.0f});
                break;

            // positive directions
            case GLFW_KEY_X:
                *active *= glm::translate(glm::vec3{5, 0, 0});
                break;
            case GLFW_KEY_Y:
                *active *= glm::translate(glm::vec3{0, 5, 0});
                break;
            case GLFW_KEY_Z:
                *active *= glm::translate(glm::vec3{0, 0, -5});
                break;

            // negative directions
            case GLFW_KEY_I:
                *active *= glm::translate(glm::vec3{-5, 0, 0});
                break;
            case GLFW_KEY_J:
                *active *= glm::translate(glm::vec3{0, -5, 0});
                break;
            case GLFW_KEY_K:
                *active *= glm::translate(glm::vec3{0, 0, 5});
                break;
            case GLFW_KEY_0:
            	if(*active == ufo_cf){  // mother-ship faster
            		ellipse_angle_change += 0.01;
            	}else if(*active == minUfo1_cf){		// mini ufo 1 faster
            		min1_ellipse_angle_change += 0.01;
            	}else if(*active == minUfo2_cf){		// mini ufo 2 faster
            		min2_ellipse_angle_change += 0.01;
            	}
                break;
            case GLFW_KEY_F:
            	FAN_SPEED += 5;
            	break;
            case GLFW_KEY_G:
            	FAN_SPEED -= 5;
            	break;
            case GLFW_KEY_S:
            	if(d_swiv_speed <= 0){
            		SWIVEL_SPEED += 20;
            	}else{
            		SWIVEL_SPEED -= 20;
            	}
            	break;
            case GLFW_KEY_D:
            	if(d_swiv_speed <= 0){
            		SWIVEL_SPEED += 20;
            	}else{
            		SWIVEL_SPEED -= 20;
            	}
            	break;
            case GLFW_KEY_1:
            	if(*active == ufo_cf){  // mother-ship slower
            		ellipse_angle_change -= 0.01;
            	}else if(*active == minUfo1_cf){		// mini ufo 1 slower
            		min1_ellipse_angle_change -= 0.01;
            	}else if(*active == minUfo2_cf){		// mini ufo 2 slower
            		min2_ellipse_angle_change -= 0.01;
            	}
            	break;

            default:
                break;
        };
    }
    // controls movement of other objects
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                exit(0);
            case GLFW_KEY_0:
            	active = &light0_cf;
                if (glIsEnabled(GL_LIGHT0))
                    glDisable(GL_LIGHT0);
                else
                    glEnable(GL_LIGHT0);
                break;
            case GLFW_KEY_1:
                // not used currently
                break;
            case GLFW_KEY_2:
            	active = &lamp_cf;
                if (glIsEnabled(GL_LIGHT2))
                    glDisable(GL_LIGHT2);
                else
                    glEnable(GL_LIGHT2);
                break;
            case GLFW_KEY_4:
                if (glIsEnabled(GL_LIGHT4))
                    glDisable(GL_LIGHT4);
                else
                    glEnable(GL_LIGHT4);
                break;
            case GLFW_KEY_5:
                if (glIsEnabled(GL_LIGHT5))
                    glDisable(GL_LIGHT5);
                else
                    glEnable(GL_LIGHT5);
                break;
            case GLFW_KEY_SPACE: /* pause and restart the animation */
                is_anim_running ^= true;
                break;
            case GLFW_KEY_C:
                active = &camera_cf;
                break;
            case GLFW_KEY_U:
                active = &ufo_cf;
                break;
            case GLFW_KEY_F:
                active = &minUfo1_cf;
                break;
            case GLFW_KEY_O:
                active = &minUfo2_cf;
                break;
            case GLFW_KEY_V:
            	active = &fan_cf;
            	break;
            case GLFW_KEY_B:
            	active = &swivel_cf;
            	break;
            // car controls
            case GLFW_KEY_T:
                active = &car_cf;
                break;
            case GLFW_KEY_W:
                if(*active == car_cf){
                    car_speed -= 0.1;
                    *active *= glm::translate(glm::vec3(0, car_speed, 0));
                    // rotate tires forwards
                    car.rotate_wheels(-car_speed);
                }
                break;
            case GLFW_KEY_S:
                if(*active == car_cf){
                    car_speed += 0.1;
                    *active *= glm::translate(glm::vec3(0, car_speed, 0));
                    car.rotate_wheels(-car_speed);
                }
                break;
            /* TODO */
            // set active coordinate frames for new objects and lights
        }
    }
}

int main (int argc, char **argv)
{
    glfwInit();
    GLFWwindow *win;
    win = glfwCreateWindow(100, 50, "Animation", NULL, NULL);

    glfwMakeContextCurrent(win);
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n",
                glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }

    srand (time(0));

    myGLInit ();
    myModelInit ();

    /* setup display callback function */
    glfwSetFramebufferSizeCallback(win, reshapeCallback);
    glfwSetWindowRefreshCallback(win, displayCallback);
    glfwSetKeyCallback(win, keyCallback);
    glfwSetWindowSize(win, 1000, 700);

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        updateCoordFrames();
        displayCallback(win);
    }
    glfwDestroyWindow(win);
    glfwTerminate();

}
