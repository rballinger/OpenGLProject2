/*
 * Ground.h
 *
 *  Created on: Feb 27, 2015
 *      Author: dan
 */

#ifndef GROUND_H_
#define GROUND_H_
#include <vector>
#include <glm/vec3.hpp>
#include "BufferObject.h"
using namespace std;

class Ground : public BufferObject {
private:

public:
    void build(void *);
    void render(bool) const;
    int top_count;
};

#endif /* GROUND_H_ */
