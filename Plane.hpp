/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The plane class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#ifndef H_PLANE
#define H_PLANE

#include "Object.hpp"
#include "Vector.hpp"
/**
 * Define a simple Plane with corners at each of 'corners'
 */
class Plane : public Object {
private:
    Vector topleft, topright, bottomleft, bottomright;
public:  
    //Default constructor creates a unit plane

    Plane() : topleft(Vector(0, 0, 0)),
	      topright(Vector(0, 1, 0)),
	      bottomright(Vector(1, 1, 0)),
	      bottomleft(Vector(1, 0, 0))
	{
	    color = Color::WHITE;
	};
    
  Plane(Vector topleft, Vector topright, Vector bottomleft, Vector bottomright, Color col, bool reflective, bool transparent)
    : topleft(topleft), topright(topright), bottomleft(bottomleft), bottomright(bottomright), Object(reflective, transparent)
	{
	    color = col;
	};
    
    float intersect(Vector pos, Vector dir);
    
    Vector normal(Vector p);
    
};

#endif //!H_PLANE
