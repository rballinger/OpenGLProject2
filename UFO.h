/*
 * UFO.h
 *
 *  Created on: Jan 30, 2015
 *      Author: dan
 */

#ifndef UFO_H_
#define UFO_H_
#include "BufferObject.h"
class UFO : public BufferObject {
private:
    const int SEGMENT_SUBDIV = 3;
    const float OUTER_RAD = 2.3;
    const float INNER_RAD = 0.0;
    const float THICKNESS = 0.05; /* half thick */
    int top_count, pts_count;

protected:
public:
    void build (void*);
    void render(bool) const;
};

#endif /* UFO_H_ */
