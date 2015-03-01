/*
 * QuadBufferObject.h
 *
 *  Created on: Feb 1, 2015
 *      Author: dan
 */

#ifndef QUADBUFFEROBJECT_H_
#define QUADBUFFEROBJECT_H_
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

class QuadOrTriBufferObject {
protected:
    GLuint quad_vertex_buffer, quad_color_buffer, quad_index_buffer;
    GLuint cone_quad_vertex_buffer, cone_quad_color_buffer, cone_quad_index_buffer;  // cone
    GLuint post_quad_vertex_buffer, post_quad_color_buffer, post_quad_index_buffer;  // POST quads
    GLuint post_tri_vertex_buffer, post_tri_color_buffer, post_tri_index_buffer;     // POST tris
    GLuint base_quad_vertex_buffer, base_quad_color_buffer, base_quad_index_buffer;  // POST quads
    GLuint base_tri_vertex_buffer, base_tri_color_buffer, base_tri_index_buffer;     // POST tris
    GLuint tri_vertex_buffer, tri_color_buffer, tri_index_buffer;
    GLuint line_vertex_buffer, line_color_buffer, line_index_buffer;
    std::vector <glm::vec3> quad_all_points, quad_all_colors;
    std::vector <glm::vec3> tri_all_points, tri_all_colors;
    std::vector <glm::vec3> cone_quad_all_points, cone_quad_all_colors;   // cone
    std::vector <glm::vec3> post_quad_all_points, post_quad_all_colors;   // post quads
    std::vector <glm::vec3> post_tri_all_points, post_tri_all_colors;	  // post tris
    std::vector <glm::vec3> base_quad_all_points, base_quad_all_colors;   // post quads
    std::vector <glm::vec3> base_tri_all_points, base_tri_all_colors;	  // post tris
    std::vector <glm::vec3> line_all_points, line_all_colors;
    vector<GLushort> quad_all_index, cone_quad_all_index, post_quad_all_index, base_quad_all_index,
    				post_tri_all_index, base_tri_all_index, tri_all_index, line_all_index;
private:
    bool build_complete;
public:
    QuadOrTriBufferObject() {
    	quad_vertex_buffer = quad_color_buffer = quad_index_buffer = 0;
    	cone_quad_vertex_buffer = cone_quad_color_buffer = cone_quad_index_buffer = 0;
    	post_quad_vertex_buffer = post_quad_color_buffer = post_quad_index_buffer = 0;
    	base_quad_vertex_buffer = base_quad_color_buffer = base_quad_index_buffer = 0;

    	tri_vertex_buffer = tri_color_buffer = tri_index_buffer = 0;
    	post_tri_vertex_buffer = post_tri_color_buffer = post_tri_index_buffer = 0;
    	base_tri_vertex_buffer = base_tri_color_buffer = base_tri_index_buffer = 0;

    	line_vertex_buffer = line_color_buffer = line_index_buffer = 0;
        build_complete = false;
    }

    ~QuadOrTriBufferObject() {
#if 0
        if (glIsBuffer(quad_vertex_buffer))
            glDeleteBuffers(1, &quad_vertex_buffer);
        if (glIsBuffer(quad_color_buffer))
            glDeleteBuffers(1, &quad_color_buffer);
        if (glIsBuffer(quad_index_buffer))
            glDeleteBuffers(1, &quad_index_buffer);

        if (glIsBuffer(post_quad_vertex_buffer))
            glDeleteBuffers(1, &post_quad_vertex_buffer);
        if (glIsBuffer(post_quad_color_buffer))
            glDeleteBuffers(1, &post_quad_color_buffer);
        if (glIsBuffer(post_quad_index_buffer))
            glDeleteBuffers(1, &post_quad_index_buffer);

        if (glIsBuffer(base_quad_vertex_buffer))
            glDeleteBuffers(1, &base_quad_vertex_buffer);
        if (glIsBuffer(base_quad_color_buffer))
            glDeleteBuffers(1, &base_quad_color_buffer);
        if (glIsBuffer(base_quad_index_buffer))
            glDeleteBuffers(1, &base_quad_index_buffer);

        if (glIsBuffer(cone_quad_vertex_buffer))
            glDeleteBuffers(1, &cone_quad_vertex_buffer);
        if (glIsBuffer(cone_quad_color_buffer))
            glDeleteBuffers(1, &cone_quad_color_buffer);
        if (glIsBuffer(cone_quad_index_buffer))
            glDeleteBuffers(1, &cone_quad_index_buffer);

        if (glIsBuffer(tri_vertex_buffer))
            glDeleteBuffers(1, &tri_vertex_buffer);
        if (glIsBuffer(tri_color_buffer))
            glDeleteBuffers(1, &tri_color_buffer);
        if (glIsBuffer(tri_index_buffer))
            glDeleteBuffers(1, &tri_index_buffer);

        if (glIsBuffer(post_tri_vertex_buffer))
            glDeleteBuffers(1, &post_tri_vertex_buffer);
        if (glIsBuffer(post_tri_color_buffer))
            glDeleteBuffers(1, &post_tri_color_buffer);
        if (glIsBuffer(post_tri_index_buffer))
            glDeleteBuffers(1, &post_tri_index_buffer);

        if (glIsBuffer(base_tri_vertex_buffer))
            glDeleteBuffers(1, &base_tri_vertex_buffer);
        if (glIsBuffer(base_tri_color_buffer))
            glDeleteBuffers(1, &base_tri_color_buffer);
        if (glIsBuffer(base_tri_index_buffer))
            glDeleteBuffers(1, &base_tri_index_buffer);

        if (glIsBuffer(line_vertex_buffer))
            glDeleteBuffers(1, &line_vertex_buffer);
        if (glIsBuffer(line_color_buffer))
            glDeleteBuffers(1, &line_color_buffer);
        if (glIsBuffer(line_index_buffer))
            glDeleteBuffers(1, &line_index_buffer);
#endif
    }

