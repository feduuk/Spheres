#include <iostream>
#include "RayTracer.hpp"

int main() {
    RayTracer tracer;
    tracer.AddSphere(new Sphere(Vec(-1.5, 0, 6), 1, Vec(1, 0, 0)));
    tracer.AddSphere(new Sphere(Vec(1, 0.5, 5), 1.5, Vec(0, 0, 1)));

    tracer.AddLight(Light(Vec(0, 2, 2), 1));

    tracer.Render(1024, 1024, "out.bmp");
  
}