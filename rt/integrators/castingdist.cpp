#include <rt/integrators/castingdist.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world), nearColor(nearColor), nearDist(nearDist), farColor(farColor), farDist(farDist)
{
    /* TODO */
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
	Intersection intersection = world->scene->intersect(ray);
	if (intersection) {
		//float cosinedot = (-dot(ray.d, intersection.normal())) / ray.d.length();
		//RGBColor newcolor = (farColor - nearColor) * fbound((intersection.distance - nearDist)  / (farDist - nearDist)) + nearColor;
		//return (cosinedot * newcolor);
		Vector n = intersection.normal() * 0.5 + Vector::rep(0.5f);
		return RGBColor(n.x, n.y, n.z);
		
		{

		};
	}
	return RGBColor(.0f, .0f, .0f);
}

}
