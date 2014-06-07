/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The sphere class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#include "Cylinder.hpp"
#include <math.h>
#include <iostream>
#include <exception>
#include <stdexcept>

/**
 * Cylinder's intersection method. The input is a ray (pos, dir).
 */
float Cylinder::intersect(Vector pos, Vector dir)
{
    float x = pos.x - base.x;
    float z = pos.z - base.z;
    float a = dir.x*dir.x + dir.z*dir.z;
    float b = dir.x*x + dir.z*z;
    float c = x*x + z*z - radius*radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant <= 0) return -1.0f;

    float t1 = (-b + sqrt(discriminant)) / (2*a);
    float t2 = (-b - sqrt(discriminant)) / (2*a);

    if (t1 > 0) {
	if (t1 < t2) return t1;
	else if (t2 > 0) return t2;
	else return t1;
    }
    else if (t2 > 0) {
	return t2;
    }
    else {
	return -1.0f;
    }
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
