#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/materials/glass.h>

namespace rt {

class RecursiveRayTracingIntegrator : public Integrator {
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
    RGBColor getRadianceWrapper(const Ray& ray, int counter) const;
    
private:
    RGBColor normalGetRadiance(const Ray& ray, Intersection& intersection) const;
    int depth_max = 6;
    int offset_scale = 1000;
};

}

#endif