/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The object class
 *  This is a generic type for storing objects in the scene.
 *  Being an abstract class, this class cannot be instantiated.
 *  Sphere, Plane etc, must be defined as subclasses of Object
 *      and provide implementations for the virtual functions
 *      intersect()  and normal().
 -------------------------------------------------------------*/

#ifndef H_OBJECT
#define H_OBJECT

#include "Vector.hpp"
#include "Color.hpp"

class Object 
{
protected:
    Color color;
public:
    bool reflective;
    bool transparent;

    Object() {}
    Object(bool reflective, bool transparent)
	: reflective(reflective), transparent(transparent)
	{}
    virtual float intersect(Vector pos, Vector dir) = 0;
    virtual Vector normal(Vector pos) = 0;
    virtual ~Object() {}
    virtual Color getColor(Vector);
    void setColor(Color col);
};

#endif
