/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The plane class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#ifndef H_TEXPLANE
#define H_TEXPLANE
#include <iostream>
#include <vector>
#include "Object.hpp"
#include "Vector.hpp"
/**
 * Define a textured Plane that is entirely flat
 */
class TexturedPlane : public Plane {
private:
    std::vector<std::vector<Color> > texture;
    float width, height;
    int texwidth, texheight; 
public:  
    //Default constructor creates a unit plane

    TexturedPlane() : Plane() {
	color = Color::WHITE;
	texture.push_back(std::vector<Color>());
	texture[0].push_back(Color());
    };
    
    TexturedPlane(Vector topleft, float width, float height, bool reflective, bool transparent, std::vector<std::vector<Color> > texture)
	: Plane(topleft, topleft+Vector(width,0,0), topleft+Vector(0,0,height), topleft+Vector(width,0,height), Color::WHITE, reflective, transparent), texture(texture) {
	width = (topleft - topright).length();
	height = (topleft - bottomleft).length();

	texwidth = texture.size();
	texheight = texture[0].size();
    };

    Vector normal(Vector pos) {
	return Vector(0, 1, 0);
    }

    Color getColor(Vector p) {
	// Vector tex(texwidth, 0, texheight);
	Vector v = p - topleft;
	v /= 3; 

	float w = v.x * texwidth;
	float h = v.z * texheight;

	int x = fmodf(w+2000, texwidth);
	int z = fmodf(h+2000, texheight);

	return texture[x][z];
    }
};

#endif //!H_TEXPLANE
