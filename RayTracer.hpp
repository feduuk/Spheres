#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Picture.hpp"
#include "Sphere.hpp"
#include "Light.hpp"

using namespace std;

class RayTracer {
    vector<Sphere*> spheres;
    vector<Light> lights;

    Sphere* FindIntersection(const Ray& ray, double tmin, double tmax, double& t) const;
    Vec CastRay(const Ray& ray, double tmin, double tmax);
public:
    void AddSphere(Sphere* sphere);
    void AddLight(Light light);

    void Render(int width, int height, const char* path);
};

// ����� ���������� � ���� ���������
Sphere* RayTracer::FindIntersection(const Ray& ray, double tmin, double tmax, double& t) const {
    t = INF; // ������������, ��� ��� �����������
    Sphere* closest = nullptr;

    // ���������� �� ���� �������
    for (Sphere* sphere : spheres) {
        double ti = sphere->Intersect(ray);

        if (ti >= tmin && ti < tmax && ti < t) {
            t = ti; // ��������� ��������� ���������
            closest = sphere; // � ���������� ��������� ��������
        }
    }

    return closest;
}

// ����������� ����
Vec RayTracer::CastRay(const Ray& ray, double tmin, double tmax) {
    double t;
    Sphere* sphere = FindIntersection(ray, tmin, tmax, t); // ������� ��������� ������, � ������� ������������ ���

    // ���� ��� �� � ��� �� ������������
    if (sphere == nullptr)
        return Vec(0, 0, 0);

    Vec point = ray.GetPoint(t); // ������� ����� ����������� ���� � ��������
    Vec normal = sphere->GetNormal(point); // �������� ������� � ���� �����

    double diffuse = 0;

    // ���������� �� ���� ���������� ���������
    for (Light light : lights) {
        double energy = light.GetEnergy(); // ������� ���������
        Vec L = light.GetDirection(point); // ������ ��������� �����

        diffuse += std::max(0.0, L.Dot(normal));
    }

    return sphere->GetColor() * diffuse;
}

void RayTracer::AddSphere(Sphere* sphere) {
    spheres.push_back(sphere);
}

void RayTracer::AddLight(Light light) {
    lights.push_back(light);
}

// ����������� �����
void RayTracer::Render(int width, int height, const char* path) {
    double size = std::max(width, height);
    double ds = 0.5 / size;

    Picture picture(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double wx = x / size - 0.5;
            double wy = 0.5 - y / size;

            Vec D(wx, wy, 1);
            Ray ray(Vec(0, 0, 0), D.Normalized());

            Vec color = CastRay(ray, 0, INF);
            picture.SetPixel(x, y, color);
        }
    }

    picture.Save(path);
}
