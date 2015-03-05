/*
 * StreetLamp.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: dan
 */
#include "StreetLamp.h"
#include <glm/gtx/vector_angle.hpp>

#define M_PI 3.14159265358979323846

using glm::vec3;
void StreetLamp::init_model(int level) {
	/* the following if statements are needed to avoid regenerating the buffers
	   when the cylinder is recreated at different recursion detail
	 */

	float percentRender = level/100.0;

	// quads used for faces of torus
	if (!glIsBuffer(quad_vertex_buffer))
		glGenBuffers(1, &quad_vertex_buffer);
	if (!glIsBuffer(quad_color_buffer))
		glGenBuffers(1, &quad_color_buffer);
	if (!glIsBuffer(quad_index_buffer))
		glGenBuffers(1, &quad_index_buffer);
	quad_all_points.clear();
	quad_all_colors.clear();
	quad_all_index.clear();

	/* divide cylinder into a number of quads */
	float pheta = 2 * M_PI / (PHETA_SUBDIV);
	float phi = 0;
	float d_pheta = 2 * M_PI / (PHETA_SUBDIV);
	float d_phi = 2 * M_PI / (PHI_SUBDIV);

	vec3 c1, c2, c3, c4;

	float x = 0.40f, y = 0.40f, z = 0.40f;
	vec3 c{x,y,z};

	c1 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta))*cos(0),(BIG_RAD + LITTLE_RAD * cos(pheta))*sin(0), LITTLE_RAD*sin(pheta)};
	c2 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*cos(0),(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*sin(0), LITTLE_RAD*sin(pheta + d_pheta)};

	for (int q = 0; q < PHETA_SUBDIV; q++){
		 for (int s = 0; s < ceil(PHI_SUBDIV*percentRender); s++) {

			quad_all_index.push_back(quad_all_points.size());
			quad_all_points.push_back(c2);
			quad_all_index.push_back(quad_all_points.size());
			quad_all_points.push_back(c1);

			quad_all_colors.push_back(c);
			quad_all_colors.push_back(c);
			phi  += d_phi;
			c1 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta))*cos(phi),(BIG_RAD + LITTLE_RAD * cos(pheta))*sin(phi), LITTLE_RAD*sin(pheta)};
			c2 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*cos(phi),(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*sin(phi), LITTLE_RAD*sin(pheta + d_pheta)};

			quad_all_index.push_back(quad_all_points.size());
			quad_all_points.push_back(c1);
			quad_all_index.push_back(quad_all_points.size());
			quad_all_points.push_back(c2);

			quad_all_colors.push_back(c);
			quad_all_colors.push_back(c);
		 }
		 if(q > PHETA_SUBDIV/2){
			c.x += 0.005f;
			c.y += 0.005f;
			c.z += 0.005f;
		 }else{
			c.x -= 0.005f;
			c.y -= 0.005f;
			c.z -= 0.005f;
		 }
		 phi = 0;
		 pheta += d_pheta;
         c1 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta))*cos(phi),(BIG_RAD + LITTLE_RAD * cos(pheta))*sin(phi), LITTLE_RAD*sin(pheta)};
         c2 = vec3{(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*cos(phi),(BIG_RAD + LITTLE_RAD * cos(pheta + d_pheta))*sin(phi), LITTLE_RAD*sin(pheta + d_pheta)};
     }

    /* USED FOR QUAD FACES OF torus */
    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, quad_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : quad_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
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


    /////////////////////////// Lamp shade (cone) ///////////////////////////////////////

    if (!glIsBuffer(cone_quad_vertex_buffer))
        glGenBuffers(1, &cone_quad_vertex_buffer);
    if (!glIsBuffer(cone_quad_color_buffer))
        glGenBuffers(1, &cone_quad_color_buffer);
    if (!glIsBuffer(cone_quad_index_buffer))
        glGenBuffers(1, &cone_quad_index_buffer);
    cone_quad_all_points.clear();
    cone_quad_all_colors.clear();
    cone_quad_all_index.clear();

    /* divide cone into a number of quads */
    float d_angle = 2 * M_PI / (SEGMENT_SUBDIV);
    float angle = M_PI;

    vec3 l1, l2, l3, l4;
    x = 0.1f, y = 0.2f, z = 0.2f;
    vec3 lamp_color{x,y,z};

    // outer cone wall
    float Z = THICKNESS;
    for (int s = 0; s < SEGMENT_SUBDIV; s++) {
        l1 = vec3{TOP_RAD * cos(angle),
        	TOP_RAD * sin(angle), Z};
        l2 = vec3{TOP_RAD  * cos(angle + d_angle),
        	TOP_RAD  * sin(angle + d_angle), Z};
        l3 = vec3{OUTER_RAD * cos(angle),
            OUTER_RAD * sin(angle), -Z};
        l4 = vec3{OUTER_RAD  * cos(angle + d_angle),
                OUTER_RAD  * sin(angle + d_angle), -Z};

        cone_quad_all_index.push_back(cone_quad_all_points.size());
        cone_quad_all_points.push_back(l1);
        cone_quad_all_index.push_back(cone_quad_all_points.size());
        cone_quad_all_points.push_back(l3);
        cone_quad_all_index.push_back(cone_quad_all_points.size());
        cone_quad_all_points.push_back(l4);
        cone_quad_all_index.push_back(cone_quad_all_points.size());
        cone_quad_all_points.push_back(l2);

		if(s < SEGMENT_SUBDIV/2){
			lamp_color.x += 0.019f;
			lamp_color.y += 0.019f;
			lamp_color.z += 0.019f;
		}else{
			lamp_color.x -= 0.019f;
			lamp_color.y -= 0.019f;
			lamp_color.z -= 0.019f;
		}

		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);

		cone_quad_all_index.push_back(cone_quad_all_points.size());
		cone_quad_all_points.push_back(l1);
		cone_quad_all_index.push_back(cone_quad_all_points.size());
		cone_quad_all_points.push_back(l2);
		cone_quad_all_index.push_back(cone_quad_all_points.size());
		cone_quad_all_points.push_back(l4);
		cone_quad_all_index.push_back(cone_quad_all_points.size());
		cone_quad_all_points.push_back(l3);

		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);
		cone_quad_all_colors.push_back(lamp_color);

		angle  += d_angle;
    }

    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, cone_quad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, cone_quad_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    ptr = vertex_ptr;
    for (auto v : cone_quad_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, cone_quad_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, cone_quad_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : cone_quad_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cone_quad_all_index.size() * sizeof(GLushort), cone_quad_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    /////////////////////// POST (CYCLINDER) //////////////////
	// quads used for faces of cylinder
    if (!glIsBuffer(post_quad_vertex_buffer))
        glGenBuffers(1, &post_quad_vertex_buffer);
    if (!glIsBuffer(post_quad_color_buffer))
        glGenBuffers(1, &post_quad_color_buffer);
    if (!glIsBuffer(post_quad_index_buffer))
        glGenBuffers(1, &post_quad_index_buffer);
    post_quad_all_points.clear();
    post_quad_all_colors.clear();
    post_quad_all_index.clear();

    // triangles used for end of cylinder
    if (!glIsBuffer(post_tri_vertex_buffer))
        glGenBuffers(1, &post_tri_vertex_buffer);
    if (!glIsBuffer(post_tri_color_buffer))
        glGenBuffers(1, &post_tri_color_buffer);
    if (!glIsBuffer(post_tri_index_buffer))
        glGenBuffers(1, &post_tri_index_buffer);
    post_tri_all_points.clear();
    post_tri_all_colors.clear();
    post_tri_all_index.clear();

    /* divide cylinder into a number of quads */
    d_angle = 2 * M_PI / (POST_SEGMENT_SUBDIV);
    angle = M_PI;

     vec3 p1, p2, p3, p4;

     x = 0.23f, y = 0.23f, z = 0.23f;
     vec3 post_color{x,y,z};
     vec3 center_post{0,0,POST_THICKNESS};
     vec3 center_post_low{0,0,-POST_THICKNESS};

    // outer cylinder wall
     Z = POST_THICKNESS;
	p1 = vec3{POST_OUTER_RAD * cos(angle),
	POST_OUTER_RAD * sin(angle), Z};
	p2 = vec3{POST_OUTER_RAD  * cos(angle + d_angle),
	POST_OUTER_RAD  * sin(angle + d_angle), Z};
	p3 = vec3{POST_OUTER_RAD * cos(angle),
	POST_OUTER_RAD * sin(angle), -Z};
	p4 = vec3{POST_OUTER_RAD  * cos(angle + d_angle),
	POST_OUTER_RAD  * sin(angle + d_angle), -Z};

	// start quad
	post_quad_all_index.push_back(post_quad_all_points.size());
	post_quad_all_points.push_back(p1);
	post_quad_all_index.push_back(post_quad_all_points.size());
	post_quad_all_points.push_back(p3);
	post_quad_all_index.push_back(post_quad_all_points.size());
	post_quad_all_points.push_back(p4);
	post_quad_all_index.push_back(post_quad_all_points.size());
	post_quad_all_points.push_back(p2);

	post_quad_all_colors.push_back(post_color);
	post_quad_all_colors.push_back(post_color);
	post_quad_all_colors.push_back(post_color);
	post_quad_all_colors.push_back(post_color);

	// start top circular face of cylinder
	post_tri_all_index.push_back(0);
	post_tri_all_points.push_back(center_post);
	post_tri_all_colors.push_back(post_color);

	post_tri_all_index.push_back(1);
	post_tri_all_points.push_back(p1);
	post_tri_all_colors.push_back(post_color);

     for (int s = 0; s < POST_SEGMENT_SUBDIV; s++) {
    	 angle  += d_angle;
    	 p1 = p2;
    	 p3 = p4;
         p2 = vec3{POST_OUTER_RAD * cos(angle),
        	 POST_OUTER_RAD * sin(angle), Z};
         p4 =  vec3{POST_OUTER_RAD * cos(angle),
        	 POST_OUTER_RAD * sin(angle), -Z};

         post_quad_all_index.push_back(post_quad_all_points.size()-1);
         post_quad_all_index.push_back(post_quad_all_points.size()-2);
         post_quad_all_index.push_back(post_quad_all_points.size());
         post_quad_all_points.push_back(p4);
         post_quad_all_index.push_back(post_quad_all_points.size());
         post_quad_all_points.push_back(p2);

         post_quad_all_colors.push_back(post_color);
         post_quad_all_colors.push_back(post_color);

		if(s < POST_SEGMENT_SUBDIV/2){
			post_color.x += 0.005f;
			post_color.y += 0.005f;
			post_color.z += 0.005f;
		}else{
			post_color.x -= 0.005f;
			post_color.y -= 0.005f;
			post_color.z -= 0.005f;
		}

		// top
		post_tri_all_index.push_back(0);
		post_tri_all_index.push_back(post_tri_all_points.size()-1);
		post_tri_all_points.push_back(p2);
		post_tri_all_index.push_back(post_tri_all_points.size()-1);
		post_tri_all_colors.push_back(post_color);
     }

	// top last triangle
	angle  += d_angle;
	p2 = vec3{POST_OUTER_RAD * cos(angle),
		POST_OUTER_RAD * sin(angle), Z};
	post_tri_all_index.push_back(0);
	post_tri_all_index.push_back(post_tri_all_points.size()-2);
	post_tri_all_points.push_back(p2);
	post_tri_all_index.push_back(post_tri_all_points.size()-2);
	post_tri_all_colors.push_back(post_color);

    // reset colors
	post_color.x = 0.19f;
	post_color.y = 0.19f;
	post_color.z = 0.19f;

	// start top circular face of cylinder
	int hold = post_tri_all_points.size();
	post_tri_all_index.push_back(hold);
	post_tri_all_points.push_back(center_post);
	post_tri_all_colors.push_back(post_color);

	post_tri_all_index.push_back(post_tri_all_points.size());
	post_tri_all_points.push_back(p4);
	post_tri_all_colors.push_back(post_color);

	// bottom triangle face
    for (int s = 0; s < POST_SEGMENT_SUBDIV; s++) {
		angle  += d_angle;
		p4 =  vec3{POST_OUTER_RAD * cos(angle),
			POST_OUTER_RAD * sin(angle), -Z};

		if(s < POST_SEGMENT_SUBDIV/2){
			post_color.x -= 0.005f;
			post_color.y -= 0.005f;
			post_color.z -= 0.005f;
		}else{
			post_color.x += 0.005f;
			post_color.y += 0.005f;
			post_color.z += 0.005f;
		}
		// bottom
		post_tri_all_index.push_back(hold);
		post_tri_all_index.push_back(post_tri_all_points.size()-1);
		post_tri_all_points.push_back(p4);
		post_tri_all_index.push_back(post_tri_all_points.size()-2);
		post_tri_all_colors.push_back(post_color);
    }
	// bottom last triangle
	angle  += d_angle;
	p4 =  vec3{POST_OUTER_RAD * cos(angle),
		POST_OUTER_RAD * sin(angle), -Z};
	post_tri_all_index.push_back(0);
	post_tri_all_index.push_back(post_tri_all_points.size()-1);
	post_tri_all_points.push_back(p4);
	post_tri_all_index.push_back(post_tri_all_points.size()-2);
	post_tri_all_colors.push_back(post_color);

    /* USED FOR QUAD FACES OF CYLINDER */
    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, post_quad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, post_quad_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    ptr = vertex_ptr;
    for (auto v : post_quad_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, post_quad_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, post_quad_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : post_quad_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, post_quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, post_quad_all_index.size() * sizeof(GLushort), post_quad_all_index.data(), GL_DYNAMIC_DRAW);

    /* USED FOR TRI FACES OF CYLINDER */
    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, post_tri_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, post_tri_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    ptr = vertex_ptr;
    for (auto v : post_tri_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, post_tri_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, post_tri_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : post_tri_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, post_tri_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, post_tri_all_index.size() * sizeof(GLushort), post_tri_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



    /////////////////////// POST (CYCLINDER) //////////////////
	// quads used for faces of cylinder
    if (!glIsBuffer(base_quad_vertex_buffer))
        glGenBuffers(1, &base_quad_vertex_buffer);
    if (!glIsBuffer(base_quad_color_buffer))
        glGenBuffers(1, &base_quad_color_buffer);
    if (!glIsBuffer(base_quad_index_buffer))
        glGenBuffers(1, &base_quad_index_buffer);
    base_quad_all_points.clear();
    base_quad_all_colors.clear();
    base_quad_all_index.clear();

    // triangles used for end of cylinder
    if (!glIsBuffer(base_tri_vertex_buffer))
        glGenBuffers(1, &base_tri_vertex_buffer);
    if (!glIsBuffer(base_tri_color_buffer))
        glGenBuffers(1, &base_tri_color_buffer);
    if (!glIsBuffer(base_tri_index_buffer))
        glGenBuffers(1, &base_tri_index_buffer);
    base_tri_all_points.clear();
    base_tri_all_colors.clear();
    base_tri_all_index.clear();

    /* divide cylinder into a number of quads */
    d_angle = 2 * M_PI / (BASE_SEGMENT_SUBDIV);
    angle = M_PI;

     vec3 b1, b2, b3, b4;

     x = 0.33f, y = 0.33f, z = 0.33f;
     vec3 base_color{x,y,z};
     vec3 center_base{0,0,BASE_THICKNESS};
     vec3 center_base_low{0,0,-BASE_THICKNESS};

    // outer cylinder wall
     Z = BASE_THICKNESS;
	b1 = vec3{BASE_OUTER_RAD * cos(angle),
		BASE_OUTER_RAD * sin(angle), Z};
	b2 = vec3{BASE_OUTER_RAD  * cos(angle + d_angle),
		BASE_OUTER_RAD  * sin(angle + d_angle), Z};
	b3 = vec3{BASE_OUTER_RAD * cos(angle),
		BASE_OUTER_RAD * sin(angle), -Z};
	b4 = vec3{BASE_OUTER_RAD  * cos(angle + d_angle),
		BASE_OUTER_RAD  * sin(angle + d_angle), -Z};

	// start quad
	base_quad_all_index.push_back(base_quad_all_points.size());
	base_quad_all_points.push_back(b1);
	base_quad_all_index.push_back(base_quad_all_points.size());
	base_quad_all_points.push_back(b3);
	base_quad_all_index.push_back(base_quad_all_points.size());
	base_quad_all_points.push_back(b4);
	base_quad_all_index.push_back(base_quad_all_points.size());
	base_quad_all_points.push_back(b2);

	base_quad_all_colors.push_back(base_color);
	base_quad_all_colors.push_back(base_color);
	base_quad_all_colors.push_back(base_color);
	base_quad_all_colors.push_back(base_color);

	// start top circular face of cylinder
	base_tri_all_index.push_back(0);
	base_tri_all_points.push_back(center_base);
	base_tri_all_colors.push_back(base_color);

	base_tri_all_index.push_back(1);
	base_tri_all_points.push_back(b1);
	base_tri_all_colors.push_back(base_color);

     for (int s = 0; s < BASE_SEGMENT_SUBDIV; s++) {
    	 angle  += d_angle;
    	 b1 = b2;
    	 b3 = b4;
         b2 = vec3{BASE_OUTER_RAD * cos(angle),
        	 BASE_OUTER_RAD * sin(angle), Z};
         b4 =  vec3{BASE_OUTER_RAD * cos(angle),
        	 BASE_OUTER_RAD * sin(angle), -Z};

         base_quad_all_index.push_back(base_quad_all_points.size()-1);
         base_quad_all_index.push_back(base_quad_all_points.size()-2);
         base_quad_all_index.push_back(base_quad_all_points.size());
         base_quad_all_points.push_back(b4);
         base_quad_all_index.push_back(base_quad_all_points.size());
         base_quad_all_points.push_back(b2);

         base_quad_all_colors.push_back(base_color);
         base_quad_all_colors.push_back(base_color);

		if(s < BASE_SEGMENT_SUBDIV/2){
			base_color.x += 0.007f;
			base_color.y += 0.007f;
			base_color.z += 0.007f;
		}else{
			base_color.x -= 0.007f;
			base_color.y -= 0.007f;
			base_color.z -= 0.007f;
		}

		// top
		base_tri_all_index.push_back(0);
		base_tri_all_index.push_back(base_tri_all_points.size()-1);
		base_tri_all_points.push_back(b2);
		base_tri_all_index.push_back(base_tri_all_points.size()-1);
		base_tri_all_colors.push_back(base_color);
     }

	// top last triangle
	angle  += d_angle;
	b2 = vec3{BASE_OUTER_RAD * cos(angle),
		BASE_OUTER_RAD * sin(angle), Z};
	base_tri_all_index.push_back(0);
	base_tri_all_index.push_back(base_tri_all_points.size()-2);
	base_tri_all_points.push_back(b2);
	base_tri_all_index.push_back(base_tri_all_points.size()-2);
	base_tri_all_colors.push_back(base_color);

    // reset colors
	base_color.x = 0.19f;
	base_color.y = 0.19f;
	base_color.z = 0.19f;

	// start top circular face of cylinder
	hold = base_tri_all_points.size();
	base_tri_all_index.push_back(hold);
	base_tri_all_points.push_back(center_base_low);
	base_tri_all_colors.push_back(base_color);

	base_tri_all_index.push_back(base_tri_all_points.size());
	base_tri_all_points.push_back(b4);
	base_tri_all_colors.push_back(base_color);

	// bottom triangle face
    for (int s = 0; s < BASE_SEGMENT_SUBDIV; s++) {
		angle  += d_angle;
		b4 =  vec3{BASE_OUTER_RAD * cos(angle),
			BASE_OUTER_RAD * sin(angle), -Z};

		if(s < BASE_SEGMENT_SUBDIV/2){
			base_color.x -= 0.005f;
			base_color.y -= 0.005f;
			base_color.z -= 0.005f;
		}else{
			base_color.x += 0.005f;
			base_color.y += 0.005f;
			base_color.z += 0.005f;
		}
		// bottom
		base_tri_all_index.push_back(hold);
		base_tri_all_index.push_back(base_tri_all_points.size()-1);
		base_tri_all_points.push_back(b4);
		base_tri_all_index.push_back(base_tri_all_points.size()-2);
		base_tri_all_colors.push_back(base_color);
    }
	// bottom last triangle
	angle  += d_angle;
	b4 =  vec3{BASE_OUTER_RAD * cos(angle),
		BASE_OUTER_RAD * sin(angle), -Z};
	base_tri_all_index.push_back(0);
	base_tri_all_index.push_back(base_tri_all_points.size()-1);
	base_tri_all_points.push_back(p4);
	base_tri_all_index.push_back(base_tri_all_points.size()-2);
	base_tri_all_colors.push_back(base_color);

    /* USED FOR QUAD FACES OF CYLINDER */
    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, base_quad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, base_quad_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    ptr = vertex_ptr;
    for (auto v : base_quad_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, base_quad_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, base_quad_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : base_quad_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, base_quad_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, base_quad_all_index.size() * sizeof(GLushort), base_quad_all_index.data(), GL_DYNAMIC_DRAW);

    /* USED FOR TRI FACES OF CYLINDER */
    /* Allocate memory for vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, base_tri_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, base_tri_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    ptr = vertex_ptr;
    for (auto v : base_tri_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, base_tri_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, base_tri_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : base_tri_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, base_tri_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, base_tri_all_index.size() * sizeof(GLushort), base_tri_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// this overrides the render in QuadOrTriBufferObject.h
void StreetLamp::render(bool outline) const {

	float lamp_x = 2.097f, lamp_y = 2.57f, lamp_z = 0.0f;
	float elbow_x = 3.0f, elbow_y = 2.7f, elbow_z = 0.0f;
	float post_x = 3.90f, post_y = 0.355f, post_z = 0.0f;
	float base_x = 3.90f, base_y = -1.4f, base_z = 0.0f;

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

		glPushMatrix();
		glTranslatef(elbow_x,elbow_y,elbow_z);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, quad_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
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
		glPopMatrix();
    }

	if(cone_quad_all_points.size() > 0){
		/* bind vertex buffer */
		if (glIsBuffer(cone_quad_vertex_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, cone_quad_vertex_buffer);
			glVertexPointer(3, GL_FLOAT, 0, 0);
		}
		/* bind color buffer */
		if (glIsBuffer(cone_quad_color_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, cone_quad_color_buffer);
			glColorPointer(3, GL_FLOAT, 0, 0);
		}

		/* bind the index buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_quad_index_buffer);

		glPushMatrix();
		glTranslatef(lamp_x,lamp_y,lamp_z);
		glRotatef(-90,1,0,0);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, cone_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
			/* remove from BEGIN to END to disable rendering the polygon outline */
			glPolygonMode(GL_FRONT, GL_LINE);

			glEnable(GL_POLYGON_OFFSET_LINE);
			/* With polygon offset enabeld,  lines are rendered away from the polygons.
			Negative offset: lines are now rendered CLOSER to the camera */
			glPolygonOffset(-1.0, 1);

			glDisableClientState(GL_COLOR_ARRAY);
			glColor3ub(255, 255, 255);
			glDrawElements(GL_QUADS, cone_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		glPopMatrix();
    }

	//////////////  RENDER CYCLINDER (POST) //////////////

    if(post_quad_all_points.size() > 0){
		/* bind vertex buffer */
		if (glIsBuffer(post_quad_vertex_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, post_quad_vertex_buffer);
			glVertexPointer(3, GL_FLOAT, 0, 0);
		}
		/* bind color buffer */
		if (glIsBuffer(post_quad_color_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, post_quad_color_buffer);
			glColorPointer(3, GL_FLOAT, 0, 0);
		}

		/* bind the index buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, post_quad_index_buffer);

		glPushMatrix();
		glTranslatef(post_x,post_y,post_z);
		glRotatef(-90,1,0,0);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, post_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
			/* remove from BEGIN to END to disable rendering the polygon outline */
			glPolygonMode(GL_FRONT, GL_LINE);

			glEnable(GL_POLYGON_OFFSET_LINE);
			/* With polygon offset enabeld,  lines are rendered away from the polygons.
			Negative offset: lines are now rendered CLOSER to the camera */
			glPolygonOffset(-1.0, 1);

			glDisableClientState(GL_COLOR_ARRAY);
			glColor3ub(255, 255, 255);
			glDrawElements(GL_QUADS, post_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		glPopMatrix();
    }

    if(post_tri_all_points.size() > 0){
		/* bind vertex buffer */
		if (glIsBuffer(post_tri_vertex_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, post_tri_vertex_buffer);
			glVertexPointer(3, GL_FLOAT, 0, 0);
		}
		/* bind color buffer */
		if (glIsBuffer(post_tri_color_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, post_tri_color_buffer);
			glColorPointer(3, GL_FLOAT, 0, 0);
		}

		/* bind the index buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, post_tri_index_buffer);

		glPushMatrix();
		glTranslatef(post_x,post_y,post_z);
		glRotatef(-90,1,0,0);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, post_tri_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
			/* remove from BEGIN to END to disable rendering the polygon outline */
			glPolygonMode(GL_FRONT, GL_LINE);

			glEnable(GL_POLYGON_OFFSET_LINE);
			/* With polygon offset enabeld,  lines are rendered away from the polygons.
			Negative offset: lines are now rendered CLOSER to the camera */
			glPolygonOffset(-1.0, 1);

			glDisableClientState(GL_COLOR_ARRAY);
			glColor3ub(255, 255, 255);
			glDrawElements(GL_QUADS, post_tri_all_index.size(), GL_UNSIGNED_SHORT, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		glPopMatrix();
    }


	//////////////  RENDER CYCLINDER (BASE) //////////////

    if(base_quad_all_points.size() > 0){
		/* bind vertex buffer */
		if (glIsBuffer(base_quad_vertex_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, base_quad_vertex_buffer);
			glVertexPointer(3, GL_FLOAT, 0, 0);
		}
		/* bind color buffer */
		if (glIsBuffer(base_quad_color_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, base_quad_color_buffer);
			glColorPointer(3, GL_FLOAT, 0, 0);
		}

		/* bind the index buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, base_quad_index_buffer);

		glPushMatrix();
		glTranslatef(base_x,base_y,base_z);
		glRotatef(-90,1,0,0);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, base_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
			/* remove from BEGIN to END to disable rendering the polygon outline */
			glPolygonMode(GL_FRONT, GL_LINE);

			glEnable(GL_POLYGON_OFFSET_LINE);
			/* With polygon offset enabeld,  lines are rendered away from the polygons.
			Negative offset: lines are now rendered CLOSER to the camera */
			glPolygonOffset(-1.0, 1);

			glDisableClientState(GL_COLOR_ARRAY);
			glColor3ub(255, 255, 255);
			glDrawElements(GL_QUADS, base_quad_all_index.size(), GL_UNSIGNED_SHORT, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		glPopMatrix();
    }

    if(base_tri_all_points.size() > 0){
		/* bind vertex buffer */
		if (glIsBuffer(base_tri_vertex_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, base_tri_vertex_buffer);
			glVertexPointer(3, GL_FLOAT, 0, 0);
		}
		/* bind color buffer */
		if (glIsBuffer(base_tri_color_buffer)) {
			glBindBuffer(GL_ARRAY_BUFFER, base_tri_color_buffer);
			glColorPointer(3, GL_FLOAT, 0, 0);
		}

		/* bind the index buffer */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, base_tri_index_buffer);

		glPushMatrix();
		glTranslatef(base_x,base_y,base_z);
		glRotatef(-90,1,0,0);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, base_tri_all_index.size(), GL_UNSIGNED_SHORT, 0);

		if (outline) {
			/* remove from BEGIN to END to disable rendering the polygon outline */
			glPolygonMode(GL_FRONT, GL_LINE);

			glEnable(GL_POLYGON_OFFSET_LINE);
			/* With polygon offset enabeld,  lines are rendered away from the polygons.
			Negative offset: lines are now rendered CLOSER to the camera */
			glPolygonOffset(-1.0, 1);

			glDisableClientState(GL_COLOR_ARRAY);
			glColor3ub(255, 255, 255);
			glDrawElements(GL_QUADS, base_tri_all_index.size(), GL_UNSIGNED_SHORT, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		glPopMatrix();
    }
}

void StreetLamp::build(void *data) {
    int lev = *((int *) data);
    init_model(lev);

    post_build(); /* must call post_build(), to allow actual rendering */
}

