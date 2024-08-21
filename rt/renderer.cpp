#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>


namespace rt {

Renderer::Renderer(Camera* cam, Integrator* integrator)
    : cam(cam), integrator(integrator), samples(1)
{
}

void Renderer::render(Image& img) {
    if (samples == 1) {
        // Rendering Loop over all pixels
        for (int y = 0; y < img.height(); y++) {
            for (int x = 0; x < img.width(); x++) {
                img(x, y) = integrator->getRadiance(cam->getPrimaryRay(((x + 0.5f) / img.width()) * 2 - 1, -(((y + 0.5f) / img.height()) * 2 - 1)));
            }
        }
    }
    else {
        for (int y = 0; y < img.height(); y++) {
            for (int x = 0; x < img.width(); x++) {
                RGBColor color = RGBColor::rep(.0f);
                for (int i = 0; i < samples; i++) {
                   float xoff = random();
                   float yoff = random();
                   color = color + integrator->getRadiance(cam->getPrimaryRay(((x + xoff) / img.width()) * 2 - 1, -(((y + yoff) / img.height()) * 2 - 1)));
                }
                img(x, y) = color / samples;
            }
        }
    }
    
}

void Renderer::renderThread(int start, Image& img) const {
    for (int pix = start; pix < img.width() * img.height() - 1; pix += THREAD_COUNT) {
        int x = pix % img.width();
        int y = pix / img.width();
        img(pix) = integrator->getRadiance(cam->getPrimaryRay(((x + 0.5f) / img.width()) * 2 - 1, -(((y + 0.5f) / img.height()) * 2 - 1)));
    }

    std::cout << "Thread " << start << " finished rendering!" << std::endl;
}

void Renderer::renderThreadSample(int start, Image& img) {
    for (int pix = start; pix < img.width() * img.height() - 1; pix += THREAD_COUNT) {

        int x = pix % img.width();
        int y = pix / img.width();

        int s = samples;

        
        if (useSamplemap) {
            int add = (samplemap(pix).r * additionalSamples);
            s = add + samples;  
        }
        

        RGBColor color = RGBColor::rep(.0f);
        for (int i = 0; i < s; i++) {
            float xoff = random();
            float yoff = random();
            color = color + integrator->getRadiance(cam->getPrimaryRay(((x + xoff) / img.width()) * 2 - 1, -(((y + yoff) / img.height()) * 2 - 1)));
        }
        img(pix) = color / float(s);
    }

    std::cout << "Thread " << start << " finished rendering!" << std::endl;
}

void Renderer::renderThreading(Image& img) {
    if (samples == 1) {
        std::vector<std::thread*> threads;

        for (int t = 0; t < THREAD_COUNT; t++) {
            std::thread* thread_obj = new std::thread(&Renderer::renderThread, this, t, std::ref(img));
            threads.push_back(thread_obj);
        }

        std::cout << THREAD_COUNT << " threads started rendering..." << std::endl;

        for (int t = 0; t < THREAD_COUNT; t++) {
            threads[t]->join();
        }
    }
    else {
        std::vector<std::thread*> threads;

        for (int t = 0; t < THREAD_COUNT; t++) {
            std::thread* thread_obj = new std::thread(&Renderer::renderThreadSample, this, t, std::ref(img));
            threads.push_back(thread_obj);
        }

        std::cout << THREAD_COUNT << " threads started rendering..." << std::endl;

        for (int t = 0; t < THREAD_COUNT; t++) {
            threads[t]->join();
        }
    }
}

void Renderer::loadSampleMap(const std::string& filename, int width, int height, int add) {
    additionalSamples = add;
    samplemap = Image(width, height);
    samplemap.readPNG(filename);
    useSamplemap = true;
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

void Renderer::test_render1(Image& img) {
    // Rendering Loop over all pixels
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            img(x, y) = a1computeColor(x, y, img.width(), img.height());            
        }
    }
}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {
    // Rendering Loop over all pixels
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            img(x, y) = a2computeColor(cam->getPrimaryRay(((x+0.5f)/img.width()) * 2 - 1, -(((y + 0.5f) / img.height()) * 2 - 1)));
        }
    }
}

}
