#include <rt/textures/perlin.h>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
    : white(white), black(black)
{
    
}

rt::RGBColor PerlinTexture::getColor(const Point& coord) {

    float value = 0;

    float ampsum = .0f;

    for (std::pair<float, float> p : octaves) {
        ampsum = ampsum + p.second;
        float noise1 = fabs(p.second * noise(floor(coord.x * p.first), floor(coord.y * p.first), floor(coord.z * p.first)));
        float noise2 = fabs(p.second * noise(floor(coord.x * p.first), floor(coord.y * p.first), ceil(coord.z * p.first)));
        float noise3 = fabs(p.second * noise(floor(coord.x * p.first), ceil(coord.y * p.first), floor(coord.z * p.first)));
        float noise4 = fabs(p.second * noise(floor(coord.x * p.first), ceil(coord.y * p.first), ceil(coord.z * p.first)));
        float noise5 = fabs(p.second * noise(ceil(coord.x * p.first), floor(coord.y * p.first), floor(coord.z * p.first)));
        float noise6 = fabs(p.second * noise(ceil(coord.x * p.first), floor(coord.y * p.first), ceil(coord.z * p.first)));
        float noise7 = fabs(p.second * noise(ceil(coord.x * p.first), ceil(coord.y * p.first), floor(coord.z * p.first)));
        float noise8 = fabs(p.second * noise(ceil(coord.x * p.first), ceil(coord.y * p.first), ceil(coord.z * p.first)));
        
        float noise_ = lerp3d(noise1, noise5, noise3, noise7, noise2, noise6, noise4, noise8, absfractional(coord.x * p.first), absfractional(coord.y * p.first), absfractional(coord.z * p.first));
        value = value + noise_;
    }

    value = value / ampsum;

    return lerp(black, white, value);
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    return RGBColor(.0f, .0f, .0f);
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    return RGBColor(.0f, .0f, .0f);
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    octaves.push_back({ frequency , amplitude });
}

}