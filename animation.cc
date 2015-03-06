/**
 * Example of 3D object animation
 *
 * Hans Dulimarta
 * dulimar@cis.gvsu.edu
 */
#include <GL/glew.h>
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include "StreetLight.h"
#include "Cylinder.h"
#include "Wheel.h"
#include "Sphere.h"
#include "Island.h"
#include "UFO.h"
#include "Tire.h"

using namespace std;
void displayCallback(GLFWwindow*);

/* define global variables here */
Wheel *wheel;
Tire* tire;
Sphere sphere, light;
StreetLight streetLight;
Sphere lamp;
Island island;
UFO *ufo;
UFO *miniUFO1;
UFO *miniUFO2;
UFO *miniUFO3;

glm::mat4 wheel_cf;
glm::mat4 lamp_cf;
glm::mat4 tire_cf;
glm::mat4 ufo_cf, minUfo1_cf, minUfo2_cf, minUfo3_cf;
glm::mat4 frame_cf;
glm::mat4 camera_cf, light0_cf, ufo_light_cf;
glm::mat4 *active;

float x_prev = 0.0;
float y_prev = 0.0;

// mini ufos
float min_x1_prev = 0.0;
float min_y1_prev = 0.0;
float min_x2_prev = 0.0;
float min_y2_prev = 0.0;
float min_x3_prev = 0.0;
float min_y3_prev = 0.0;

float ellipse_angle = 0.0;
float min1_ellipse_angle = 0.0;
float min2_ellipse_angle = 2.0;
float min3_ellipse_angle = 0.0;

const float INIT_SWING_ANGLE = 35.0f; /* degrees */
const float GRAVITY = 9.8;   /* m/sec^2 */
bool is_anim_running = true;

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
    camera_cf = glm::lookAt(glm::vec3(260,90,180), glm::vec3(0,0,0), glm::vec3(0,0,1));
}

/*================================================================*
 * Idle Callback function. This is the main engine for simulation *
 *================================================================*/
void updateCoordFrames()
{
    static double last_timestamp = 0;
    static float swing_time = 0;
    static float swing_angle = 0;
    static float ufo_angle = 0;
    static int deg = 0;
    const float UFO_SPEED = 144; /* in degrees per second */
    float delta, current;

    static float majAxis = 180.0;
    static float minorAxis = 60.0;

    static float min1_majAxis = 60.0;
    static float min1_minorAxis = 19.0;

    // ellipse x = a cos t
    // 		   y = b sin t
    current = glfwGetTime();
    if (is_anim_running) {
        //delta = (current - last_timestamp);
        //ufo_angle = UFO_SPEED * delta;
        //ufo_cf *= glm::rotate(glm::radians(ufo_angle), glm::vec3{0.0f, 0.0f, 1.0f});

        float x = majAxis*cos(ellipse_angle);
        float y = minorAxis*sin(ellipse_angle);

        if(ellipse_angle == 0.0){
        	x = y = 0.0;
        }
        ellipse_angle += 0.03;

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
        min1_ellipse_angle += 0.03;

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
        min2_ellipse_angle += 0.03;

    	minUfo2_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{min2_x - min_x2_prev, 0.0,0.0});
    	minUfo2_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,0.0, min2_y - min_y2_prev});

        min_x2_prev = min2_x;
        min_y2_prev = min2_y;

        // THREE

        /* use the pendulum equation to calculate its angle */
        /*swing_time += delta * 3;
        float angle = INIT_SWING_ANGLE * cos(swing_time * sqrt(GRAVITY / swingarm->length()));
        swing_arm_cf *= glm::rotate(glm::radians(angle - swing_angle), glm::vec3{0.0f, 1.0f, 0.0f});
        swing_angle = angle;*/
    }
    last_timestamp = current;
}

void myGLInit ()
{
    glClearColor (0.6f, 1.0f, 1.0f, 1.0f); /* black background */

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

    // ufo light
    /*glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light1_color);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_color);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light1_color);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 700);
*/
    // street lamp light
    glEnable (GL_LIGHT2);
    glLightfv (GL_LIGHT2, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT2, GL_SPECULAR, light0_color);

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
    glVertex3i (2, 0, 0);
    glColor3ub (0, 255, 0);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 2, 0);
    glColor3ub (0, 0, 255);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 0, 2);
    glEnd();

    /* Specify the reflectance property of the ground using glColor
       (instead of glMaterial....)
     */
    glEnable (GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3ub (30, 30, 30);

    glBegin (GL_QUADS);
    const int GROUND_SIZE = 300;
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (GROUND_SIZE, GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-GROUND_SIZE, GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-GROUND_SIZE, -GROUND_SIZE);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (GROUND_SIZE, -GROUND_SIZE);
    glEnd();
    glDisable (GL_COLOR_MATERIAL);

    /* place the light source in the scene. */
    glLightfv (GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::column(light0_cf, 3)));

    /* place the light source in the scene. */
    glLightfv (GL_LIGHT2, GL_POSITION, glm::value_ptr(glm::column(lamp_cf, 3)));

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

    /// light for UFO

    /* recall that the last column of a CF is the origin of the CF */
    glLightfv (GL_LIGHT1, GL_POSITION, glm::value_ptr(glm::column(ufo_light_cf, 3)));

    /* we use the Z-axis of the light CF as the spotlight direction */
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(glm::column(ufo_light_cf, 3)));

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
        /*glPushMatrix();
        {
        	glMultMatrixf(glm::value_ptr(minUfo3_cf));
        	miniUFO3->render();
        }
        glPopMatrix();*/
    }
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0,0.0,15.0);
    glRotatef (90, 0, 1, 0);
    tire->render();
    glPopMatrix();

    /* to make smooth transition between frame */
    glfwSwapBuffers(win);
}

