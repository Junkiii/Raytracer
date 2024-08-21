#include <cmath>
#include <core/scalar.h>

namespace rt {

float fractional( float f ) {
    float intpart;
    return modff(f, &intpart);
}

float absfractional(float f) {
    float fr = fractional(f);
    if (fr>=0) return fr;
    fr += 1.0f;
    if (fr >= 1.0f) //can happed due to epsilon errors
        return 0.0f;
    return fr;
}

bool fequal(float f1, float f2) {
    float diff = fabs(f1 - f2);
    f1 = fabs(f1);
    f2 = fabs(f2);
    float l = (f2 > f1) ? f2 : f1;
    if (diff <= l * epsilon) return true;
    return false;
}

/**
* Clamps a floating point number between 0.0f and 1.0f.
*/
float fbound(float f) {
    if (f < 0) return 0.0f;
    else if (f > 1)return 1.0f;
    else return f;
}

/**
* Floating point division with zero check.
* Return -FLT_MAX or FLT_MAX if zero division is performed.
*/
float fdiv(float num, float denom) {
    /*
    if (fequal(denom, 0.0f)) {
        if (num > 0) return FLT_MAX;
        if (num < 0) return -FLT_MAX;
    }
    */
    return num / denom;
}

}