    void post_build() {
        build_complete = true;
    }

    virtual void build(void *data) = 0;

    virtual void render(bool draw_outline) const {
        if (!build_complete) {
            return;
        }

        if(quad_all_points.size() > 0){
			/* bind vertex buffer */
			if (glIsBuffer(quad_vertex_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, quad_vertex_buffer);
				glVertexPointer(3, GL_FLOAT, 0, 0);
			}
			/* bind color buffer */
			if (glIsBuffer(quad_color_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, quad_color_buffer);
				glColorPointer(3, GL_FLOAT, 0, 0);
			}

			/* bind the index buffer */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);

			/* render the polygon */
			glPolygonMode(GL_FRONT, GL_FILL);
			glDrawElements(GL_QUADS, quad_all_index.size(), GL_UNSIGNED_SHORT, 0);

			if (draw_outline) {
				/* remove from BEGIN to END to disable rendering the polygon outline */
				glPolygonMode(GL_FRONT, GL_LINE);

				glEnable(GL_POLYGON_OFFSET_LINE);
				/* With polygon offset enabeld,  lines are rendered away from the polygons.
				Negative offset: lines are now rendered CLOSER to the camera */
				glPolygonOffset(-1.0, 1);

				glDisableClientState(GL_COLOR_ARRAY);
				glColor3ub(255, 255, 255);
				glDrawElements(GL_QUADS, quad_all_index.size(), GL_UNSIGNED_SHORT, 0);
				glEnableClientState(GL_COLOR_ARRAY);
				glDisable(GL_POLYGON_OFFSET_LINE);
			}
        }

        if(tri_all_points.size() > 0){
			/* bind vertex buffer */
			if (glIsBuffer(tri_vertex_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, tri_vertex_buffer);
				glVertexPointer(3, GL_FLOAT, 0, 0);
			}
			/* bind color buffer */
			if (glIsBuffer(tri_color_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, tri_color_buffer);
				glColorPointer(3, GL_FLOAT, 0, 0);
			}

			/* bind the index buffer */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_index_buffer);

			/* render the polygon */
			glPolygonMode(GL_FRONT, GL_FILL);
			glDrawElements(GL_TRIANGLES, tri_all_index.size(), GL_UNSIGNED_SHORT, 0);

			if (draw_outline) {
				/* remove from BEGIN to END to disable rendering the polygon outline */
				glPolygonMode(GL_FRONT, GL_LINE);

				glEnable(GL_POLYGON_OFFSET_LINE);
				/* With polygon offset enabeld,  lines are rendered away from the polygons.
				Negative offset: lines are now rendered CLOSER to the camera */
				glPolygonOffset(-1.0, 1);

				glDisableClientState(GL_COLOR_ARRAY);
				glColor3ub(255, 255, 255);
				glDrawElements(GL_QUADS, tri_all_index.size(), GL_UNSIGNED_SHORT, 0);
				glEnableClientState(GL_COLOR_ARRAY);
				glDisable(GL_POLYGON_OFFSET_LINE);
			}
        }

        if(line_all_points.size() > 0){
			/* bind vertex buffer */
			if (glIsBuffer(line_vertex_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, line_vertex_buffer);
				glVertexPointer(3, GL_FLOAT, 0, 0);
			}
			/* bind color buffer */
			if (glIsBuffer(line_color_buffer)) {
				glBindBuffer(GL_ARRAY_BUFFER, line_color_buffer);
				glColorPointer(3, GL_FLOAT, 0, 0);
			}

			/* bind the index buffer */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, line_index_buffer);

			/* render the polygon */
			glPolygonMode(GL_FRONT, GL_FILL);
			glDrawElements(GL_LINES, line_all_index.size(), GL_UNSIGNED_SHORT, 0);

			if (draw_outline) {
				/* remove from BEGIN to END to disable rendering the polygon outline */
				glPolygonMode(GL_FRONT, GL_LINE);

				glEnable(GL_POLYGON_OFFSET_LINE);
				/* With polygon offset enabeld,  lines are rendered away from the polygons.
				Negative offset: lines are now rendered CLOSER to the camera */
				glPolygonOffset(-1.0, 1);

				glDisableClientState(GL_COLOR_ARRAY);
				glColor3ub(255, 255, 255);
				glDrawElements(GL_QUADS, line_all_index.size(), GL_UNSIGNED_SHORT, 0);
				glEnableClientState(GL_COLOR_ARRAY);
				glDisable(GL_POLYGON_OFFSET_LINE);
			}
        }

        /* unbind the buffers */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};
#endif /* QUADBUFFEROBJECT_H_ */
