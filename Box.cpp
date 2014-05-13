/*----------------------------------------
 * COSC363 Ray Tracer
 *
 *  The box class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------*/

#include "Box.h"
#include <math.h>

/** 
 * Box's intersection method. The input is ray (pos, dir).
 */
float Box::intersect(Vector pos, Vector dir)
{
    // test intersection with each plane
}

static bool compare(float a, float b)
{
    float delta = fabs(a - b);
    return delta < 0.001;
}

/**
 * Returns the unit normal vector at a given point.
 * Assumption: The input point p lies on the box.
 */
Vector Box::normal(Vector p)
{
    Vector n;

    if (compare(center.z + width, p.z)) {
	n.x = 0;
	n.y = 0;
	n.z = 1;
    }
    else if (compare(center.z - width, p.z)) {
	n.x = 0;
	n.y = 0;
	n.z = -1;
    }
    else if (compare(center.y + width, p.y)) {
	n.x = 0;
	n.y = 1;
	n.z = 0;
    }
    else if (compare(center.y - width, p.y)) {
	n.x = 0;
	n.y = -1;
	n.z = 0;
    }
    else if (compare(center.x + width, p.x)) {
	n.x = 1;
	n.y = 0;
	n.z = 0;
    }
    else if (compare(center.x - width, p.x)) {
	n.x = -1;
	n.y = 0;
	n.z = 0;
    }

    return n;
}
