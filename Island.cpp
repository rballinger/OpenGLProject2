/*
 * Island.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: dan
 */
#include "Island.h"
#include <glm/gtx/vector_angle.hpp>

using glm::vec3;
void Island::init_model(int level) {
	/* the following if statements are needed to avoid regenerating the buffers
	   when the cylinder is recreated at different recursion detail
	 */

    //number of faces on tread / edges on circular side
    int num_divisions = 20;

    /* divide tire into a number of quads */
    float d_angle = 2 * M_PI / (num_divisions * SEGMENT_SUBDIV);
    const float D60 = M_PI / (num_divisions * 3);
    float angle = 0;

	float x = 0.50f, y = 0.50f, z = 0.50f;
	vec3 curb_color{x,y,z};

    vec3 c1, c2;

    float Z = THICKNESS;
    for (int s = 0; s < num_divisions; s++) {
        c1 = vec3{OUTER_RAD * cos(angle),
            OUTER_RAD * sin(angle), Z};
        c2 = vec3{OUTER_RAD * cos(angle + D60),
                OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < SEGMENT_SUBDIV; k++) {
            float t = (float) k / SEGMENT_SUBDIV;
            vec3 v1{INNER_RAD * cos(angle),
                INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            quad_all_index.push_back(quad_all_points.size());
            quad_all_points.push_back(v1);
            quad_all_index.push_back(quad_all_points.size());
            quad_all_points.push_back(v2);
            quad_all_colors.push_back(curb_color);
            quad_all_colors.push_back(curb_color);
            angle  += d_angle;
			if(k > SEGMENT_SUBDIV/2){
			 curb_color.x += 0.003f;
			 curb_color.y += 0.003f;
			 curb_color.z += 0.003f;
			}else{
			 curb_color.x -= 0.003f;
			 curb_color.y -= 0.003f;
			 curb_color.z -= 0.003f;
			}
        }
    }

    /* repeat the first two vertices to complete the quad */
    pts_count = quad_all_index.size();
    quad_all_index.push_back(0);
    quad_all_index.push_back(1);
    top_count = quad_all_index.size();

    Z = -THICKNESS;
    for (int s = 0; s < num_divisions; s++) {
        c1 = vec3{OUTER_RAD * cos(angle),
                OUTER_RAD * sin(angle), Z};
        c2 = vec3{OUTER_RAD * cos(angle + D60),
                OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < SEGMENT_SUBDIV; k++) {
            float t = (float) k / SEGMENT_SUBDIV;
            vec3 v1{INNER_RAD * cos(angle),
                    INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            quad_all_index.push_back(quad_all_points.size());
            quad_all_points.push_back(v1);
            quad_all_index.push_back(quad_all_points.size());
            quad_all_points.push_back(v2);
            quad_all_colors.push_back(curb_color);
            quad_all_colors.push_back(curb_color);
            angle  += d_angle;
			if(k < SEGMENT_SUBDIV/2){
			 curb_color.x += 0.003f;
			 curb_color.y += 0.003f;
			 curb_color.z += 0.003f;
			}else{
			 curb_color.x -= 0.003f;
			 curb_color.y -= 0.003f;
			 curb_color.z -= 0.003f;
			}
        }
    }
    quad_all_index.push_back(pts_count);
    quad_all_index.push_back(pts_count + 1);

    /* indices for the outer walls */
    for (int k = 0; k < num_divisions * SEGMENT_SUBDIV; k++) {
    	quad_all_index.push_back(2*k + 1);
    	quad_all_index.push_back(2*k + 1 + pts_count);
    }
    quad_all_index.push_back(1);
    quad_all_index.push_back(pts_count + 1);

    /* indices for the inner walls */
    for (int k = 0; k < num_divisions * SEGMENT_SUBDIV; k++) {
    	quad_all_index.push_back(2*k + pts_count);
    	quad_all_index.push_back(2*k);
    }
    quad_all_index.push_back(pts_count);
    quad_all_index.push_back(0);

    glGenBuffers(1, &quad_vertex_buffer);
    glGenBuffers(1, &quad_index_buffer);
    glGenBuffers(1, &quad_color_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, quad_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : quad_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_all_index.size() * sizeof(GLushort), quad_all_index.data(), GL_DYNAMIC_DRAW);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_all_index.size() * sizeof(GLushort), quad_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, quad_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, quad_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : quad_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_all_index.size() * sizeof(GLushort), quad_all_index.data(), GL_DYNAMIC_DRAW);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void Island::render(bool outline) const {
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index_buffer);
	/* bind color buffer */
	if (glIsBuffer(quad_color_buffer)) {
		glBindBuffer(GL_ARRAY_BUFFER, quad_color_buffer);
		glColorPointer(3, GL_FLOAT, 0, 0);
	}
    glPushMatrix();
    glTranslatef(3.85f,-1.88f,0.0f);
    glRotatef(90,1,0,0);
    glScalef(1.2f,2.0f,1.0f);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT, 0);
    glFrontFace(GL_CW);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (top_count)));
    glFrontFace(GL_CCW);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (2*top_count)));
    glFrontFace(GL_CCW);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (3*top_count)));
    glPopMatrix();
}

void Island::build(void *data) {
    int lev = *((int *) data);
    init_model(lev);

    post_build(); /* must call post_build(), to allow actual rendering */
}

