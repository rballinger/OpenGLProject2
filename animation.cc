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
#include "Arm.h"
#include "StreetLight.h"
#include "Cylinder.h"
#include "Wheel.h"
#include "Sphere.h"
using namespace std;
void displayCallback(GLFWwindow*);

/* define global variables here */
Wheel *wheel;
Arm* swingarm;
Sphere sphere;
StreetLight streetLight;
Sphere lamp;

glm::mat4 wheel_cf;
glm::mat4 lamp_cf;
glm::mat4 swing_arm_cf, frame_cf;
glm::mat4 camera_cf, light0_cf;
glm::mat4 *active;

const float INIT_SWING_ANGLE = 35.0f; /* degrees */
const float GRAVITY = 9.8;   /* m/sec^2 */
bool is_anim_running = true;

/* light source setting */
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
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
    camera_cf = glm::lookAt(glm::vec3(75,70,40), glm::vec3(0,0,0), glm::vec3(0,0,1));
}

/*================================================================*
 * Idle Callback function. This is the main engine for simulation *
 *================================================================*/
void updateCoordFrames()
{
    static double last_timestamp = 0;
    static float swing_time = 0;
    static float swing_angle = 0;
    static float wheel_angle = 0;
    static int deg = 0;
    const float WHEEL_SPEED = 72; /* in degrees per second */
    float delta, current;


    current = glfwGetTime();
    if (is_anim_running) {
        delta = (current - last_timestamp);
        wheel_angle = WHEEL_SPEED * delta;
        wheel_cf *= glm::rotate(glm::radians(wheel_angle), glm::vec3{0.0f, 0.0f, 1.0f});

        /* use the pendulum equation to calculate its angle */
        swing_time += delta * 3;
        float angle = INIT_SWING_ANGLE *
                cos(swing_time * sqrt(GRAVITY / swingarm->length()));
        swing_arm_cf *= glm::rotate(glm::radians(angle - swing_angle), glm::vec3{0.0f, 1.0f, 0.0f});
        swing_angle = angle;
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


    /* The following nesting of push-pop pairs create an easy
     * way to render different object w.r.t other coordinate
     * frame.
     *
     * The swingarm is rendered w.r.t the swing base frame
     * The wheel is rendered w.r.t the swing arm frame
     */
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(frame_cf));
        streetLight.render();
        glPushMatrix();
        {
            glMultMatrixf(glm::value_ptr(swing_arm_cf));
            swingarm->render();
            glPushMatrix();
            {
                glMultMatrixf(glm::value_ptr(wheel_cf));
                wheel->render();
            }
            glPopMatrix();

        }
        glPopMatrix();
    }
    glPopMatrix();
    /* to make smooth transition between frame */
    glfwSwapBuffers(win);
}

void myModelInit ()
{
    sphere.build(35, 40);

    swingarm = new Arm;
    swingarm->build();

    wheel = new Wheel();
    wheel->build();
    wheel_cf = glm::translate(glm::vec3{0.0f, 0.0f, -swingarm->length()});
    wheel_cf *= glm::rotate(glm::radians(90.0f), glm::vec3{1,0,0});

    streetLight.build();
    lamp.build(35, 40);
    frame_cf = glm::translate(glm::vec3{0, 0 , 25});
    active = &camera_cf;

    light0_cf = glm::translate(glm::vec3{-25, 8, 50});

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
                active = &light0_cf;
                if (glIsEnabled(GL_LIGHT0))
                    glDisable(GL_LIGHT0);
                else
                    glEnable(GL_LIGHT0);
                break;
            case GLFW_KEY_1:
                break;
            case GLFW_KEY_2:
                active = &lamp_cf;
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