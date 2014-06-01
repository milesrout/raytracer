/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The plane class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#include "Plane.hpp"
#include <math.h>

/**
 * Plane's intersection method.  The input is a ray (pos, dir). 
 */
float Plane::intersect(Vector pos, Vector dir)
{
    Vector dummy;
    Vector n = normal(dummy);
    float t = (topleft - pos).dot(n) / dir.dot(n);
    
    Vector a = pos;
    Vector b = topleft;
    Vector c = topright;
    Vector d = bottomleft;
    Vector e = bottomright;

    bool pred = b.dot(c - b) <= a.dot(c - b) && a.dot(c - b) <= c.dot(c - b) &&
	        b.dot(e - b) <= a.dot(e - b) && a.dot(e - b) <= e.dot(e - b);

    if (pred && t > 0.0)
	return t;
    return -1.0f;
}

/**
 * Returns the unit normal vector at a given point.
 * Assumption: The input point p lies on the plane.
 */
Vector Plane::normal(Vector)
{
    Vector n = (topleft - topright).cross(topleft - bottomleft);
    n.normalise();
    return n;
    // return Vector(0,1,0);
}
