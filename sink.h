#ifndef SINK_H
#define SINK_H

#include <image.h>

class Sink
{
protected:
    const Image *img1 = NULL;
    const Image *img2 = NULL;
public:
    void SetInput(Image *);
    void SetInput2(Image *);
    const Image *getInput() { return img1; };
    const Image *getInput2() { return img2; };
    virtual const char *SinkName() = 0;
};

class CheckSum : public Sink
{
public:
    void OutputCheckSum(char *);
    virtual const char *SinkName() { return "CheckSum"; };
};

#endif