void myModelInit ()
{
    sphere.build(35, 40);

    ufo = new UFO();
    ufo->build(0.0, 0.0,100.0,1.0);
    miniUFO1 = new UFO();
    miniUFO1->build(0.0, 120.0,700.0,0.2);

    miniUFO2 = new UFO();
    miniUFO2->build(100.0, 120.0,790.0,0.2);

	//miniUFO3 = new UFO();
	//miniUFO3->build(-100.0, 120.0,700.0,0.2);

    light.build(35, 40);
    island.build();

    tire = new Tire;
    tire->build();

    tire_cf = glm::translate(glm::vec3{0.0f, 0.0f, 10.0f});
    tire_cf *= glm::rotate(glm::radians(90.0f), glm::vec3{1,0,0});

    ufo_cf = glm::translate(glm::vec3{0.0f, 0.0f, 20.0f});
    minUfo1_cf = glm::translate(glm::vec3{0.0f, 0.0f, 0.0f});
    minUfo2_cf = glm::translate(glm::vec3{-25.0f, 20.0f, 0.0f});
    //minUfo3_cf = glm::translate(glm::vec3{0.0f, 0.0f, 0.0f});

    streetLight.build();
    lamp.build(35, 40);
    frame_cf = glm::translate(glm::vec3{0, 0 , 25});
    active = &camera_cf;

    light0_cf = glm::translate(glm::vec3{-450, -30, 106});

    lamp_cf = glm::translate(glm::vec3{0, 0, 10});
}

void keyCallback (GLFWwindow *win, int key, int scan_code, int action, int mods) {
    if (action == GLFW_RELEASE) return; /* ignore key release action */

    if (mods == GLFW_MOD_SHIFT) {
        switch (key) {
            case GLFW_KEY_UP: /* tilt */
                *active *= glm::rotate(glm::radians(-3.0f), glm::vec3{1.0f, 0.0f, 0.0f});
                break;
            case GLFW_KEY_DOWN: /* tilt */
                *active *= glm::rotate(glm::radians(+3.0f), glm::vec3{1.0f, 0.0f, 0.0f});
                break;
            case GLFW_KEY_LEFT: /* pan left */
                *active *= glm::rotate(glm::radians(-3.0f), glm::vec3{0.0f, 1.0f, 0.0f});
                break;
            case GLFW_KEY_RIGHT: /* pan right */
                *active *= glm::rotate(glm::radians(+3.0f), glm::vec3{0.0f, 1.0f, 0.0f});
                break;
            case GLFW_KEY_X:
                *active *= glm::translate(glm::vec3{1, 0, 0});
                break;
            case GLFW_KEY_Y:
                *active *= glm::translate(glm::vec3{0, 1, 0});
                break;
            case GLFW_KEY_Z:
                *active *= glm::translate(glm::vec3{0, 0, 1});
                break;
            default:
                break;
        };

    }
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                exit(0);
            case GLFW_KEY_0:
                if (glIsEnabled(GL_LIGHT0))
                    glDisable(GL_LIGHT0);
                else
                    glEnable(GL_LIGHT0);
                break;
            case GLFW_KEY_1:
                if (glIsEnabled(GL_LIGHT1))
                    glDisable(GL_LIGHT1);
                else
                    glEnable(GL_LIGHT1);
                break;
            case GLFW_KEY_2:
                if (glIsEnabled(GL_LIGHT2))
                    glDisable(GL_LIGHT2);
                else
                    glEnable(GL_LIGHT2);
                break;
            case GLFW_KEY_SPACE: /* pause the animation */
                is_anim_running ^= true;
                break;
            case GLFW_KEY_C:
                active = &camera_cf;
                break;
            case GLFW_KEY_F:
                active = &frame_cf;
                break;
            case GLFW_KEY_I:  // move camera in
            	camera_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,5.0,0.0});
                break;
            case GLFW_KEY_O:  // move camera out
            	camera_cf *= glm::translate(glm::mat4(1.0f),glm::vec3{0.0,-5.0,0.0});
                break;
            case GLFW_KEY_X:
                *active *= glm::translate(glm::vec3{-1, 0, 0});
                break;
            case GLFW_KEY_Y:
                *active *= glm::translate(glm::vec3{0, -1, 0});
                break;
            case GLFW_KEY_Z:
                *active *= glm::translate(glm::vec3{0, 0, -1});
                break;
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
