/*----------------------------------------
 * COSC363 Ray Tracer
 *
 *  The box class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------*/

#ifndef H_BOX
#define H_BOX

#include "Object.h"

/**
 * Defines a simple Box located at 'center'
 * with the specified width
 */
class Box : public Object {
private:
    Vector center;
    float width;

public:
    Box() : center(Vector()), width(1) // Default constructor creates a box with width 1.
	{
	    color = Color::WHITE;
	};

    Box(Vector c, float w, Color col)
	: center(c), width(w)
	{
	    color = col;
	};
    
    float intersect(Vector pos, Vector dir);

    Vector normal(Vector p);

};

#endif //!H_BOX
