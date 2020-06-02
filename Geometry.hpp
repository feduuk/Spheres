#pragma once

#include <iostream>
#include <cmath>

const double EPSILON = 0.0000001; // маленькое число
const double INF = 10000000000000; // бесконечность

struct Vec {
    double x;
    double y;
    double z;

    Vec(); // нулевой вектор
    Vec(double x, double y, double z); // вектор из координат

    double Norm() const; // получение нормы вектора
    double Dot(const Vec& vec) const; // скалярное произведение векторов

    void Normalize(); // нормализация вектора
    Vec Normalized() const; // получение нормализованного вектора

    Vec operator+(const Vec& vec) const; // сложение векторов
    Vec operator-(const Vec& vec) const; // разность векторов
    Vec operator*(const Vec& vec) const; // покоординатное умножение
    Vec operator*(double a) const; // умножение на число
    Vec operator/(double a) const; // деление на число
};

class Ray {
    Vec origin; // начало луча
    Vec direction; // направление луча

public:
    Ray(const Vec& origin, const Vec& direction);
    Vec GetOrigin() const; // получение начала луча
    Vec GetDirection() const; // получение направления луча
    Vec GetPoint(double t) const; // получение точки
};

// нулевой вектор
Vec::Vec() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

// вектор из координат
Vec::Vec(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// получение нормы вектора
double Vec::Norm() const {
    return sqrt(x * x + y * y + z * z);
}

// скалярное произведение векторов
double Vec::Dot(const Vec& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

// нормализация вектора
void Vec::Normalize() {
    double norm = Norm();

    if (norm < EPSILON)
        return;

    x /= norm;
    y /= norm;
    z /= norm;
}

// получение нормализованного вектора
Vec Vec::Normalized() const {
    double norm = Norm();

    return norm < EPSILON ? Vec() : Vec(x / norm, y / norm, z / norm);
}

// сложение векторов
Vec Vec::operator+(const Vec& vec) const {
    return Vec(x + vec.x, y + vec.y, z + vec.z);
}

// разность векторов
Vec Vec::operator-(const Vec& vec) const {
    return Vec(x - vec.x, y - vec.y, z - vec.z);
}

// покоординатное умножение
Vec Vec::operator*(const Vec& vec) const {
    return Vec(x * vec.x, y * vec.y, z * vec.z);
}

// умножение на число
Vec Vec::operator*(double a) const {
    return Vec(x * a, y * a, z * a);
}

// деление на число
Vec Vec::operator/(double a) const {
    return Vec(x / a, y / a, z / a);
}

Ray::Ray(const Vec& origin, const Vec& direction) {
    this->origin = origin;
    this->direction = direction;
}

// получение начала луча
Vec Ray::GetOrigin() const {
    return origin;
}

// получение направления луча
Vec Ray::GetDirection() const {
    return direction;
}

// получение точки
Vec Ray::GetPoint(double t) const {
    return origin + direction * t;
}
