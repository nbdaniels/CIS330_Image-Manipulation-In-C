#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>

class Source
{
protected:
    Image img;
    virtual void Execute() = 0;
public:
    Source();
    virtual void Update() = 0;
    Image *GetOutput();
    Image getImage();
    virtual const char *SourceName() = 0;
};

class Color : public Source
{
private:
    int width;
    int height;
    unsigned char R, G, B;
public:
    Color(int, int, unsigned char, unsigned char, unsigned char);
    unsigned char getR() { return R; };
    unsigned char getG() { return G; };
    unsigned char getB() { return B; };
    virtual void Execute();
    virtual void Update();
    virtual const char *SourceName() { return "Constant Color"; };
};
#endif