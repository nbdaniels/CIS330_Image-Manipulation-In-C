#include <source.h>

Source::Source()
{
    img = Image(this);
}

Image * Source::GetOutput()
{
    //printf("RETURNING OUTPUT\n");
    return &img;
}

Image Source::getImage()
{
    return img;
}

Color::Color(int width, int height, unsigned char R, unsigned char G, unsigned char B)
{
    this->width = width;
    this->height = height;
    this->R = R;
    this->G = G;
    this->B = B;
    Color::Execute();
}

void Color::Execute()
{
    //printf("CONSTANT COLOR IMAGE\n");
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3 * width * height * sizeof(unsigned char));
    Pixel p = Pixel(getR(), getG(), getB());
    int i, j;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            img.setPixelAt((i * width) + j, p);
        }
}

void Color::Update()
{
    
}