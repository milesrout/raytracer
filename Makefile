CFLAGS=-g -O3 -DAALEVEL=1 -DADAPTIVE_THRESHOLD=0.1 -DADAPTIVE_COUNTER_THRESHOLD=3
RayTracer: RayTracer.o Color.o Object.o Vector.o Plane.o Sphere.o Cylinder.o
	g++ $(CFLAGS) Color.o RayTracer.o Object.o Vector.o Plane.o Sphere.o Cylinder.o -lGL -lGLU -lglut -o RayTracer  

Color.o: Color.cpp Color.hpp
	g++ $(CFLAGS) -c Color.cpp -o Color.o   

Object.o: Object.cpp Object.hpp
	g++ $(CFLAGS) -c Object.cpp -o Object.o   

Sphere.o: Sphere.cpp Sphere.hpp Object.hpp
	g++ $(CFLAGS) -c Sphere.cpp -o Sphere.o   

Cylinder.o: Cylinder.cpp Cylinder.hpp Object.hpp
	g++ $(CFLAGS) -c Cylinder.cpp -o Cylinder.o   

Plane.o: Plane.cpp Plane.hpp Object.hpp
	g++ $(CFLAGS) -c Plane.cpp -o Plane.o   

Vector.o: Vector.cpp Vector.hpp
	g++ $(CFLAGS) -c Vector.cpp -o Vector.o   

RayTracer.o: RayTracer.cpp Vector.hpp Sphere.hpp Object.hpp Color.hpp TexturedPlane.hpp
	g++ $(CFLAGS) -c RayTracer.cpp -o RayTracer.o   


clean:
	rm *.o RayTracer
