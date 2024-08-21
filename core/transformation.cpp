#include <core/transformation.h>

namespace rt {

    /**
    * Returns a rotation matrix for the given angle
    * and the given axis.
    */
    Matrix rotation(const Vector& axis, float angle) {
        Vector r = axis/*.normalize()*/;
        int min_r = r.minCompAbs();
        Vector s_;
        if (min_r == 0) s_ = Vector(0, -r.z, r.y);
        else if (min_r == 1) s_ = Vector(-r.z, 0, r.x);
        else s_ = Vector(-r.y, r.x, 0);
        s_ = s_.normalize();
        Vector t = cross(r, s_);

        Matrix M = Matrix::identity();
        M.r1.x = r.x;
        M.r1.y = s_.x;
        M.r1.z = t.x;

        M.r2.x = r.y;
        M.r2.y = s_.y;
        M.r2.z = t.y;

        M.r3.x = r.z;
        M.r3.y = s_.z;
        M.r3.z = t.z;

        Matrix R = Matrix::identity();
        R.r2.y = cos(angle);
        R.r2.z = -sin(angle);
        R.r3.y = sin(angle);
        R.r3.z = cos(angle);

        return product(product(M, R), M.transpose());
    }

    /**
    * Returns a translation matrix for the given vector.
    */
    Matrix translation(const Vector& t) {
        Matrix temp = Matrix::identity();
        temp.r1.w = t.x;
        temp.r2.w = t.y;
        temp.r3.w = t.z;
        return temp;
    }

    /**
    * Returns a scaling matrix for the scale f.
    */
    Matrix scaling(float f) {
        Matrix temp = Matrix::identity();
        temp = temp * f;
        temp.r4.w = 1;
        return temp;
    }

    /**
    * Returns a scaling matrix for the scaling 
    * vector s;
    */
    Matrix scaling(const Vector& s) {
        Matrix temp = Matrix::identity();
        temp.r1.x = s.x;
        temp.r2.y = s.y;
        temp.r3.z = s.z;
        return temp;
    }

}
