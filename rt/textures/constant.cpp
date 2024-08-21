#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    color = RGBColor(.0f, .0f, .0f);
}

ConstantTexture::ConstantTexture(const RGBColor& color)
    : color(color)
{
    
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    return color;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    // The derivative of a constant function is zero
    return RGBColor(.0f, .0f, .0f);
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    // The derivative of a constant function is zero
    return RGBColor(.0f, .0f, .0f);
}

}