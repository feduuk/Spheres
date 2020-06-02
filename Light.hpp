#pragma once

#include "Geometry.hpp"

class Light {
    Vec position; // позици€
    double energy; // энерги€ света
public:
    Light(Vec position, double energy);

    Vec GetDirection(Vec point) const;
    double GetEnergy() const; // получение €ркости
};

Light::Light(Vec position, double energy) {
    this->position = position;
    this->energy = energy;
}

// получение вектора света
Vec Light::GetDirection(Vec point) const {
    return (position - point).Normalized();
}

// получение €ркости
double Light::GetEnergy() const {
    return energy;
}