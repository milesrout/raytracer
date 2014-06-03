/*----------------------------------------------------------
 * COSC363  Ray Tracer
 *
 *  The plane class
 *  This is a subclass of Object, and hence implements the
 *  methods intersect() and normal().
 -------------------------------------------------------------*/

#ifndef H_TEXTURED_PLANE
#define H_TEXTURED_PLANE

#include <string>
#include <stdint.h>
#include "Plane.hpp"
#include "Object.hpp"
#include "Vector.hpp"

using namespace std;

/**
 * Define a simple Plane with corners at each of 'corners',
 * and with a texture.
 */
class TexturedPlane : public Plane {
private:
    bool texEnabled;
    ifstream texFile;
    uint8_t x_size;
    uint8_t y_size;
    Color *colors;
public:  
    //Default constructor creates a unit plane with no texture
    TexturedPlane() : texEnabled(false), Plane() {}

    TexturedPlane(Vector topleft, Vector topright, Vector bottomleft, Vector bottomright,
		  Color col, bool reflective, bool transparent, string textureFilename) 
	: texEnabled(true), texFile(textureFilename), 
	  Plane(topleft, topright, bottomleft, bottomright, Color::WHITE, reflective, transparent) {
	uint8_t magic;
	texFile.read(&magic, 1);
	if (magic != 0x18) throw runtime_error("wrong file format");
	
	texFile.read(&x_size, 1);
	texFile.read(&y_size, 1);

	colors = new Color[x_size][y_size];
	
	for (int i = 0; i < x_size; i++) {
	    for (int j = 0; j < y_size, j++) {
		uint8_t r, g, b; // 0 - 255
		texFile.read(&r, 1);
		texFile.read(&g, 1);
		texFile.read(&b, 1);

		Color col(r/255.0f, g/255.0f, b/255.0f);
		colors[i][j] = col;
	    }
	}
    }
};

#endif //!H_TEXTURED_PLANE
