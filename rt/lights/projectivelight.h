#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>
#include <core/julia.h>
#include <core/scalar.h>

namespace rt {

	class ProjectiveLight : public Light {
	public:
		Point position;
		RGBColor intensity;

		ProjectiveLight() {}
		ProjectiveLight(const Point& position, const RGBColor& intensity);
		virtual LightHit getLightHit(const Point& p) const;
		virtual RGBColor getIntensity(const LightHit& irr) const;

		float computeWeight(float fx, float fy, float r, const Point& c, float div) const;
		RGBColor computeColor(const LightHit& irr) const;

	};

}

#endif
