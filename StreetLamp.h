/*
 * StreetLamp.h
 *
 *  Created on: Feb 27, 2015
 *      Author: dan
 */

#ifndef STREETLAMP_H_
#define STREETLAMP_H_
#include <vector>
#include <glm/vec3.hpp>
#include "QuadOrTriBufferObject.h"
using namespace std;

class StreetLamp : public QuadOrTriBufferObject {
private:

	// lamp elbow (torus) characteristics)
    const int PHETA_SUBDIV = 82;
    const int PHI_SUBDIV = 82;
    const float LITTLE_RAD = 0.10;
    const float BIG_RAD = 0.9;
    void init_model(int level);

    // lamp (cone) characteristics
    const int SEGMENT_SUBDIV = 78;
    const float OUTER_RAD = 0.7;
    const float TOP_RAD = 0.1;
    const float THICKNESS = 0.19;

    // post characteristics
    const int POST_SEGMENT_SUBDIV = 58;
    const float POST_OUTER_RAD = 0.10;
    const float POST_THICKNESS = 2.37; /* half thick */

    // base characteristics
    const int BASE_SEGMENT_SUBDIV = 58;
    const float BASE_OUTER_RAD = 0.5;
    const float BASE_THICKNESS = 0.6; /* half thick */

protected:
public:
    void build (void*);
    void render(bool) const override;  // override the render in QuadOrTriBuffer.h
};
#endif /* STREETLAMP_H_ */
