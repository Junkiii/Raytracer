#include <core/color.h>

namespace rt {

    /**
    * Constructor for RGBColor.
    * Takes Float4 and sets the rgb values to x,y,z of Float4.
    * Ignores the w values of Float4
    */
    RGBColor::RGBColor(const Float4& f4)
        : r(f4.x), g(f4.y), b(f4.z) {}

    RGBColor RGBColor::operator + (const RGBColor& c) const {
        return RGBColor(r + c.r, g + c.g, b + c.b);
    }

    RGBColor RGBColor::operator - (const RGBColor& c) const {
        return RGBColor(r - c.r, g - c.g, b - c.b);
    }

    RGBColor RGBColor::operator * (const RGBColor& c) const {
        return RGBColor(r * c.r, g * c.g, b * c.b);
    }

    /**
    * Checking for equality component wise.
    * Is using epsilon! (Uses fequal(float a, float b) in scalar.h)
    */
    bool RGBColor::operator == (const RGBColor& c) const {
        return (fequal(r, c.r) && fequal(g, c.g) && fequal(b, c.b));
    }

    /**
    * Checking for unequality component wise.
    * Is using epsilon!
    */
    bool RGBColor::operator != (const RGBColor& b) const {
        return !(*this == b);
    }

    /**
    * Clamp the RGBColor between 0 and 1.
    * Uses fbound(float f) in scalar.h
    */
    RGBColor RGBColor::clamp() const {
        return RGBColor(fbound(r), fbound(g), fbound(b));
    }

    RGBColor RGBColor::gamma(float gam) const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    float RGBColor::luminance() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    RGBColor operator * (float scalar, const RGBColor& c) {
        return RGBColor(scalar * c.r, scalar * c.g, scalar * c.b);
    }

    RGBColor operator * (const RGBColor& c, float scalar) {
        return scalar * c;
    }

    /**
    * RGBColor / scalar
    * This function is NOT checking for division with zero.
    */
    RGBColor operator / (const RGBColor& c, float scalar) {
        return RGBColor(c.r / scalar, c.g / scalar, c.b / scalar);
    }
}
