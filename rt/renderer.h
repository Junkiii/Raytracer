#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <rt/integrators/integrator.h>
#include <core/random.h>
#include <thread>
#include <atomic>

namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
    Renderer(Camera* cam, Integrator* integrator);
    void setSamples(uint samples) { this->samples = samples; }
    void render(Image& img);

    //For multithreading:
    void renderThreading(Image& img);

    void test_render1(Image& img);
    void test_render2(Image& img);

    void loadSampleMap(const std::string& filename, int width, int height, int add);

    void progressBar(float no_lines);

    
private:
    Camera* cam;
    Integrator* integrator;
    uint samples;

    //For multithreading
    const int THREAD_COUNT = std::thread::hardware_concurrency();
    void renderThread(int start, Image& img) const;
    void renderThreadSample(int start, Image& img);

    Image samplemap;
    bool useSamplemap = false;
    int additionalSamples = -1;
};

}

#endif