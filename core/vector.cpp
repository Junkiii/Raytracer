#include <core/vector.h>

namespace rt {

Vector::Vector(float x, float y, float z)
    : x(x), y(y), z(z) {}

Vector::Vector(const Float4& f4)
    : x(f4.x), y(f4.y), z(f4.z)
{
    // TODO: Check this. ignore w in vectors? (makes no difference in direction)
}

Vector Vector::operator + (const Vector& b) const {
    return Vector(x + b.x, y + b.y, z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
}

Vector Vector::operator - () const {
    return Vector(-x, -y, -z);
}

/**
* Normalizing the vector.
*/
Vector Vector::normalize() const {
    float len = this->length();
    return *this / len;
}

Vector operator * (float scalar, const Vector& b) {
    return Vector(scalar * b.x, scalar * b.y, scalar * b.z);
}

Vector operator * (const Vector& a, float scalar) {
    return Vector(scalar * a.x, scalar * a.y, scalar * a.z);
}

/**
* Dividing a vector with a scalar.
* Is NOT checking for zero division.
*/
Vector operator / (const Vector& a, float scalar) {
    return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
}

Vector cross(const Vector& a, const Vector& b) {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float dot(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
* Calculates the squared length. Efficient!
* (-DIFF-)
*/
float Vector::lensqr() const {
    return sqr(x) + sqr(y) + sqr(z);
}

/**
* Calculates the length of a the vector.
* Uses lensqr(). Inefficient!
*/
float Vector::length() const {
    return sqrt(this->lensqr());
}

/**
* Checking for equality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Vector::operator == (const Vector& b) const {
    return (fequal(x, b.x) && fequal(y, b.y) && fequal(z, b.z));
}

/**
* Checking for unequality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Vector::operator != (const Vector& b) const {
    return !(*this == b);
}

/**
* Computes component-wise minimum.
*/
Vector min(const Vector& a, const Vector& b) {
    return Vector(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
}

/**
* Computes component-wise maximum.
*/
Vector max(const Vector& a, const Vector& b) {
    return Vector(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));
}

Point operator + (const Point& a, const Vector& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator + (const Vector& a, const Point& b) {
    return b + a;
}

Point operator - (const Point& a, const Vector& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
* I don't know what to do here.
*/
Point operator * (const Float4& scale, const Point& p) {
    NOT_IMPLEMENTED;
}

/**
* Component-wise division of two vectors.
*/
Vector Vector::operator / (const Vector& b) const {
    return Vector(fdiv(x, b.x), fdiv(y, b.y), fdiv(z, b.z));
}

/**
* Returns the index of the largest component of the vector.
*/
int Vector::maxComp() const {
    if (x > y) {
        if (x > z) return 0;
        else return 2;
    }
    else {
        if (y > z) return 1;
        else return 2;
    }
}

/**
* Return the index of the smallest component of the vector.
*/
int Vector::minComp() const {
    if (x < y) {
        if (x < z) return 0;
        else return 2;
    }
    else {
        if (y < z) return 1;
        else return 2;
    }
}

/**
* Return the index of the smallest absolute component of the vector.
*/
int Vector::minCompAbs() const {
    float x_abs = fabs(x);
    float y_abs = fabs(y);
    float z_abs = fabs(z);
    if (x_abs < y_abs) {
        if (x_abs < z_abs) return 0;
        else return 2;
    }
    else {
        if (y_abs < z_abs) return 1;
        else return 2;
    }
}

/**
* Access Vector components via indices.
* Returns -1.0f if the index is out of bounds.
*/
float& Vector::operator[] (int index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    float err = -1.0f;
    return err;
}

/**
* Access Vector components via indices.
* Returns -1.0f if the index is out of bounds.
*/
float Vector::operator[] (int index) const{
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    float err = -1.0f;
    return err;
}

}
