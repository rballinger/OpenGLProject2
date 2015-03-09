#include <iostream>
#include <cmath>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>

#undef GLFW_DLL
#include <GLFW/glfw3.h>

#include "StreetLight.h"
#include "Car.h"
#include "Tire.h"
#include "Shapes/Sphere.h"

using namespace std;

void init_model();
void win_refresh(GLFWwindow*);
float arc_ball_rad_square;
int screen_ctr_x, screen_ctr_y;

bool wireframe = true;
Sphere lamp;
Car car;
Tire *tire_fr, *tire_fl, *tire_rr, *tire_rl;
StreetLight streetLight;
glm::mat4 camera_cf, frame_cf, lamp_cf,
    car_cf, tire_fr_cf, tire_fl_cf, tire_rr_cf, tire_rl_cf;
glm::mat4 *active;

GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
GLfloat black_color[] = {0.0, 0.0, 0.0, 1.0};   /* color */


void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}


void win_resize (GLFWwindow * win, int width, int height)
{
#ifdef DEBUG
    cout << __FUNCTION__ << " " << width << "x" << height << endl;
#endif
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    float rad = min(h,w)/2;
    arc_ball_rad_square = rad * rad;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(60.0, static_cast<float> (width)/ static_cast<float> (height), 1, 1000);
}

void win_refresh (GLFWwindow *win) {
    glClearColor (0.6f, 1.0f, 1.0f, 1.0f); /* black background */
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);

    glLoadMatrixf(glm::value_ptr(camera_cf));

    /* axes */
    glBegin (GL_LINES);
    glColor3ub (255, 0, 0);
    glVertex3i (0, 0, 0);
    glVertex3i (5, 0, 0);
    glColor3ub (0, 255, 0);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 5, 0);
    glColor3ub (0, 0, 255);
    glVertex3i (0, 0, 0);
    glVertex3i (0, 0, 5);
    glEnd();

    /* ground */
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

    glTranslatef(0, -30.0f, 0);
    /* render static objects: streetLight */
    glPushMatrix();
    {
        glMultMatrixf(glm::value_ptr(frame_cf));
        streetLight.render();
    }
    glPopMatrix();

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

    glPushMatrix();
    {
        // place car in cf
        glMultMatrixf(glm::value_ptr(car_cf));
        car.render(wireframe);
        glPushMatrix();
        {
            //glTranslatef(4.0f, -18.8f, -1.5f);
            glMultMatrixf(glm::value_ptr(tire_fr_cf));
            glRotatef(270, 0, 1.0f, 0);
            glScalef(0.25f, 0.25f, 0.25f);
            tire_fr->render();
        }
        glPopMatrix();
        glPushMatrix();
        {
            //glTranslatef(4.0f, -4.2f, -1.5f);
            glMultMatrixf(glm::value_ptr(tire_fl_cf));
            glRotatef(270, 0, 1.0f, 0);
            glScalef(0.25f, 0.25f, 0.25f);
            tire_fl->render();
        }
        glPopMatrix();
        glPushMatrix();
        {
            //glTranslatef(4.0f, -18.8f, -1.5f);
            glMultMatrixf(glm::value_ptr(tire_fr_cf));
            glRotatef(90, 0, 1.0f, 0);
            glScalef(0.25f, 0.25f, 0.25f);
            tire_rr->render();
        }
        glPopMatrix();
        glPushMatrix();
        {
            //glTranslatef(4.0f, -4.2f, -1.5f);
            glMultMatrixf(glm::value_ptr(tire_fl_cf));
            glRotatef(90, 0, 1.0f, 0);
            glScalef(0.25f, 0.25f, 0.25f);
            tire_rl->render();
        }
        glPopMatrix();
    }
    glPopMatrix();

    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods) {
    if (action == GLFW_RELEASE) return; /* ignore key release action */

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
            default:
                break;
        };
    }	// controls movement of other objects
    else {
        switch (key) {
            case GLFW_KEY_W:
                wireframe = !wireframe;
                break;
            case GLFW_KEY_ESCAPE:
                exit(0);
            case GLFW_KEY_1:
                if (glIsEnabled(GL_LIGHT2))
                    glDisable(GL_LIGHT2);
                else
                    glEnable(GL_LIGHT2);
                win_refresh(win);
                break;
            case GLFW_KEY_C:
                active = &camera_cf;
                break;
        }
    }
    win_refresh(win);
}

