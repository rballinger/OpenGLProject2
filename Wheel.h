/*
 * Wheel.h
 *
 *  Created on: Jan 30, 2015
 *      Author: dan
 */


#include "WheelBufferObject.h"
class Wheel : public WheelBufferObject {
private:
    const int SEGMENT_SUBDIV = 10;		// shared by tire and hub

    // tire characteristics
    const float TIRE_OUTER_RAD = 0.5;
    const float TIRE_INNER_RAD = 0.23;
    const float TIRE_THICKNESS = 0.16; /* half thick */

    // hub characteristics
    const float HUB_OUTER_RAD = 0.25;
    const float HUB_INNER_RAD = 0.075;
    const float HUB_THICKNESS = 0.11;

    // hex nut characteristics
    const int HEX_SEGMENT_SUBDIV = 3;
    const float HEX_OUTER_RAD = 0.044;
    const float HEX_INNER_RAD = 0.021;
    const float HEX_THICKNESS = 0.156; /* half thick */

    int tire_top_count, tire_pts_count;
    int hub_top_count, hub_pts_count;
    int hex_top_count, hex_pts_count;
protected:
public:
    void genTireVerts();
    void genHubVerts();
    void genNutVerts();
    void build (void*);
    void render(bool) const;
};

