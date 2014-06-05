CFLAGS=-g -Ofast -DAALEVEL=1
RayTracer: RayTracer.o Color.o Object.o Vector.o Plane.o Sphere.o TexturedPlane.hpp
	g++ $(CFLAGS) Color.o RayTracer.o Object.o Vector.o Plane.o Sphere.o -lGL -lGLU -lglut -o RayTracer  

Color.o: Color.cpp Color.hpp
	g++ $(CFLAGS) -c Color.cpp -o Color.o   

Object.o: Object.cpp Object.hpp
	g++ $(CFLAGS) -c Object.cpp -o Object.o   

Sphere.o: Sphere.cpp Sphere.hpp Object.hpp
	g++ $(CFLAGS) -c Sphere.cpp -o Sphere.o   

Plane.o: Plane.cpp Plane.hpp Object.hpp
	g++ $(CFLAGS) -c Plane.cpp -o Plane.o   

Vector.o: Vector.cpp Vector.hpp
	g++ $(CFLAGS) -c Vector.cpp -o Vector.o   

RayTracer.o: RayTracer.cpp Vector.hpp Sphere.hpp Object.hpp Color.hpp
	g++ $(CFLAGS) -c RayTracer.cpp -o RayTracer.o   


clean:
	rm *.o RayTracer
