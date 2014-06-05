// ========================================================================
// COSC 363  Computer Graphics  Lab07
// A simple ray tracer
// ========================================================================
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "TexturedPlane.hpp"
#include <GL/glut.h>
using namespace std;

#ifndef AALEVEL
#define AALEVEL 1
#endif /* AALEVEL */

const float WIDTH = 20.0;  
const float HEIGHT = 20.0;
const float EDIST = 30.0;
const int PPU = 60;     //Total 1200x1200 pixels
const int MAX_STEPS = 4;//10000;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;

vector<Object*> sceneObjects;
vector<vector<Color> > colours;

Vector light = Vector(10.0, 40.0, -5.0);
Color backgroundCol = Color::GRAY;

//A useful struct
struct PointBundle   
{
    Vector point;
    int index;
    float dist;
};

/*
 * This function compares the given ray with all objects in the scene
 * and computes the closest point  of intersection.
 */
PointBundle closestPt(Vector pos, Vector dir)
{
    Vector  point(0, 0, 0);
    float min = 10000.0;

    PointBundle out = {point, -1, 0.0};

    for(int i = 0;  i < sceneObjects.size();  i++) {
	float t = sceneObjects[i]->intersect(pos, dir);
	if(t > 0) { //Intersects the object
	    point = pos + dir*t;
	    if(t < min) {
		out.point = point;
		out.index = i;
		out.dist = t;
		min = t;
	    }
	}
    }

    return out;
}

/*
 * Computes the colour value obtained by tracing a ray.
 * If reflections and refractions are to be included, then secondary rays will 
 * have to be traced from the point, by converting this method to a recursive
 * procedure.
 */

