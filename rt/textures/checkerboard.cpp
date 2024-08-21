#include <rt/textures/checkerboard.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
    : white(white), black(black)
{
    
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    int lu = floor(2 * coord.x);
    int lv = floor(2 * coord.y);
    int lw = floor(2 * coord.z);

    int parity = (lu + lv + lw) % 2;



    if (parity == 0) {
        return white;
    }
    else {
        return black;
    }
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    return RGBColor(.0f, .0f, .0f);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    return RGBColor(.0f, .0f, .0f);
}

}