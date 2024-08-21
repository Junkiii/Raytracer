#include <core/matrix.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) 
    : r1(r1), r2(r2), r3(r3), r4(r4) {}

/**
* Access Matrix rows via indices.
* Returns row1 as standard value.
*/
Float4& Matrix::operator[](int idx) {
    if (idx == 0) return r1;
    if (idx == 1) return r2;
    if (idx == 2) return r3;
    if (idx == 3) return r4;
    return r1;
}

/**
* Access Matrix rows via indices.
* Returns row1 as standard value.
*/
Float4 Matrix::operator[](int idx) const {
    if (idx == 0) return r1;
    if (idx == 1) return r2;
    if (idx == 2) return r3;
    if (idx == 3) return r4;
    return r1;
}

Matrix Matrix::operator+(const Matrix& b) const {
    return Matrix(r1 + b.r1, r2 + b.r2, r3 + b.r3, r4 + b.r4);
}

Matrix Matrix::operator-(const Matrix& b) const {
    return Matrix(r1 - b.r1, r2 - b.r2, r3 - b.r3, r4 - b.r4);
}

/**
* Transpose the matrix.
*/
Matrix Matrix::transpose() const {
    Float4 row1(r1.x, r2.x, r3.x, r4.x);
    Float4 row2(r1.y, r2.y, r3.y, r4.y);
    Float4 row3(r1.z, r2.z, r3.z, r4.z);
    Float4 row4(r1.w, r2.w, r3.w, r4.w);
    return Matrix(row1, row2, row3, row4);
}

/**
* Invert the matrix.
*/
Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

/**
* Checking for equality component wise.
* Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
*/
bool Matrix::operator==(const Matrix& b) const {
    return (r1 == b.r1 && r2 == b.r2 && r3 == b.r3 && r4 == b.r4);
}

/**
* Checking for unequality component wise.
* Is using epsilon!
*/
bool Matrix::operator!=(const Matrix& b) const {
    return !(*this == b);
}

/**
* Matrix multiplication.
*/
Matrix product(const Matrix& a, const Matrix& b) {
    Matrix b_t = b.transpose();
    Float4 row1(dot(a.r1, b_t.r1), dot(a.r1, b_t.r2), dot(a.r1, b_t.r3), dot(a.r1, b_t.r4));
    Float4 row2(dot(a.r2, b_t.r1), dot(a.r2, b_t.r2), dot(a.r2, b_t.r3), dot(a.r2, b_t.r4));
    Float4 row3(dot(a.r3, b_t.r1), dot(a.r3, b_t.r2), dot(a.r3, b_t.r3), dot(a.r3, b_t.r4));
    Float4 row4(dot(a.r4, b_t.r1), dot(a.r4, b_t.r2), dot(a.r4, b_t.r3), dot(a.r4, b_t.r4));
    return Matrix(row1, row2, row3, row4);
}

Matrix operator*(const Matrix& a, float scalar) {
    return Matrix(a.r1 * scalar, a.r2 * scalar, a.r3 * scalar, a.r4 * scalar);
}

Matrix operator*(float scalar, const Matrix& a) {
    return a * scalar;
}

Float4 Matrix::operator*(const Float4& b) const {
    return Float4(dot(r1, b), dot(r2, b), dot(r3, b), dot(r4, b));
}

/**
* Multiplication with a vector. 
* Uses multiplication with a Float4.
*/
Vector Matrix::operator*(const Vector& b) const {
    Float4 bf(b);
    Float4 res = *this * bf;
    return Vector(res);
}

/**
* Multiplication with a point.
* Uses multiplication with a Float4.
*/
Point Matrix::operator*(const Point& b) const {
    Float4 bf(b);
    Float4 res = *this * bf;
    return Point(res);
}

float Matrix::det() const {
    return r1.x * det3x3(r2.y, r2.z, r2.w, r3.y, r3.z, r3.w, r4.y, r4.z, r4.w) - r1.y * det3x3(r2.x, r2.z, r2.w, r3.x, r3.z, r3.w, r4.x, r4.z, r4.w) + r1.z * det3x3(r2.x, r2.y, r2.w, r3.x, r3.y, r3.w, r4.x, r4.y, r4.w) - r1.w * det3x3(r2.x, r2.y, r2.z, r3.x, r3.y, r3.z, r4.x, r4.y, r4.z);
}

float Matrix::det3x3(float f, float g, float h, float j, float k, float l, float n, float o, float p) const {
    return f * k * p + g * l * n + h * j * o - h * k * n - f * l * o - g * j * p;
}

Matrix Matrix::zero() {
    Float4 row1(0, 0, 0, 0);
    Float4 row2(0, 0, 0, 0);
    Float4 row3(0, 0, 0, 0);
    Float4 row4(0, 0, 0, 0);
    return Matrix(row1, row2, row3, row4);
}

Matrix Matrix::identity() {
    Float4 row1(1, 0, 0, 0);
    Float4 row2(0, 1, 0, 0);
    Float4 row3(0, 0, 1, 0);
    Float4 row4(0, 0, 0, 1);
    return Matrix(row1, row2, row3, row4);
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    return Matrix(Float4(e1.x, e2.x, e3.x, 0.0f), Float4(e1.y, e2.y, e3.y, 0.0f), Float4(e1.z, e2.z, e3.z, 0.0f), Float4(0.0f, 0.0f, 0.0f, 1.0f));
}

}