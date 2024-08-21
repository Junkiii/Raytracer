#include <rt/integrators/casting.h>




namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		float grayvalue = (-dot(ray.d, intersection.normal()));
		return RGBColor(grayvalue, grayvalue, grayvalue);
	}
	return RGBColor(.0f, .0f, .0f);
}

}
