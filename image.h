#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>

class Source;

class Pixel {
private:
    unsigned char R;
    unsigned char G;
    unsigned char B;
public:
    Pixel();
    Pixel(unsigned char, unsigned char, unsigned char);
    unsigned char getR() { return R; };
    unsigned char getG() { return G; };
    unsigned char getB() { return B; };
    void setPixelR(unsigned char c) { R = c; };
    void setPixelG(unsigned char c) { G = c; };
    void setPixelB(unsigned char c) { B = c; };
};
class Image {
private:
    int width;
    int height;
    Source *src;
    Pixel *pixels;
public:
    Image ();
    Image (Source *);
    Image (const Image &img);
    Image (int, int);
    Image (int, int, Pixel*);
    int getWidth() const { return width; };
    int getHeight() const { return height; };
    Pixel *getPixels() const { return pixels; };
    Pixel getPixelAt(int i) const { return pixels[i]; };
    Source *getSource() const { return src; };
    void setPixelAt(int, int, Pixel *);
    void setPixelAt(int, Pixel);
    void setWidth(int);
    void setHeight(int);
    void setSource(Source *);
    void allocatePixels(int);
    void setPixels(Pixel *, int) ;
    void freeMe();
    void Update() const;
};

#endif