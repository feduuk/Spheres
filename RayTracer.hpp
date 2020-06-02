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

// поиск ближайшего к лучу примитива
Sphere* RayTracer::FindIntersection(const Ray& ray, double tmin, double tmax, double& t) const {
    t = INF; // предполагаем, что нет пересечения
    Sphere* closest = nullptr;

    // проходимся по всем фигурам
    for (Sphere* sphere : spheres) {
        double ti = sphere->Intersect(ray);

        if (ti >= tmin && ti < tmax && ti < t) {
            t = ti; // обновляем ближайшее расстоние
            closest = sphere; // и запоминаем ближайший примитив
        }
    }

    return closest;
}

// трассировка луча
Vec RayTracer::CastRay(const Ray& ray, double tmin, double tmax) {
    double t;
    Sphere* sphere = FindIntersection(ray, tmin, tmax, t); // находим ближайший объект, с которым пересекается луч

    // если луч ни с чем не пересекается
    if (sphere == nullptr)
        return Vec(0, 0, 0);

    Vec point = ray.GetPoint(t); // находим точку перемесения луча с объектом
    Vec normal = sphere->GetNormal(point); // получаем нормаль в этой точке

    double diffuse = 0;

    // проходимся по всем источникам освещения
    for (Light light : lights) {
        double energy = light.GetEnergy(); // энергия источника
        Vec L = light.GetDirection(point); // вектор источника света

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

// трассировка лучей
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
