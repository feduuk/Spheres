#pragma once

#include "Geometry.hpp"

class Light {
    Vec position; // �������
    double energy; // ������� �����
public:
    Light(Vec position, double energy);

    Vec GetDirection(Vec point) const;
    double GetEnergy() const; // ��������� �������
};

Light::Light(Vec position, double energy) {
    this->position = position;
    this->energy = energy;
}

// ��������� ������� �����
Vec Light::GetDirection(Vec point) const {
    return (position - point).Normalized();
}

// ��������� �������
double Light::GetEnergy() const {
    return energy;
}