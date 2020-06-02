#pragma once

#include <iostream>
#include "Geometry.hpp"

class Sphere {
    Vec center; // центр
    double radius; // радиус    
    Vec color; // цвет

public:
    Sphere(Vec center, double radius, Vec color);

    double Intersect(const Ray& ray) const; // пересечение с лучём
    Vec GetNormal(const Vec& point) const; // получение нормали в точке
    Vec GetColor() const; // получение цвета
};

Sphere::Sphere(Vec center, double radius, Vec color) {
    this->center = center;
    this->radius = radius;
    this->color = color;
}

// пересечение сферы с лучём
double Sphere::Intersect(const Ray& ray) const {
    Vec oc = ray.GetOrigin() - center;

    double k = -oc.Dot(ray.GetDirection());
    double d = k * k - oc.Dot(oc) + radius * radius;

    if (d < EPSILON)
        return INF;

    d = sqrt(d);

    double t = k - d;

    if (t < EPSILON)
        t = k + d;

    return t;
}

// получение нормали в точке
Vec Sphere::GetNormal(const Vec& point) const {
    return (point - center) * (1.0 / radius);
}

// получение цвета
Vec Sphere::GetColor() const {
    return color;
}