/*
    The virtual trackball technique implemented here is based on:
    https://www.opengl.org/wiki/Object_Mouse_Trackball
*/
void cursor_handler (GLFWwindow *win, double xpos, double ypos) {
    int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
    static glm::vec3 first_click;
    static glm::mat4 current_cam;
    static bool is_tracking = false;

    glm::vec3 this_vec;
    if (state == GLFW_PRESS) {
        /* TODO: use glUnproject? */
        float x = (xpos - screen_ctr_x);
        float y = -(ypos - screen_ctr_y);
        float hypot_square = x * x + y * y;
        float z;

        /* determine whether the mouse is on the sphere or on the hyperbolic sheet */
        if (2 * hypot_square < arc_ball_rad_square)
            z = sqrt(arc_ball_rad_square - hypot_square);
        else
            z = arc_ball_rad_square / 2.0 / sqrt(hypot_square);
        if (!is_tracking) {
            /* store the mouse position when the button was pressed for the first time */
            first_click = glm::normalize(glm::vec3{x, y, z});
            current_cam = camera_cf;
            is_tracking = true;
        }
        else {
            /* compute the rotation w.r.t the initial click */
            this_vec = glm::normalize(glm::vec3{x, y, z});
            /* determine axis of rotation */
            glm::vec3 N = glm::cross(first_click, this_vec);

            /* determine the angle of rotation */
            float theta = glm::angle(first_click, this_vec);

            /* create a quaternion of the rotation */
            glm::quat q{cos(theta / 2), sin(theta / 2) * N};
            /* apply the rotation w.r.t to the current camera CF */
            camera_cf = current_cam * glm::toMat4(glm::normalize(q));
        }
        win_refresh(win);
    }
    else {
        is_tracking = false;
    }
}

void scroll_handler (GLFWwindow *win, double xscroll, double yscroll) {
    /* translate along the camera Z-axis */
    glm::mat4 z_translate = glm::translate((float)yscroll * glm::vec3{0, 0, 5});
    camera_cf =  z_translate * camera_cf;
    win_refresh(win);
}

void init_gl() {
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
    // street lamp light
    glEnable (GL_LIGHT2);
    glLightfv (GL_LIGHT2, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT2, GL_SPECULAR, light0_color);

    glEnableClientState(GL_VERTEX_ARRAY);

    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf *= glm::translate(glm::vec3{0, 0, -20});

    lamp_cf = glm::translate(glm::vec3{0, 0, 10});
}

void make_model() {
    streetLight.build();
    lamp.build(35, 40);
    car.build();
    tire_fr = new Tire();
    tire_fl = new Tire();
    tire_rr = new Tire();
    tire_rl = new Tire();
    tire_fr->build();
    tire_fl->build();
    tire_rr->build();
    tire_rl->build();
    frame_cf = glm::translate(glm::vec3{0, 0 , 25});
    car_cf = glm::translate(glm::vec3(0, 25, 1.5));
    tire_fr_cf = glm::translate(glm::vec3(0, 25, 1.5));
    tire_fl_cf = glm::translate(glm::vec3(0, 20, 1.5));
    tire_rr_cf = glm::translate(glm::vec3(0, 15, 1.5));
    tire_rl_cf = glm::translate(glm::vec3(0, 10, 1.5));
    active = &camera_cf;		// camera frame is initially active
}

int main() {
    cout << "Hello" << endl;

    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }

    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "Test", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }

    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    // glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwSetCursorPosCallback(win, cursor_handler);
    glfwSetScrollCallback(win, scroll_handler);
    glfwMakeContextCurrent(win);

    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }

    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);


    glfwSetWindowSize(win, 700 , 500);
    glfwSwapInterval(1);
    init_gl();
    make_model();

    int ev_num = 0;
    win_refresh(win);
    while (!glfwWindowShouldClose(win)) {
        glfwWaitEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
