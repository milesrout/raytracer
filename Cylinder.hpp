/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The cylinder class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#ifndef H_CYLINDER
#define H_CYLINDER

#include "Object.hpp"

/**
 * Defines a simple Cylinder located at 'center' 
 * with the specified radius
 */
class Cylinder : public Object {
private:
    Vector base;
    float radius;
    float height;
  
public:  
    Cylinder() : base(Vector()), radius(1), height(1)  //Default constructor creates a unit cylinder
	{
	    color = Color::WHITE;
	};
    
    Cylinder(Vector b, float r, float h, Color col, bool reflective, bool transparent)
	: base(b), radius(r), height(h), Object(reflective, transparent)
	{
	    color = col;
	};

    float intersect(Vector pos, Vector dir);
    
    Vector normal(Vector p);
    
};

#endif //!H_CYLINDER
