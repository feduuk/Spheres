#pragma once

#include <iostream>
#include "Geometry.hpp"

class Sphere {
    Vec center; // �����
    double radius; // ������    
    Vec color; // ����

public:
    Sphere(Vec center, double radius, Vec color);

    double Intersect(const Ray& ray) const; // ����������� � �����
    Vec GetNormal(const Vec& point) const; // ��������� ������� � �����
    Vec GetColor() const; // ��������� �����
};

Sphere::Sphere(Vec center, double radius, Vec color) {
    this->center = center;
    this->radius = radius;
    this->color = color;
}

// ����������� ����� � �����
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

// ��������� ������� � �����
Vec Sphere::GetNormal(const Vec& point) const {
    return (point - center) * (1.0 / radius);
}

// ��������� �����
Vec Sphere::GetColor() const {
    return color;
}