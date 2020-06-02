#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.0000001; // ��������� �����
const double INF = 10000000000000; // �������������

struct Vec {
    double x;
    double y;
    double z;

    Vec(); // ������� ������
    Vec(double x, double y, double z); // ������ �� ���������

    double Norm() const; // ��������� ����� �������
    double Dot(const Vec& vec) const; // ��������� ������������ ��������

    void Normalize(); // ������������ �������
    Vec Normalized() const; // ��������� ���������������� �������

    Vec operator+(const Vec& vec) const; // �������� ��������
    Vec operator-(const Vec& vec) const; // �������� ��������
    Vec operator*(const Vec& vec) const; // �������������� ���������
    Vec operator*(double a) const; // ��������� �� �����
    Vec operator/(double a) const; // ������� �� �����
};

class Ray {
    Vec origin; // ������ ����
    Vec direction; // ����������� ����

public:
    Ray(const Vec& origin, const Vec& direction);
    Vec GetOrigin() const; // ��������� ������ ����
    Vec GetDirection() const; // ��������� ����������� ����
    Vec GetPoint(double t) const; // ��������� �����
};

// ������� ������
Vec::Vec() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

// ������ �� ���������
Vec::Vec(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// ��������� ����� �������
double Vec::Norm() const {
    return sqrt(x * x + y * y + z * z);
}

// ��������� ������������ ��������
double Vec::Dot(const Vec& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

// ������������ �������
void Vec::Normalize() {
    double norm = Norm();

    if (norm < EPSILON)
        return;

    x /= norm;
    y /= norm;
    z /= norm;
}

// ��������� ���������������� �������
Vec Vec::Normalized() const {
    double norm = Norm();

    return norm < EPSILON ? Vec() : Vec(x / norm, y / norm, z / norm);
}

// �������� ��������
Vec Vec::operator+(const Vec& vec) const {
    return Vec(x + vec.x, y + vec.y, z + vec.z);
}

// �������� ��������
Vec Vec::operator-(const Vec& vec) const {
    return Vec(x - vec.x, y - vec.y, z - vec.z);
}

// �������������� ���������
Vec Vec::operator*(const Vec& vec) const {
    return Vec(x * vec.x, y * vec.y, z * vec.z);
}

// ��������� �� �����
Vec Vec::operator*(double a) const {
    return Vec(x * a, y * a, z * a);
}

// ������� �� �����
Vec Vec::operator/(double a) const {
    return Vec(x / a, y / a, z / a);
}

Ray::Ray(const Vec& origin, const Vec& direction) {
    this->origin = origin;
    this->direction = direction;
}

// ��������� ������ ����
Vec Ray::GetOrigin() const {
    return origin;
}

// ��������� ����������� ����
Vec Ray::GetDirection() const {
    return direction;
}

// ��������� �����
Vec Ray::GetPoint(double t) const {
    return origin + direction * t;
}