Color trace(Vector pos, Vector dir, int step)
{
    PointBundle q = closestPt(pos, dir);

    if (q.index == -1) {

	return backgroundCol;        //no intersection
    }

    Object *obj = sceneObjects[q.index];
    Vector n = sceneObjects[q.index]->normal(q.point);
    Vector l = light - q.point;

    l.normalise();
    float lDotn = l.dot(n);
    Color col = sceneObjects[q.index]->getColor(q.point); //Object's colour
    PointBundle shadow = closestPt(q.point, l);

    // I have changed this around a bit so that ambient light is still
    // reflective, which it wasn't when I used the steps from the Lab
    // verbatim.
    Color colorSum;

    if (shadow.index != -1) { // there is an intersection
    	colorSum = col.phongLight(backgroundCol, 0.0f, 0.0f);
    } 

    Vector v(-dir.x, -dir.y, -dir.z);

    if (lDotn < 0.0) {
	colorSum = col.phongLight(backgroundCol, 0.0f, 0.0f);
    }
    else {
	Vector r = ((n * 2) * lDotn) - l;
	r.normalise();

	float rDotv = r.dot(v);
	float spec;
	if (rDotv < 0)
	    spec = 0.0;
	else
	    spec = pow(rDotv, 15);
	colorSum = col.phongLight(backgroundCol, lDotn, spec);
    }
	
    if (obj->reflective && step < MAX_STEPS) {
	Vector reflectionVector = ((n * 2) * n.dot(v)) - v;
	reflectionVector.normalise();
	float reflCoeff = 0.5f;
	if (lDotn < 0.0 || shadow.index != -1)
	    reflCoeff = 0.1f;
	Color reflectionCol = trace (q.point, reflectionVector, step+1);
	colorSum.combineColor(reflectionCol, reflCoeff);
    }

    if (obj->transparent && step < MAX_STEPS) {
	// We basically refract twice here: once on entering the
	// object and once on leaving.
	float transCoeff = 0.95f;

	// The inner refraction vector is the direction of the ray
	// when first refracted when entering the object.
	float eta1 = 1.0f;
	float eta2 = 1.01f;
	float eta = eta1/eta2;
	float dot = dir.dot(n);
	float cosThetaT = sqrt(1 - eta*eta * (1 - dot*dot));
	Vector innerRefrVector = dir*eta - n*(eta * dot + cosThetaT);
	
	// The outer refraction vector is the direction of the ray
	// when refracting again upon leaving the object.
	PointBundle outer = closestPt(q.point, innerRefrVector);
	Vector outerRefrVector;
	if (outer.index != -1) {
	    Object *outerObj = sceneObjects[outer.index];
	    Vector normal = outerObj->normal(outer.point) * -1;

	    float tmp = eta1;
	    eta1 = eta2;
	    eta2 = tmp;

	    eta = eta1/eta2;
	    dot = innerRefrVector.dot(normal);
	    cosThetaT = sqrt(1 - eta*eta * (1 - dot*dot));
	    outerRefrVector = dir*eta - normal*(eta * dot + cosThetaT);
	}
	else {
	    outerRefrVector = dir;
	}

	// I = I_A + \rho_C I_C
    	Color refractionCol = trace (outer.point, outerRefrVector, step+1);
    	colorSum.combineColor(refractionCol, transCoeff);
    }

    return colorSum;


}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each pixel as quads.
//---------------------------------------------------------------------------------------
void display()
{
    static int counter = 0;
    int widthInPixels = (int)(WIDTH * PPU);
    int heightInPixels = (int)(HEIGHT * PPU);
    float pixelSize = 1.0/PPU;
    float halfPixelSize = pixelSize/2.0;
    float x1, y1, xc, yc;

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);  //Each pixel is a quad.

    for(int i = 0; i < widthInPixels; i++) { //Scan every "pixel"
	x1 = XMIN + i*pixelSize;
	xc = x1 + halfPixelSize;
	for(int j = 0; j < heightInPixels; j++) {
	    y1 = YMIN + j*pixelSize;
	    yc = y1 + halfPixelSize;
	    
	    //Color col = trace (eye, dir, 1); //Trace the primary ray and get the colour value
	    Color col = colours[i][j];
	    glColor3f(col.r, col.g, col.b);
	    glVertex2f(x1, y1);				//Draw each pixel with its color value
	    glVertex2f(x1 + pixelSize, y1);
	    glVertex2f(x1 + pixelSize, y1 + pixelSize);
	    glVertex2f(x1, y1 + pixelSize);
	}
    }

    counter++;
    
    glEnd();
    glFlush();
}

void raytracer()
{
    int widthInPixels = (int)(WIDTH * PPU);
    int heightInPixels = (int)(HEIGHT * PPU);
    float pixelSize = 1.0/PPU;
    float halfPixelSize = pixelSize/2.0;
    float x1, y1, xc, yc, xaa, yaa;
    Vector eye(0., 0., 0.);

    for(int i = 0; i < widthInPixels; i++) { //Scan every "pixel"
	x1 = XMIN + i*pixelSize;
	xc = x1 + halfPixelSize;
	colours.push_back(vector<Color>());

	if ((i - 119) % 120 == 0) {
	    printf("%d%%\n", (int)((i / 1200.0f)*100) + 1);
	}

	for(int j = 0; j < heightInPixels; j++) {
	    y1 = YMIN + j*pixelSize;
	    yc = y1 + halfPixelSize;
	    Color col(0., 0., 0.);

	    for (int k = 0; k < AALEVEL; k++) {
		xaa = x1 + (2*k + 1)*halfPixelSize/AALEVEL;
		for (int l = 0; l < AALEVEL; l++) {
		    yaa = y1 + (2*l + 1)*halfPixelSize/AALEVEL;
		    Vector dir(xaa, yaa, -EDIST);	//direction of the primary ray
	    
		    dir.normalise();			//Normalise this direction
	    
		    col.combineColor(trace (eye, dir, 1), 1.0f/(AALEVEL*AALEVEL)); //Trace the primary ray and get the colour value
		}
	    }
	    colours.back().push_back(col);
	}
    }
}



