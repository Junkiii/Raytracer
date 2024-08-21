#ifndef CG1RAYTRACER_TRANSFORMATION_HEADER
#define CG1RAYTRACER_TRANSFORMATION_HEADER

#include <core/matrix.h>
#include <core/vector.h>
#include <core/scalar.h>

/*
* Used for calculating transformation matrices.
*/

namespace rt {

	Matrix rotation(const Vector& axis, float angle);

	Matrix translation(const Vector& t);

	Matrix scaling(float f);

	Matrix scaling(const Vector& s);

}

#endif