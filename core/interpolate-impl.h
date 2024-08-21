#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    return xPoint * px1 + (1.0f - xPoint) * px0;
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    return aWeight * a + bWeight * b + (1.0f - aWeight - bWeight) * c;
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    T f_y0 = lerp(px0y0, px1y0, xWeight);
    T f_y1 = lerp(px0y1, px1y1, xWeight);

    return lerp(f_y0, f_y1, yWeight);
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    T f_1 = lerp2d(px0y0z0, px1y0z0, px0y1z0, px1y1z0, xPoint, yPoint);
    T f_2 = lerp2d(px0y0z1, px1y0z1, px0y1z1, px1y1z1, xPoint, yPoint);
    return lerp(f_1, f_2, zPoint);
}

}