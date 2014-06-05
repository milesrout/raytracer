/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The sphere class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#include "Cylinder.hpp"
#include <math.h>

/**
 * Cylinder's intersection method. The input is a ray (pos, dir).
 */
float Cylinder::intersect(Vector pos, Vector dir)
{
    return -1.0f;
}

/**
 * Returns the unit normal vector at a given point.
 * Assumption: The input point p lies on the sphere.
 */
Vector Cylinder::normal(Vector p)
{
    // the lid
    if (p.y - base.y - height <= 0.001) {
	return Vector(0, 1, 0);
    }
    // the base
    else if (p.y - base.y <= 0.001) {
	return Vector(0, -1, 0);
    }
    // the side
    else {
	// the angle around the cylinder for this point
	Vector n = p - base;
	n.y = 0;
	n.normalise();
	return n;
    }
}
