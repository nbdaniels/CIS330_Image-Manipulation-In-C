#include "image.h"
#include <memory.h>
#include <source.h>

Pixel::Pixel()
{
    
}

Pixel::Pixel(unsigned char R, unsigned char G, unsigned char B)
{
    this->R = R;
    this->G = G;
    this->B = B;
}

Image::Image()
{
    width = 0;
    height = 0;
    pixels = NULL;
    src = NULL;
}

Image::Image(Source *s)
{
    width = 0;
    height = 0;
    pixels = NULL;
    src = s;
}

Image::Image(const Image &img)
{
    width = img.width;
    height = img.height;
    pixels = (Pixel *)malloc(sizeof(img.pixels));
    pixels = img.pixels;
}

Image::Image(int width, int height)
{
    this->width = width;
    this->height = height;
}

Image::Image(int width, int height, Pixel *pixels)
{
    this->width = width;
    this->height = height;
    memcpy(this->pixels, pixels, 3 * width * height * sizeof(unsigned char));
}

void Image::setPixelAt(int i, int i2, Pixel *pix) {
    pixels[i].setPixelR(pix[i2].getR());
    pixels[i].setPixelG(pix[i2].getG());
    pixels[i].setPixelB(pix[i2].getB());
}
void Image::setPixelAt(int i, Pixel pix) {
    pixels[i].setPixelR(pix.getR());
    pixels[i].setPixelG(pix.getG());
    pixels[i].setPixelB(pix.getB());
}
void Image::setWidth(int newWidth) { width = newWidth; }
void Image::setHeight(int newHeight) { height = newHeight; }
void Image::setPixels(Pixel *pixels, int num) { memcpy(this->pixels, pixels, num); }
void Image::setSource(Source *src) { this->src = src; };
void Image::allocatePixels(int num) { pixels = (Pixel *)malloc(num); };
void Image::freeMe()
{
    free(pixels);
    free(this);
}

void Image::Update() const
{
    //printf("UPDATING AN IMAGE\n");
    src->Update();
}