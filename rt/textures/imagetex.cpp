#include <rt/textures/imagetex.h>

namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
    :bh(bh), i(i)
{
    image.readPNG(filename);
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
    : image(image), bh(bh), i(i)
{

}

RGBColor ImageTexture::getColor(const Point& coord) {
    float pix_x;
    float pix_y;
    float tu;
    float tv;

    if (bh == REPEAT) {
        tu = coord.x - floor(coord.x);
        tv = coord.y - floor(coord.y);

        pix_x = tu * image.width();
        pix_y = tv * image.height();
    }
    else if (bh == MIRROR) {
        int l_u = floor(coord.x);
        int l_v = floor(coord.y);

        tu = coord.x - l_u;
        tv = coord.y - l_v;

        if (l_u % 2 != 0) tu = 1 - tu;
        if (l_v % 2 != 0) tv = 1 - tv;

        pix_x = tu * image.width();
        pix_y = tv * image.height();
    }
    else if (bh == CLAMP) {
        pix_x = 0;
        pix_y = 0;
        
        if (coord.x < 0) {
            tu = 0;
            pix_x = tu * image.width();
        }
        else if (coord.x > 1) { 
            tu = 1; 
            pix_x = image.width();
        }
        else {
            tu = coord.x;
            pix_x = tu * image.width();
        }

        float tv;
        if (coord.y < 0) {
            tv = 0;
            pix_y = tv * image.height();
        }
        else if (coord.y > 1) {
            tv = 1; 
            pix_y = image.height();
        }
        else {
            tv = coord.y;
            pix_y = tv * image.height();
        }
    }

    if (i == NEAREST) {
        pix_x = min((uint)floor(pix_x), (uint)image.width() - 1);
        pix_y = min((uint)floor(pix_y), (uint)image.height() - 1);
        return image(pix_x, pix_y);
    }
    else {
        float u = tu * (image.width() - 1);
        float v = tv * (image.height() - 1);

        int floor_u = floor(u);
        int floor_v = floor(v);

        float fu = u - floor_u;
        float fv = v - floor_v;

        return (1 - fu) * (1 - fv) * image(floor_u, floor_v)
            + (1 - fu) * (fv)*image(floor_u, min((uint)floor_v + 1, image.height() - 1))
            + (fu) * (1 - fv) * image(min((uint)floor_u + 1, image.width() - 1), floor_v)
            + (fu) * (fv)*image(min((uint)floor_u + 1, image.width() - 1), min((uint)floor_v + 1, image.height() - 1));
    }
}

/// <summary>
/// Calculate the color change in x direction.
/// Used for bump mapping.
/// </summary>
/// <param name="coord">Texture coordinates between 0 and 1</param>
/// <returns>Differential</returns>
RGBColor ImageTexture::getColorDX(const Point& coord) {
    float pix_x = coord.x * (image.width() - 1);
    float pix_y = coord.y * (image.height() - 1);
    /*
    * Calculating the forward difference, if possible; else return black.
    */
    if (i == NEAREST) {
        RGBColor forward_diff = (getColor(Point((pix_x + 1.0f) / image.width(), coord.y, coord.z)) - getColor(coord)) * image.width();
        return forward_diff;
    }
    else {
        RGBColor central_diff = (getColor(Point((pix_x + 1.0f) / image.width(), coord.y, coord.z)) - getColor(Point((pix_x - 1.0f) / image.width(), coord.y, coord.z))) * 0.25f * image.width();
        return central_diff;
    }
}

/// <summary>
/// Calculate the color change in y direction.
/// Used for bump mapping.
/// </summary>
/// <param name="coord">Texture coordinates between 0 and 1</param>
/// <returns>Differential</returns>
RGBColor ImageTexture::getColorDY(const Point& coord) {
    float pix_x = coord.x * (image.width() - 1.0f);
    float pix_y = coord.y * (image.height() - 1.0f);
    /*
    * Use the forward difference for NEAREST and the central difference for bilinear.
    * Bilinear isnt completely right but seems to be not that much off.
    */
    if (i == NEAREST) {
        RGBColor forward_diff = (getColor(Point(coord.x, (pix_y + 1.0f) / image.height(), coord.z)) - getColor(coord)) * image.height();
        return forward_diff;
    }
    else {
        RGBColor central_diff = (getColor(Point(coord.x, (pix_y + 1.0f) / image.height(), coord.z)) - getColor(Point(coord.x, (pix_y - 1.0f) / image.height(), coord.z))) * 0.25f * image.height();
        return central_diff;
    }
}

}