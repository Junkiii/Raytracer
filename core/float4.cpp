#include <core/float4.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w) 
    : x(x), y(y), z(z), w(w) {}

/**
* Creates a Float4 with w = 1.0f.
*/
Float4::Float4(const Point& p) 
    : x(p.x), y(p.y), z(p.z), w(1.0f) {}

/**
* Creates a Float4 with w = 0.0f.
*/
Float4::Float4(const Vector& vec) 
    : x(vec.x), y(vec.y), z(vec.z), w(0.0f) {}

/**
* Access Float4 values via indices.
* Returns -1.0f if the index is out of bounds.
*/
float& Float4::operator [] (int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    if (idx == 3) return w;
    float err = -1.0f;
    return err;
}

/**
* Access Float4 values via indices.
* Returns -1.0f if the index is out of bounds.
*/
float Float4::operator [] (int idx) const {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    if (idx == 3) return w;
    float err = -1.0f;
    return err;
}

Float4 Float4::operator + (const Float4& b) const {
    return Float4(x + b.x, y + b.y, z + b.z, w + b.w);
}

Float4 Float4::operator - (const Float4& b) const {
    return Float4(x - b.x, y - b.y, z - b.z, w - b.w);
}

Float4 Float4::operator * (const Float4& b) const {
    return Float4(x * b.x, y * b.y, z * b.z, w * b.w);
}

/**
* Dividing a Float4 with a Float4. 
* Checks for zero division. Return FLT_MAX and -FLT_MAX 
* if zero division performed.
* Uses fdiv(float num, float denom) in scalar.h
*/
Float4 Float4::operator / (const Float4& b) const {
    return Float4(fdiv(x, b.x), fdiv(y, b.y), fdiv(z, b.z), fdiv(w, b.w));
}

Float4 operator * (float scalar, const Float4& b) {
    return Float4(b.x * scalar, b.y * scalar, b.z * scalar, b.w * scalar);
}

Float4 operator * (const Float4& a, float scalar) {
    return Float4(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

/**
* Dividing a Float4 with a float.
* Checks for zero division. Return FLT_MAX and -FLT_MAX
* if zero division performed.
* Uses fdiv(float num, float denom) in scalar.h 
* (-DIFF-)
*/
Float4 operator / (const Float4& a, float scalar) {
    return Float4(fdiv(a.x, scalar), fdiv(a.y, scalar), fdiv(a.z, scalar), fdiv(a.w, scalar));
}

/**
* Computes the dot product of two Float4's.
*/
float dot(const Float4& a, const Float4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Float4 Float4::operator - () const {
    return Float4(-x, -y, -z, -w);
}

/**
* Checking for equality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Float4::operator == (const Float4& b) const {
    return (fequal(x, b.x) && fequal(y, b.y) && fequal(z, b.z) && fequal(w, b.w));
}

/**
* Checking for unequality component wise.
* Is using epsilon!
*/
bool Float4::operator != (const Float4& b) const {
    return !(*this == b);
}

/**
* Computes component-wise minimum.
*/
Float4 min(const Float4& a, const Float4& b) {
    return Float4(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z), fmin(a.w, b.w));
}

/**
* Computes component-wise maximum.
*/
Float4 max(const Float4& a, const Float4& b) {
    return Float4(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z), fmax(a.w, b.w));
}
}