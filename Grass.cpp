/*
 * Grass.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: dan
 */
/*
 * Felt.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: dan
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <glm/gtx/vector_angle.hpp>
#include "Grass.h"

using glm::vec3;

void Grass::init_model(int level) {

    /* the following if statements are needed to avoid regenerating the buffers
       when the sphere is recreated at different recursion detail
     */
    if (!glIsBuffer(tri_vertex_buffer))
        glGenBuffers(1, &tri_vertex_buffer);
    if (!glIsBuffer(tri_color_buffer))
        glGenBuffers(1, &tri_color_buffer);
    if (!glIsBuffer(tri_index_buffer))
        glGenBuffers(1, &tri_index_buffer);
    tri_all_points.clear();
    tri_all_colors.clear();
    tri_all_index.clear();


    /// grass points generated
    vec3 center{0.0f,0.0f,0.0f};
    float x = 0.24f, y = 0.4f, z = 0.02f;
    vec3 grass_color{x,y,z};
    vec3 radial_point = {RAD,0.0f,0.0f};

    float angle = 0;
    float d_angle = M_PI/SEGMENT_SUBDIV;

	// start top circular face of cylinder
	tri_all_index.push_back(0);
	tri_all_points.push_back(center);
	tri_all_colors.push_back(grass_color);

	tri_all_index.push_back(tri_all_points.size());
	tri_all_points.push_back(radial_point);
	tri_all_colors.push_back(grass_color);

	for(int i = 0; i < 2*SEGMENT_SUBDIV; i++){

		angle += d_angle;
		radial_point.x = RAD*cos(angle);
		radial_point.y = RAD*sin(angle);
		tri_all_index.push_back(tri_all_points.size());
		tri_all_points.push_back(radial_point);
		tri_all_colors.push_back(grass_color);

		if(i < SEGMENT_SUBDIV){
			grass_color.x += 0.04f;
			grass_color.y += 0.04f;
			grass_color.z += 0.04f;
		}else{
			grass_color.x -= 0.04f;
			grass_color.y -= 0.04f;
			grass_color.z -= 0.04f;
		}

		tri_all_index.push_back(0);
		tri_all_index.push_back(tri_all_points.size() - 1);
	}

    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, tri_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, tri_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : tri_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, tri_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, tri_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : tri_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri_all_index.size() * sizeof(GLushort), tri_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Grass::render(bool outline) const {
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

		glPushMatrix();
		glRotatef(-90,1,0,0);
		glTranslatef(3.8f,0.0f,-1.88f);
		glScalef(0.7f,1.2f,1.3f);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, tri_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
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
		glPopMatrix();
    }
}

void Grass::build(void *data) {
    int lev = *((int *) data);
    init_model(lev);

    post_build(); /* must call post_build(), to allow actual rendering */
}



