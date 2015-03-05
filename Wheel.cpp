#define _USE_MATH_DEFINES
#include <cmath>
#include "Wheel.h"

#define M_PI 3.14159265358979323846

using glm::vec3;

/* Calculates list of vertices, later used to build vertex buffer */
void Wheel::genTireVerts()
{
    //number of faces on tread / edges on circular side
    int num_divisions = 20;

    /* divide tire into a number of quads */
    float d_angle = 2 * M_PI / (num_divisions * SEGMENT_SUBDIV);
    const float D60 = M_PI / (num_divisions * 3);
    float angle = 0;

    vec3 c1, c2;

    float Z = TIRE_THICKNESS;
    for (int s = 0; s < num_divisions; s++) {
        c1 = vec3{TIRE_OUTER_RAD * cos(angle),
        	TIRE_OUTER_RAD * sin(angle), Z};
        c2 = vec3{TIRE_OUTER_RAD * cos(angle + D60),
        	TIRE_OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < SEGMENT_SUBDIV; k++) {
            float t = (float) k / SEGMENT_SUBDIV;
            vec3 v1{TIRE_INNER_RAD * cos(angle),
            	TIRE_INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            tire_all_index.push_back(tire_all_points.size());
            tire_all_points.push_back(v1);
            tire_all_index.push_back(tire_all_points.size());
            tire_all_points.push_back(v2);
            angle  += d_angle;
        }
    }

    /* repeat the first two vertices to complete the quad */
    tire_pts_count = tire_all_index.size();
    tire_all_index.push_back(0);
    tire_all_index.push_back(1);
    tire_top_count = tire_all_index.size();

    Z = -TIRE_THICKNESS;
    for (int s = 0; s < num_divisions; s++) {
        c1 = vec3{TIRE_OUTER_RAD * cos(angle),
        	TIRE_OUTER_RAD * sin(angle), Z};
        c2 = vec3{TIRE_OUTER_RAD * cos(angle + D60),
        	TIRE_OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < SEGMENT_SUBDIV; k++) {
            float t = (float) k / SEGMENT_SUBDIV;
            vec3 v1{TIRE_INNER_RAD * cos(angle),
            	TIRE_INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            tire_all_index.push_back(tire_all_points.size());
            tire_all_points.push_back(v1);
            tire_all_index.push_back(tire_all_points.size());
            tire_all_points.push_back(v2);
            angle  += d_angle;
        }
    }
    tire_all_index.push_back(tire_pts_count);
    tire_all_index.push_back(tire_pts_count + 1);

    /* indices for the outer walls */
    for (int k = 0; k < num_divisions * SEGMENT_SUBDIV; k++) {
    	tire_all_index.push_back(2*k + 1);
    	tire_all_index.push_back(2*k + 1 + tire_pts_count);
    }
    tire_all_index.push_back(1);
    tire_all_index.push_back(tire_pts_count + 1);

    /* indices for the inner walls */
    for (int k = 0; k < num_divisions * SEGMENT_SUBDIV; k++) {
    	tire_all_index.push_back(2*k + tire_pts_count);
    	tire_all_index.push_back(2*k);
    }
    tire_all_index.push_back(tire_pts_count);
    tire_all_index.push_back(0);
}

/* Calculates list of vertices, later used to build vertex buffer */
void Wheel::genHubVerts()
{
    int num_divisions = 28;

    /* divide hub into a number of quads */
    float d_angle = 2 * M_PI / (num_divisions * SEGMENT_SUBDIV);
    const float D60 = M_PI / (num_divisions * 3);
    float angle = 0;
    float x = 0.45f, y = 0.45f, z = 0.45f;
    vec3 hub_colors{x,y,z};

    vec3 c1, c2;

    // front hub face
    float Z = HUB_THICKNESS;
    vec3 v1{0,0, Z+0.07};

    hub_all_points.push_back(v1);
    hub_all_colors.push_back(hub_colors);

    for (int s = 0; s < num_divisions; s++) {
        c1 = vec3{HUB_OUTER_RAD * cos(angle),
        	HUB_OUTER_RAD * sin(angle), Z};
        c2 = vec3{HUB_OUTER_RAD * cos(angle + D60),
        	HUB_OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < SEGMENT_SUBDIV; k++) {
            float t = (float) k / SEGMENT_SUBDIV;
            vec3 v2{t*c2 + (1-t)*c1};
            hub_all_index.push_back(0);
            hub_all_index.push_back(hub_all_points.size());
            hub_all_points.push_back(v2);
            hub_all_colors.push_back(hub_colors);
            angle  += d_angle;
        }
        // change colors for next points
        if(s < num_divisions/2){
			hub_colors.x += 0.07f;
			hub_colors.y += 0.07f;
			hub_colors.z += 0.07f;
        }else{
			hub_colors.x -= 0.07f;
			hub_colors.y -= 0.07f;
			hub_colors.z -= 0.07f;
        }
    }

    /* repeat the first two vertices to complete the tri */
    hub_all_index.push_back(0);
    hub_all_index.push_back(1);
    hub_all_index.push_back(2);
    hub_top_count = hub_all_index.size();

    hub_colors.x = 0.45f;
    hub_colors.y = 0.45f;
    hub_colors.z = 0.45f;

    // back hub face
    Z = -HUB_THICKNESS;
    vec3 bottom_circle_center{0,0, Z};
    int bottom_circle_center_index = hub_all_points.size();
    int save_last_index = hub_all_points.size();
    hub_all_points.push_back(bottom_circle_center);

     for (int s = 0; s < num_divisions; s++) {
         c1 = vec3{HUB_OUTER_RAD * cos(angle),
         	HUB_OUTER_RAD * sin(angle), Z};
         c2 = vec3{HUB_OUTER_RAD * cos(angle + D60),
         	HUB_OUTER_RAD * sin(angle + D60), Z};
         for (int k = 0; k < SEGMENT_SUBDIV; k++) {
             float t = (float) k / SEGMENT_SUBDIV;
             vec3 v2{t*c2 + (1-t)*c1};
             hub_all_index.push_back(bottom_circle_center_index);
             hub_all_index.push_back(hub_all_points.size());
             hub_all_points.push_back(v2);
             hub_all_colors.push_back(hub_colors);
             angle  += d_angle;
         }
         // change colors for next points
         if(s < num_divisions/2){
 			hub_colors.x += 0.02f;
 			hub_colors.y += 0.02f;
 			hub_colors.z += 0.02f;
         }else{
 			hub_colors.x -= 0.02f;
 			hub_colors.y -= 0.02f;
 			hub_colors.z -= 0.02f;
         }
     }
     hub_colors.x = 0.45f;
     hub_colors.y = 0.45f;
     hub_colors.z = 0.45f;
     /* repeat the first two vertices to complete the tri */
     hub_all_index.push_back(save_last_index + 1);
     hub_all_colors.push_back(hub_colors);
     //hub_all_index.push_back(save_last_index + 2);
     //hub_all_index.push_back(save_last_index + 3);
     hub_top_count = hub_all_index.size();
}

void Wheel::genNutVerts() {

    glGenBuffers(1, &hex_vertex_buffer);
    glGenBuffers(1, &hex_index_buffer);
    /* A mechanical nut has 6 identical segments */
    float d_angle = 2 * M_PI / (6 * HEX_SEGMENT_SUBDIV);
    const float D60 = M_PI / 3;
    float angle = 0;
    vec3 c1, c2;
    float Z = HEX_THICKNESS;
    for (int s = 0; s < 6; s++) {
        c1 = vec3{HEX_OUTER_RAD * cos(angle),
        	HEX_OUTER_RAD * sin(angle), Z};
        c2 = vec3{HEX_OUTER_RAD * cos(angle + D60),
        	HEX_OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < HEX_SEGMENT_SUBDIV; k++) {
            float t = (float) k / HEX_SEGMENT_SUBDIV;
            vec3 v1{HEX_INNER_RAD * cos(angle),
            	HEX_INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            hex_all_index.push_back(hex_all_points.size());
            hex_all_points.push_back(v1);
            hex_all_index.push_back(hex_all_points.size());
            hex_all_points.push_back(v2);
            angle += d_angle;
        }
    }
    /* repeat the first two vertices to complete the quad */
    hex_pts_count = hex_all_index.size();
    hex_all_index.push_back(0);
    hex_all_index.push_back(1);
    hex_top_count = hex_all_index.size();

    Z = -HEX_THICKNESS;
    for (int s = 0; s < 6; s++) {
        c1 = vec3{HEX_OUTER_RAD * cos(angle),
        	HEX_OUTER_RAD * sin(angle), Z};
        c2 = vec3{HEX_OUTER_RAD * cos(angle + D60),
        	HEX_OUTER_RAD * sin(angle + D60), Z};
        for (int k = 0; k < HEX_SEGMENT_SUBDIV; k++) {
            float t = (float) k / HEX_SEGMENT_SUBDIV;
            vec3 v1{HEX_INNER_RAD * cos(angle),
            	HEX_INNER_RAD * sin(angle), Z};
            vec3 v2{t*c2 + (1-t)*c1};
            hex_all_index.push_back(hex_all_points.size());
            hex_all_points.push_back(v1);
            hex_all_index.push_back(hex_all_points.size());
            hex_all_points.push_back(v2);
            angle  += d_angle;
        }
    }
    hex_all_index.push_back(hex_pts_count);
    hex_all_index.push_back(hex_pts_count + 1);

    /* indices for the outer walls */
    for (int k = 0; k < 6 * HEX_SEGMENT_SUBDIV; k++) {
    	hex_all_index.push_back(2*k + 1);
    	hex_all_index.push_back(2*k + 1 + hex_pts_count);
    }
    hex_all_index.push_back(1);
    hex_all_index.push_back(hex_pts_count + 1);

    /* indices for the inner walls */
    for (int k = 0; k < 6 * HEX_SEGMENT_SUBDIV; k++) {
    	hex_all_index.push_back(2*k + hex_pts_count);
    	hex_all_index.push_back(2*k);
    }
    hex_all_index.push_back(hex_pts_count);
    hex_all_index.push_back(0);
}

/* builds the vertex buffer */
void Wheel::build(void* data)
{
	float *vertex_ptr;
	float *ptr;

	//// TIRE /////
    glGenBuffers(1, &tire_vertex_buffer);
    glGenBuffers(1, &tire_index_buffer);

    //create the all_points list and all_vertices list
    Wheel::genTireVerts();

    glBindBuffer(GL_ARRAY_BUFFER, tire_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, tire_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // Initialize the vertices
    ptr = vertex_ptr;
    for (auto v : tire_all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Initialize the indices

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tire_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tire_all_index.size() * sizeof(GLushort), tire_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ////  HUB ////

    if (!glIsBuffer(hub_vertex_buffer))
        glGenBuffers(1, &hub_vertex_buffer);
    if (!glIsBuffer(hub_color_buffer))
        glGenBuffers(1, &hub_color_buffer);
    if (!glIsBuffer(hub_index_buffer))
        glGenBuffers(1, &hub_index_buffer);
    hub_all_points.clear();
    hub_all_colors.clear();
    hub_all_index.clear();

    //create the all_points list and all_vertices list
    Wheel::genHubVerts();

    glBindBuffer(GL_ARRAY_BUFFER, hub_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, hub_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    // Initialize the vertices
    ptr = vertex_ptr;
    for (auto v : hub_all_points) {
    	ptr[0] = v.x;
    	ptr[1] = v.y;
    	ptr[2] = v.z;
    	ptr += 3;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    // Initialize the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hub_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, hub_all_index.size() * sizeof(GLushort), hub_all_index.data(), GL_DYNAMIC_DRAW);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, hub_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, hub_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : hub_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Allocate memory for color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, hub_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, hub_all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);

    /* map the address from GPU memory to CPU memory */
    color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the colors */
    ptr = color_ptr;
    for (auto v : hub_all_colors) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hub_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, hub_all_index.size() * sizeof(GLushort), hub_all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//// HEXNUT /////

	//create the all_points list and all_vertices list
	Wheel::genNutVerts();

	glBindBuffer(GL_ARRAY_BUFFER, hex_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, hex_all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
	vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	/* Initialize the vertices */
	ptr = vertex_ptr;
	for (auto v : hex_all_points) {
		ptr[0] = v.x;
		ptr[1] = v.y;
		ptr[2] = v.z;
		ptr += 3;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Initialize the indices */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hex_index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, hex_all_index.size() * sizeof(GLushort), hex_all_index.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Wheel::render(bool outline) const {

	// bind vertex buffer
	 //// Tire IS RENDERED HERE
    glBindBuffer(GL_ARRAY_BUFFER, tire_vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tire_index_buffer);
    // render the polygon
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (20, 20, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, tire_top_count, GL_UNSIGNED_SHORT, 0);
    glFrontFace(GL_CW);
    glColor3ub (0, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, tire_top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (tire_top_count)));
    glFrontFace(GL_CCW);
    glColor3ub (0, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, tire_top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (2*tire_top_count)));
    glFrontFace(GL_CCW);
    glColor3ub (60, 60, 60);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, tire_top_count, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (3*tire_top_count)));

    // unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //// HUB IS RENDERED HERE

    glEnableClientState(GL_COLOR_ARRAY);

	/* bind vertex buffer */
	if (glIsBuffer(hub_vertex_buffer)) {
		glBindBuffer(GL_ARRAY_BUFFER, hub_vertex_buffer);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	}
	/* bind color buffer */
	if (glIsBuffer(hub_color_buffer)) {
		glBindBuffer(GL_ARRAY_BUFFER, hub_color_buffer);
		glColorPointer(3, GL_FLOAT, 0, 0);
	}

	/* bind the index buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hub_index_buffer);

	/* render the polygon */
	glPolygonMode(GL_FRONT, GL_FILL);
	glDrawElements(GL_TRIANGLE_STRIP, hub_all_index.size(), GL_UNSIGNED_SHORT, 0);


    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ///// HEXNUT RENDERED HERE
    float hex_x = 0.0f, hex_y = 0.0f;
    int num_hex_nuts = 5;
    float curr_angle = 0.0f;
    float angle_change = 360.0f / num_hex_nuts;
    float hex_pattern_radius = 0.10f;

    for(int i = 0; i < num_hex_nuts; i++){
    	glPushMatrix();
    	glRotatef(curr_angle,0,0,1);
    	glPushMatrix();
    	glTranslatef(hex_pattern_radius,hex_pattern_radius,0.015f);
    	curr_angle += angle_change;

		/* bind vertex buffer */
		glBindBuffer(GL_ARRAY_BUFFER, hex_vertex_buffer);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDisableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hex_index_buffer);
		/* render the polygon */
		glPolygonMode(GL_FRONT, GL_FILL);
		glFrontFace(GL_CCW);
		glColor3ub (192,192,192);
		glDrawRangeElements(GL_QUAD_STRIP, 0, 0, hex_top_count, GL_UNSIGNED_SHORT, 0);
		glFrontFace(GL_CW);
		glColor3ub (192,192,192);
		glDrawRangeElements(GL_QUAD_STRIP, 0, 0, hex_top_count, GL_UNSIGNED_SHORT,
				(void *) (sizeof(GLushort) * (hex_top_count)));
		glFrontFace(GL_CCW);
		glColor3ub (100,100,100);
		glDrawRangeElements(GL_QUAD_STRIP, 0, 0, hex_top_count, GL_UNSIGNED_SHORT,
				(void *) (sizeof(GLushort) * (2*hex_top_count)));
		glFrontFace(GL_CCW);
		glColor3ub (100,100,100);
		glDrawRangeElements(GL_QUAD_STRIP, 0, 0, hex_top_count, GL_UNSIGNED_SHORT,
				(void *) (sizeof(GLushort) * (3*hex_top_count)));

		/* unbind the buffers */
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glEnableClientState(GL_COLOR_ARRAY);
		glPopMatrix();
		glPopMatrix();
    }

}

