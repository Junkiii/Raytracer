
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>

#include <rt/groups/simplegroup.h>
#include <rt/solids/infiniteplane.h>
#include <rt/lights/pointlight.h>

// my debug includes
#include <chrono>

using namespace rt;

void a_indexing() {
    Image img(800, 600); // origin 800x600

    BVH* scene = new BVH();
    //SimpleGroup* scene = new SimpleGroup();
    
    //scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    //scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    //scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

    //scene->add(new InfinitePlane(Point(0, 0, 0), Vector(0, 1, 0), nullptr, nullptr));
    
    loadOBJ(scene, "models/", "kitchen.obj");
  
    std::cout << "Begin indexing..." << std::endl;
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
	scene->rebuildIndex();
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "Indexing time:" << std::endl;
    std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count()) / 1000000.0 << "[s]" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[mus]" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds> (end1 - begin1).count() << "[ns]" << std::endl;
    std::cout << "Finished indexing!" << std::endl;

    World world;
    world.scene = scene;

    //PerspectiveCamera cam1(Point(0.0f, 45.f, 200.0f), Vector(0, 0, -1), Vector(0, 1, 0), pi / 8, pi / 6);
    //PerspectiveCamera cam1(Point(-12.65f, 2.0f, 9.4f), Vector(1.0f,-0.3f,-0.6f), Vector(0, 1, 0), pi/8, pi/6);
    //PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f, 1.0f, -0.6f), Vector(0, 0, 1), pi / 8, pi / 6);
    //PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
    
    world.light.push_back(new PointLight(Point(490 * 1, 159.99f * 1, 279.5f * 1), RGBColor(40000.0f * 1 * 1, 0, 0)));
    world.light.push_back(new PointLight(Point(40 * 1, 159.99f * 1, 249.5f * 1), RGBColor(5000.0f * 1 * 1, 30000.0f * 1 * 1, 5000.0f * 1 * 1)));


    PerspectiveCamera cam1(Point(0, -10.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), Vector(0, 0, 1), pi / 8, pi / 6);
    PerspectiveCamera cam2(Point(-7.0f, -12.f, 7.771f), Vector(1.0f, 1.0f, -1.0f), Vector(0, 0, 1), pi / 8, pi / 6);
    
    RayCastingIntegrator integrator(&world);

    std::cout << "Start rendering first image..." << std::endl;
    Renderer engine1(&cam1, &integrator);
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    engine1.render(img);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "Rendering time:" << std::endl;
    std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()) / 1000000.0 << "[s]" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[mus]" << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << "[ns]" << std::endl;
    img.writePNG("a3-1.png");
    std::cout << "Finished rendering!" << std::endl;

    std::cout << "Start rendering second image..." << std::endl;
    Renderer engine2(&cam2, &integrator);
    engine2.renderThreading(img);
    img.writePNG("a3-2.png");
    std::cout << "Finished rendering!" << std::endl;
}