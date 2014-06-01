RayTracer: RayTracer.o Color.o Object.o Vector.o Plane.o Sphere.o
	g++ -g Color.o RayTracer.o Object.o Vector.o Plane.o Sphere.o -lGL -lGLU -lglut -o RayTracer -pg -O0

Color.o: Color.cpp Color.hpp
	g++ -g -c Color.cpp -o Color.o -pg -O0 

Object.o: Object.cpp Object.hpp
	g++ -g -c Object.cpp -o Object.o -pg -O0 

Sphere.o: Sphere.cpp Sphere.hpp Object.hpp
	g++ -g -c Sphere.cpp -o Sphere.o -pg -O0 

Plane.o: Plane.cpp Plane.hpp Object.hpp
	g++ -g -c Plane.cpp -o Plane.o -pg -O0 

Vector.o: Vector.cpp Vector.hpp
	g++ -g -c Vector.cpp -o Vector.o -pg -O0 

RayTracer.o: RayTracer.cpp Vector.hpp Sphere.hpp Object.hpp Color.hpp
	g++ -g -c RayTracer.cpp -o RayTracer.o -pg -O0 


clean:
	rm *.o RayTracer
