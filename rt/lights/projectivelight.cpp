#include <rt/lights/projectivelight.h>

#include <core/vector.h>

namespace rt {

    ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity)
        : position(position), intensity(intensity)
    {

    }

    LightHit ProjectiveLight::getLightHit(const Point& p) const {
        LightHit temp;
        temp.direction = position - p;
        temp.distance = temp.direction.length();
        return temp;
    }

    RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
        RGBColor temp = computeColor(irr) * intensity / (irr.distance * irr.distance);
        return temp;
    }

    float ProjectiveLight::computeWeight(float fx, float fy, float r, const Point& c, float div) const {
        Point v(fx, fy, r);
        int numIter = julia(v, c);
        return numIter / (numIter + div);
    }

    RGBColor ProjectiveLight::computeColor(const LightHit& irr) const {
        //float theta = acos(irr.direction.z / irr.distance) / pi * 2;
        //float phi = atan(irr.direction.y / irr.direction.x) / pi;
        Vector d = irr.direction.normalize();
        float theta = asin(d.z) / pi * 2;
        float phi = atan2(d.y, d.x) / pi;
        float ofx = absfractional((position.x + 1.0f) / 2.0f) * 2.0f - 1.0f;
        float ofy = absfractional((position.y + 1.0f) / 2.0f) * 2.0f - 1.0f;
        RGBColor color = RGBColor::rep(0.0f);
        //color = color + computeWeight(phi, theta, irr.distance/100, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
        //color = color + computeWeight(phi, theta, irr.distance/100, Point(-0.6f, 0.2f, 0.0f), 64.0f) * 0.2f * RGBColor(0.5f, 0.5f, -0.2f);
        //color = color + computeWeight(ofy, ofx, irr.distance/100, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
        color = color + computeWeight(phi, theta, irr.distance / 100, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
        color = color + computeWeight(phi, theta, irr.distance / 100, Point(-0.6f, 0.2f, 0.0f), 64.0f) * 0.2f * RGBColor(0.5f, 0.5f, -0.2f);
        color = color + computeWeight(ofy, ofx, irr.distance / 100, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
        color = RGBColor::rep(1.0f) - color;
        return color;
    }

}
