#define _USE_MATH_DEFINES
#include <cmath>
#include "Ground.h"

using glm::vec3;
void Ground::build(void* data) {

    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);

    vec3 temp;
	temp.x = -100;
	temp.y = -5;
	temp.z = 100;
	all_points.push_back(temp);

	temp.x = 100;
	temp.y = -5;
	temp.z = 100;
	all_points.push_back(temp);

	temp.x = -100;
	temp.y = -5;
	temp.z = -100;
	all_points.push_back(temp);

	temp.x = 100;
	temp.y = -5;
	temp.z = -100;
	all_points.push_back(temp);


    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ground::render(bool outline) const {
    const float& S = 1;
    int j = 0;
    int m = 0;

    /* draw the axes */
    glBegin(GL_LINES);
    glColor3ub (255, 0, 0);
    glVertex2i (0, 0);
    glVertex2f (S * 1.1, 0);
    glColor3ub (0, 255, 0);
    glVertex2i (0, 0);
    glVertex2f (0, S * 1.1);
    glColor3ub (0, 0, 255);
    glVertex2i (0, 0);
    glVertex3f (0, 0, S * 1.1);
    glEnd();

    /* floor */
    int floor_dim = S*2;
    int extension = 10;
    float color_vary_r = 0;
    float color_vary_g = 0;
    float color_vary_b = 0;
    int res = 8.0f;
	glBegin(GL_QUAD_STRIP);
	int reduce_color_change = 0;

    for(j = (-floor_dim-extension)*res; j < (floor_dim+extension)*res; j++){
    	for(m = (-floor_dim-extension)*res; m < (floor_dim+extension)*res; m++){
			glBegin(GL_QUAD_STRIP);
			glColor3ub (30 + color_vary_r ,30+ color_vary_g  ,30 + color_vary_b );

			glVertex3f(m/res, -floor_dim, j/res);
			glVertex3f(m/res, -floor_dim, (j + 1)/res);
			glVertex3f((m + 1)/res, -floor_dim, j/res);
			glVertex3f((m + 1)/res, -floor_dim, (j+1)/res);
			glEnd();
    	}
    	if(j < 0){
			if(color_vary_r < 160 && reduce_color_change % 2 == 0){
				color_vary_r+=0.2;
				color_vary_g+=0.2;
				color_vary_b+=0.1;
			}
			reduce_color_change++;
    	}else{
			if(color_vary_r < 160 && reduce_color_change % 2 == 0){
				color_vary_r-=0.2;
				color_vary_g-=0.2;
				color_vary_b-=0.1;
			}
			reduce_color_change--;
    	}
    }

}