void initialize()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);

    Sphere *sphere11 = new Sphere(Vector(-6, 0, -40), 8.0, Color::BLUE, false, false);
    Sphere *sphere21 = new Sphere(Vector(4, 5, -40), 3.0, Color::RED, false, false);
    Sphere *sphere31 = new Sphere(Vector(4, -5, -40), 3.0, Color::GREEN, true, false);
    Sphere *sphere12 = new Sphere(Vector(-6, 0, -50), 8.0, Color::RED, false, false);
    Sphere *sphere22 = new Sphere(Vector(4, 5, -50), 3.0, Color::GREEN, false, false);
    Sphere *sphere32 = new Sphere(Vector(4, -5, -50), 3.0, Color::BLUE, false, false);
    Sphere *sphere13 = new Sphere(Vector(-6, 0, -60), 8.0, Color::GRAY, true, false);
    Sphere *sphere14 = new Sphere(Vector(-18, 0, -40), 8.0, Color::GRAY, true, false);
    Sphere *sphere23 = new Sphere(Vector(4, 5, -60), 3.0, Color::BLUE, false, false);
    Sphere *sphere33 = new Sphere(Vector(4, -5, -60), 3.0, Color::RED, false, false);

    Sphere *sphereRef1 = new Sphere(Vector(4, 5, -30), 3.0, Color::GRAY, true, true);
    Sphere *sphereRef2 = new Sphere(Vector(4, -5, -30), 3.0, Color::GRAY, true, true);
    Sphere *sphereRef3 = new Sphere(Vector(-7, 0, -30), 4.0, Color::GRAY, true, true);

    // Plane *plane1 = new Plane(
    // 	Vector(-15, -8, -70), 
    // 	Vector(-15, -8, -10), 
    // 	Vector(15, -8, -10), 
    // 	Vector(15, -8, -70), 
    // 	Color::GRAY, true, false
    // );

    std::vector<std::vector<Color> > tex;
    tex.push_back(std::vector<Color>());
    tex.push_back(std::vector<Color>());
    tex.push_back(std::vector<Color>());
    tex.push_back(std::vector<Color>());

    tex[0].push_back(Color::RED);
    tex[0].push_back(Color::BLUE);
    tex[0].push_back(Color::GREEN);
    tex[0].push_back(Color::WHITE);

    tex[1].push_back(Color::WHITE);
    tex[1].push_back(Color::RED);
    tex[1].push_back(Color::BLUE);
    tex[1].push_back(Color::GREEN);

    tex[2].push_back(Color::GREEN);
    tex[2].push_back(Color::WHITE);
    tex[2].push_back(Color::RED);
    tex[2].push_back(Color::BLUE);

    tex[3].push_back(Color::BLUE);
    tex[3].push_back(Color::GREEN);
    tex[3].push_back(Color::WHITE);
    tex[3].push_back(Color::RED);

    Plane *plane1 = new TexturedPlane(
	Vector(-15, -8, -70),
	30, 60,
	false, false, tex
    );
    Plane *plane2 = new Plane(
	Vector(-15, 3, -70), 
	Vector(-15, -8, -70), 
	Vector(15, -8, -70), 
	Vector(15, 3, -70), 
	Color::RED, false, false
    );

    sceneObjects.push_back(sphere13);
    sceneObjects.push_back(sphere14);

    sceneObjects.push_back(sphereRef1);
    sceneObjects.push_back(sphereRef2);
    sceneObjects.push_back(sphereRef3);

    sceneObjects.push_back(sphere21);
    sceneObjects.push_back(sphere31);

    sceneObjects.push_back(sphere22);
    sceneObjects.push_back(sphere32);

    sceneObjects.push_back(sphere23);
    sceneObjects.push_back(sphere33);

    sceneObjects.push_back(plane1);
    sceneObjects.push_back(plane2);

    raytracer();
}


int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(1200,1200);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Raytracing");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
