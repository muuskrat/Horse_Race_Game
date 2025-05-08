#include "Vec2.h"
#include <cmath>

// Default constructor
Vec2::Vec2() : x(0.0f), y(0.0f) {}

// Parameterized constructor
Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

// Destructor
Vec2::~Vec2() {}

// Copy constructor
Vec2::Vec2(const Vec2& other) : x(other.x), y(other.y) {}

// Assignment operator
Vec2& Vec2::operator=(const Vec2& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

// Addition operator
Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

// Subtraction operator
Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

// Multiplication operator (scalar)
Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

// Division operator (scalar)
Vec2 Vec2::operator/(float scalar) const {
    if (scalar == 0.0f) return Vec2(); // Avoid division by zero
    return Vec2(x / scalar, y / scalar);
}

// Compound assignment operators
Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(float scalar) {
    if (scalar == 0.0f) return *this; // Avoid division by zero
    x /= scalar;
    y /= scalar;
    return *this;
}

// Magnitude (length) of the vector
float Vec2::magnitude() const {
    return sqrt(x * x + y * y);
}

// Normalize the vector (make it unit length)
void Vec2::normalize() {
    float mag = magnitude();
    if (mag != 0.0f) {
        x /= mag;
        y /= mag;
    }
}

// Dot product of two vectors
float Vec2::dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}

// Cross product of two vectors (for 2D, this returns a scalar)
float Vec2::cross(const Vec2& other) const {
    return x * other.y - y * other.x;
}
