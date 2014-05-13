Color.o: Color.cpp Color.h
	g++ -c Color.cpp -o Color.o

Object.o: Object.cpp Object.h
	g++ -c Object.cpp -o Object.o

Sphere.o: Sphere.cpp Sphere.h Object.h
	g++ -c Sphere.cpp -o Sphere.o

Vector.o: Vector.cpp Vector.h
	g++ -c Vector.cpp -o Vector.o

RayTracer.o: RayTracer.cpp Vector.h Sphere.h Object.h Color.h
	g++ -c RayTracer.cpp -o RayTracer.o

RayTracer: RayTracer.o Color.o Object.o Vector.o Sphere.o
	g++ RayTracer.o Color.o Object.o Vector.o Sphere.o -lGL -lGLU -lglut -o RayTracer

clean:
	rm *.o RayTracer
