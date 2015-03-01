/*
 * Grass.h
 *
 *  Created on: Feb 28, 2015
 *      Author: dan
 */

#ifndef GRASS_H_
#define GRASS_H_
#include <vector>
#include <glm/vec3.hpp>
#include "QuadOrTriBufferObject.h"
using namespace std;

class Grass : public QuadOrTriBufferObject {
private:
    const int SEGMENT_SUBDIV = 10;
    const float RAD = 2.0f;
    void init_model(int level);
protected:
public:
    void build (void*);
    void render(bool) const override;  // override the render in QuadOrTriBuffer.h
};

#endif /* GRASS_H_ */
