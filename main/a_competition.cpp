
#include <core/image.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/textures/constant.h>
#include <rt/renderer.h>
#include <rt/integrators/recraytrace.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <chrono>
#include <rt/groups/bvh.h>
#include <rt/loaders/obj.h>
#include <rt/lights/directional.h>
#include <rt/lights/spotlight.h>
#include <core/transformation.h>
#include <rt/primmod/instance.h>
#include <rt/integrators/castingdist.h>

using namespace rt;

namespace {

    void renderKitchen1(int numSamples) {
        Image img(1920, 1080);
        World world;
        BVH* scene = new BVH();

        world.scene = scene;
        loadOBJ(scene, "models/", "kitchen.obj");
        scene->rebuildIndex();

        DOFPerspectiveCamera cam(Point(0, -15.0f, 1.0f), Vector(0, 1.5f, -0.10f), Vector(0, 0, 1), pi / 8, pi / 6, 6.4f, 0.05f);
        //PerspectiveCamera cam(Point(0, -15.0f, 1.0f), Vector(0.0f, 1.5f, -0.10f), Vector(0, 0, 1), pi / 8, pi / 6);


        Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
        ConstantTexture* lightsrctex = new ConstantTexture(RGBColor(18, 15, 10));
        Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
        Quad* light = new Quad(Point(0, -6.0f, 2.3), Vector(0.5, 0, 0), Vector(0, 0.5, 0), nullptr, lightsource);
        AreaLight als(light);
        world.light.push_back(&als);
        scene->add(light);

        lightsrctex = new ConstantTexture(RGBColor(RGBColor(16, 12, 8)));
        Material* lightsource2 = new LambertianMaterial(lightsrctex, blacktex);
        Quad* light2 = new Quad(Point(-2, -16.0f, 0), Vector(3, 1, 0), Vector(0, 0, 3), nullptr, lightsource2);
        AreaLight als2(light2);
        world.light.push_back(&als2);
        scene->add(light2);

        //point light
        //world.light.push_back(new PointLight(Point(.0f, -10.0f, 0), RGBColor::rep(50.f)));
        //world.light.push_back(new PointLight(Point(40 * 1, 159.99f * 1, 249.5f * 1), RGBColor(5000.0f * 1 * 1, 30000.0f * 1 * 1, 5000.0f * 1 * 1)));


        DirectionalLight dirl(Vector(0, 0, -1.0f).normalize(), RGBColor::rep(1));
        world.light.push_back(&dirl);

        RecursiveRayTracingIntegrator integrator(&world);

        Renderer engine(&cam, &integrator);
        if (numSamples > 1)
            engine.setSamples(numSamples);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        engine.renderThreading(img);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        img.writePNG("kitchen.png");
        std::cout << "Time difference (sec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << std::endl;
    }

    void renderKitchen2(int numSamples, int width, int height, int additional) {
        Image img(width, height);
        World world;
        BVH* scene = new BVH();

        world.scene = scene;
        loadOBJ(scene, "models/", "kitchen.obj");
        scene->rebuildIndex();

        DOFPerspectiveCamera cam(Point(0, -15.0f, 1.0f), Vector(0, 1.5f, -0.10f), Vector(0, 0, 1), 2 * pi / 16, 2 * pi / 9, 1.3f, 0.004f);
        //PerspectiveCamera cam(Point(0, -15.0f, 1.0f), Vector(0, 1.5f, -0.10f), Vector(0, 0, 1), 2 * pi / 16, 2 * pi / 9);

        float lightscale = 0.5;

        Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
        ConstantTexture* lightsrctex = new ConstantTexture(RGBColor(18 * lightscale, 15 * lightscale, 10 * lightscale));
        Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);
        Quad* light = new Quad(Point(0, -14.0f, 2.5f), Vector(2, 0, 0), Vector(0, 2, 0), nullptr, lightsource);
        AreaLight als(light);
        world.light.push_back(&als);
        //scene->add(light);

        lightsrctex = new ConstantTexture(RGBColor(RGBColor(16 * lightscale, 12 * lightscale, 8 * lightscale)));
        Material* lightsource2 = new LambertianMaterial(lightsrctex, blacktex);
        Quad* light2 = new Quad(Point(0, -16.0f, 1), Vector(1.5, 0, 0), Vector(0, -0.5, 1.5), nullptr, lightsource2);
        AreaLight als2(light2);
        world.light.push_back(&als2);
        //scene->add(light2);

        RecursiveRayTracingIntegrator integrator(&world);
        //RayCastingDistIntegrator integrator(&world, RGBColor::rep(.0f), 0, RGBColor::rep(.0f), 0);

        Renderer engine(&cam, &integrator);
        std::cout << "Prepare rendering with " << numSamples << " Samples in " << width << "x" << height << "." << std::endl;
        std::cout << "Loading samplemap5.png with max " << additional << " additional samples." << std::endl;
       
        engine.loadSampleMap("models/samplemap5.png", width, height, additional);
        if (numSamples > 1)
            engine.setSamples(numSamples);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        engine.renderThreading(img);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        img.writePNG("kitchen.png");
        std::cout << "Time difference (sec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << std::endl;
        std::cout << "Hopefully everything went fine! :)" << std::endl;
    }
}

void a_competition() {
    renderKitchen2(500, 1920, 1080, 2000);
}