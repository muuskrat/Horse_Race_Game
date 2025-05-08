#ifndef VEC2_H
#define VEC2_H

class Vec2 {
public:
    float x;
    float y;

    // Constructors
    Vec2(); // Default constructor
    Vec2(float _x, float _y); // Parameterized constructor

    // Destructor
    ~Vec2();

    // Copy constructor
    Vec2(const Vec2& other);

    // Assignment operator
    Vec2& operator=(const Vec2& other);

    // Addition operator
    Vec2 operator+(const Vec2& other) const;

    // Subtraction operator
    Vec2 operator-(const Vec2& other) const;

    // Multiplication operator (scalar)
    Vec2 operator*(float scalar) const;

    // Division operator (scalar)
    Vec2 operator/(float scalar) const;

    // Compound assignment operators
    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(float scalar);
    Vec2& operator/=(float scalar);

    // Magnitude (length) of the vector
    float magnitude() const;

    // Normalize the vector (make it unit length)
    void normalize();

    // Dot product of two vectors
    float dot(const Vec2& other) const;

    // Cross product of two vectors (for 2D, this returns a scalar)
    float cross(const Vec2& other) const;
};

#endif // VEC2_H
