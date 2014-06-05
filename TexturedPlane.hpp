/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The plane class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#ifndef H_TEXPLANE
#define H_TEXPLANE

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
	: Plane(topleft, topleft+Vector(width, 0, 0), topleft+Vector(0,0,height), topleft+Vector(width,0,height), Color::WHITE, reflective, transparent), texture(texture) {
      width = (topleft - topright).length();
      height = (topleft - bottomleft).length();
    };
    

    Color getColor(Vector p) {

	
    }
};

#endif //!H_TEXPLANE
