#include <rt/primmod/bmap.h>
#include <core/assert.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
    : base(base), bumpmap(bumpmap), bv1(bv1), bv2(bv2), bv3(bv3), vscale(vscale)
{
    setCoordMapper(new TriangleMapper(bv1, bv2, bv3));
    
    Vector e_x = base->getV2() - base->getV1();
    Vector e_y = base->getV3() - base->getV1();
    Vector e_z = cross(e_x, e_y);

    Matrix transform = Matrix::system(e_x, e_y, e_z);

    /*
    * Precalculating w_x and w_y with the transformation matrix and e vectors.
    */
    w_x = transform * (bv2 - bv1);
    w_y = transform * (bv3 - bv1);

    sign = copysignf(1.0f, cross(bv2 - bv1, bv3 - bv1).z);
}

BBox BumpMapper::getBounds() const {
    return base->getBounds();
}

// TODO: A full implementation has to make use of the coord mappers as well!

/// <summary>
/// Wrapper intersection function for a triangle to realize bump mapping.
/// Perturbs the normal of a triangle intersection based on a grayscale bump map.
/// </summary>
/// <param name="ray">Ray with which to intersect.</param>
/// <param name="previousBestDistance">Smallest intersection distance so far.</param>
/// <returns>Intersection object.</returns>
Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    /*
    * Call the default intersect() function from the tirangle to get the intersection.
    * You just have to perturb the normal of that intersection.
    */
    Intersection i = base->intersect(ray, previousBestDistance);
    if (i) {
        // Compute the bump map texture coordinates where the hit occured.
        Point tex_hitpoint = base->texMapper->getCoords(i);
        // Compute the gradient at the given texture coordinates. Assume that the image is gray.
        RGBColor d_x = bumpmap->getColorDX(tex_hitpoint);
        RGBColor d_y = bumpmap->getColorDY(tex_hitpoint);
         
        // Multiply w_x, w_y and the gradient to perturb the normal in world space.
        Vector D = d_x.r * cross(i.normal(), w_y) - d_y.r * cross(i.normal(), w_x);
        // Return a intersection with the new normal.
        Vector new_normal = i.normal() + sign * D * vscale;
        return Intersection(i.distance, i.ray, i.solid, new_normal.normalize() , i.local());
    }
    return i;
}

void BumpMapper::setMaterial(Material* m) {
    base->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    base->setCoordMapper(cm);
}

}