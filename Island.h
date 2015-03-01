/*
 * Island.h
 *
 *  Created on: Feb 28, 2015
 *      Author: dan
 */

#ifndef ISLAND_H_
#define ISLAND_H_
#include <vector>
#include <glm/vec3.hpp>
#include "QuadOrTriBufferObject.h"
using namespace std;

class Island : public QuadOrTriBufferObject {
private:
    const int SEGMENT_SUBDIV = 18;
    const float OUTER_RAD = 1.3;
    const float INNER_RAD = 1.1;
    const float THICKNESS = 0.15; /* half thick */
    int top_count, pts_count;
    void init_model(int level);
protected:
public:
    void build (void*);
    void render(bool) const override;  // override the render in QuadOrTriBuffer.h
};

#endif /* ISLAND_H_ */
