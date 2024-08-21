#include <rt/solids/quadric.h>

namespace rt {

    Quadric::Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, CoordMapper* texMapper, Material* material)
        : Solid(texMapper, material), a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j) {}

    /**
    * Returns the bounding box of the quadric.
    * Could be precomputed. Is it worth ?
    */
    BBox Quadric::getBounds() const {
        return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX), true);
    }

    /**
    * Intersection function of the quadric.
    */
    Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const {
        float alpha = a * ray.d.x * ray.d.x + b * ray.d.y * ray.d.y + c * ray.d.z * ray.d.z + d * ray.d.x * ray.d.y + e * ray.d.x * ray.d.z + f * ray.d.y * ray.d.z;
        float beta = a * 2 * ray.o.x * ray.d.x + b * 2 * ray.o.y * ray.d.y + c * 2 * ray.o.z * ray.d.z + d * ray.o.x * ray.d.y + d * ray.o.y * ray.d.x + e * ray.o.x * ray.d.z + e * ray.o.z * ray.d.x + f * ray.o.y * ray.d.z + f * ray.o.z * ray.d.y + g * ray.d.x + h * ray.d.y + i * ray.d.z;
        float gamma = a * ray.o.x * ray.o.x + b * ray.o.y * ray.o.y + c * ray.o.z * ray.o.z + d * ray.o.x * ray.o.y + e * ray.o.x * ray.o.z + f * ray.o.y * ray.o.z + g * ray.o.x + h * ray.o.y + i * ray.o.z + j;
        
        if (!fequal(alpha, .0f)) { // 2 solutions
            float radical = beta * beta - 4 * alpha * gamma;
            if (radical < 0) return Intersection::failure();
            float t1 = (-beta + sqrt(radical)) / (2 * alpha);
            float t2 = (-beta - sqrt(radical)) / (2 * alpha);

            float minpos;
            if (t1 > 0 && t2 > 0) minpos = min(t1, t2);
            else if (t1 < 0 && t2 > 0) minpos = t2;
            else minpos = t1;

            Vector normal = calculate_normal(ray.getPoint(minpos), ray);
            if (previousBestDistance < minpos) return Intersection::failure();
            return Intersection(minpos, ray, this, normal, ray.getPoint(minpos));
        }
        else if (fequal(alpha, .0f) && !fequal(beta, .0f)) { // 1 solution
            float t = -gamma / beta;
            Vector normal = calculate_normal(ray.getPoint(t), ray); 
            if (previousBestDistance < t) return Intersection::failure();
            return Intersection(t, ray, this, normal, ray.getPoint(t));
        }
        else if (fequal(alpha, .0f) && fequal(beta, .0f)) { // no solution
            return Intersection::failure();
        }
    }

    /**
    * Calculates the normal at a given hitpoint.
    * The gradient is the normal vector.
    */
    Vector Quadric::calculate_normal(Point hitpoint, Ray ray) const {
        Vector normal(2 * a * hitpoint.x + d * hitpoint.y + e * hitpoint.z + g,
                      2 * b * hitpoint.y + d * hitpoint.x + f * hitpoint.z + h,
                      2 * c * hitpoint.z + e * hitpoint.x + f * hitpoint.y + i);
        return normal.normalize();
    }

    Solid::Sample Quadric::sample() const {
        NOT_IMPLEMENTED;
    }

    float Quadric::getArea() const {
        NOT_IMPLEMENTED;
    }

}
