/*
 * WheelBufferObject.h
 *
 *  Created on: Feb 27, 2015
 *      Author: dan
 */

#ifndef WHEELBUFFEROBJECT_H_
#define WHEELBUFFEROBJECT_H_
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#endif
#include <vector>
#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
using namespace std;

class WheelBufferObject {
protected:
	// tire data structs
    GLuint tire_vertex_buffer, tire_color_buffer, tire_index_buffer;
    std::vector <glm::vec3> tire_all_points, tire_all_colors;
    vector<GLushort> tire_all_index;

    // hub data structs
    GLuint hub_vertex_buffer, hub_color_buffer, hub_index_buffer;
    std::vector <glm::vec3> hub_all_points, hub_all_colors;
    vector<GLushort> hub_all_index;

    // hex nut data structs
    GLuint hex_vertex_buffer, hex_color_buffer, hex_index_buffer;
    std::vector <glm::vec3> hex_all_points, hex_all_colors;
    vector<GLushort> hex_all_index;
private:
    bool build_complete;
public:
    WheelBufferObject() {
    	// tire
    	tire_vertex_buffer = tire_color_buffer = tire_index_buffer = 0;

    	// hub
    	hub_vertex_buffer = hub_color_buffer = hub_index_buffer = 0;

    	// hex
    	hex_vertex_buffer = hex_color_buffer = hex_index_buffer = 0;

        build_complete = false;
    }

    ~WheelBufferObject() {
#if 0
    	// tire
        if (glIsBuffer(tire_vertex_buffer))
            glDeleteBuffers(1, &tire_vertex_buffer);
        if (glIsBuffer(tire_color_buffer))
            glDeleteBuffers(1, &tire_color_buffer);
        if (glIsBuffer(tire_index_buffer))
            glDeleteBuffers(1, &tire_index_buffer);

        // hub
        if (glIsBuffer(hub_vertex_buffer))
            glDeleteBuffers(1, &hub_vertex_buffer);
        if (glIsBuffer(hub_color_buffer))
            glDeleteBuffers(1, &hub_color_buffer);
        if (glIsBuffer(hub_index_buffer))
            glDeleteBuffers(1, &hub_index_buffer);

        // hex
        if (glIsBuffer(hex_vertex_buffer))
            glDeleteBuffers(1, &hex_vertex_buffer);
        if (glIsBuffer(hex_color_buffer))
            glDeleteBuffers(1, &hex_color_buffer);
        if (glIsBuffer(hex_index_buffer))
            glDeleteBuffers(1, &hex_index_buffer);
#endif
    }

    void post_build() {
        build_complete = true;
    }

    virtual void build(void *data) = 0;

};
#endif /* WHEELBUFFEROBJECT_H_ */
