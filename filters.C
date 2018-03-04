#include "filters.h"
#include <logging.h>

void Shrinker::Execute()
{
    //printf("GETTING IMAGE WIDTH\n");
    int width = img1->getWidth() / 2;
    //printf("GETTING IMAGE HEIGHT\n");
    int height = img1->getHeight() / 2;
    //printf("SETTING WIDTH AND HEIGHT\n");
    img.setHeight(height);
    img.setWidth(width);
    //printf("ALLOCATING PIXELS\n"); 
    int size = 3 * height * width * sizeof(unsigned char);
    img.allocatePixels(size);
    //printf("SETTING PIXELS IN HALF\n");
    //fprintf(stderr, "height width = %d %d\n", img.getHeight(), img.getWidth());
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int index = ((i * width) + j);
            int index2 = ((2 * i * img1->getWidth()) + (2*j));
            img.setPixelAt(index, index2, img1->getPixels());
            //img.setPixelAt(index, index2 + 1, img1->getPixels());
            //img.setPixelAt(index, index2 + 2, img1->getPixels());
        }
    }
    //printf("DONE SETTING PIXELS IN HALF\n");
    //printf("DONE SHRINKING IMAGE\n");
}

void Shrinker::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void TBConcat::Execute()
{
    //printf("CONCATENING TOP/BOTTOM IMAGE\n");
    if (img1->getWidth() != img2->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), img1->getWidth(), img2->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int height = img1->getHeight() + img2->getHeight();
    int width = img1->getWidth();
    //printf("ALLOCATING MEMORY\n");
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3*width*height*sizeof(unsigned char));
    
    int i, j;
    int index;
    //printf("FIRST IMAGE CONCATENATION\n");
    for (i = 0; i < img1->getHeight(); i++)
    {
        for (j = 0; j < width; j++)
        {
            index = ((i * width) + j);
            img.setPixelAt(index, index, img1->getPixels());
        }
    }
    
    //printf("SECOND IMAGE CONCATENATION\n");
    for (i = 0; i < img2->getHeight(); i++)
    {
        for (j = 0; j < width; j++, index++)
        {
            int index2 = ((i * width) + j);
            img.setPixelAt(index, index2, img2->getPixels());
        }
    }
    //printf("DONE CONCATENATING TOP/BOTTOM IMAGE\n");
}

void TBConcat::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    //printf("TB INPUT 2\n");
    sprintf(msg, "%s: about to update input2", SourceName());
    Logger::LogEvent(msg);
    getInput2()->Update();
    sprintf(msg, "%s: done updating input2", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void LRConcat::Execute()
{
    //printf("CONCATENING LEFT/RIGHT IMAGE\n");
    if (img1->getHeight() != img2->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), img1->getHeight(), img2->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int width = img1->getWidth() + img2->getWidth();
    int height;
    if (img1->getHeight() > img2->getHeight())
        height = img1->getHeight();
    else
        height = img2->getHeight();
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3*width*height*sizeof(unsigned char));
    
    int i, j;
    int index2 = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < img1->getWidth(); j++, index2++)
        {
            int index = ((i * width) + j);
            img.setPixelAt(index, index2, img1->getPixels());
        }
    }
    index2 = 0;
    for (i = 0; i < height; i++)
    {
        for (j = img1->getWidth(); j < width; j++, index2++)
        {
            int index = ((i * width) + j);
            
            img.setPixelAt(index, index2, img2->getPixels());
        }
    }
    //printf("DONE CONCATENATING LEFT/RIGHT IMAGE\n");
}

void LRConcat::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    //printf("LR INPUT 2\n");
    if (getInput2() == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    sprintf(msg, "%s: about to update input2", SourceName());
    Logger::LogEvent(msg);
    getInput2()->Update();
    //printf("CHILLING\n");
    sprintf(msg, "%s: done updating input2", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void Blender::Execute()
{
    if (img1->getHeight() != img2->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), img1->getHeight(), img2->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (img1->getWidth() != img2->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), img1->getWidth(), img2->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if (factor > 1.00)
    {
        char msg[1024];
        sprintf(msg, "Invalid factor for %s: %f", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    Pixel pixel1, pixel2;
    int width = img1->getWidth();
    int height = img2->getHeight();
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3*width*height*sizeof(unsigned char));
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int index = (i * width) + j;
            Pixel newPix;
            Pixel pixel1, pixel2;
            pixel1 = img1->getPixelAt(index);
            pixel2 = img2->getPixelAt(index);
            newPix.setPixelR( (pixel1.getR() * factor) + (pixel2.getR() * (1 - factor)) );
            newPix.setPixelG( (pixel1.getG() * factor) + (pixel2.getG() * (1 - factor)) );
            newPix.setPixelB( (pixel1.getB() * factor) + (pixel2.getB() * (1 - factor)) );
            img.setPixelAt(index, newPix);
        }
    }
}

void Blender::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    if (getInput2() == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    sprintf(msg, "%s: about to update input2", SourceName());
    Logger::LogEvent(msg);
    getInput2()->Update();
    sprintf(msg, "%s: done updating input2", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void Blender::SetFactor(float factor)
{
    this->factor = factor;
}

void
Crop::Execute(void)
{
    //printf("CROPPING\n");
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= img1->getWidth() || Istop >= img1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= img1->getHeight() || Jstop >= img1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = img1->getWidth();
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3 * width * height * sizeof(unsigned char));
    //printf("STARTING TO CROP\n");
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            img.setPixelAt(idx, img1->getPixelAt(idx1));
        }
    //printf("DONE CROPPING\n");
}

void Crop::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void Transpose::Execute()
{
    //printf("TRANSPOSING\n");
    int width = img1->getHeight();
    int height = img1->getWidth();
    //printf("TRANSPOSE WIDTH: %d\nTRANSPOSE HEIGHT: %d\n", width, height);
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3 * width * height * sizeof(unsigned char));
    int i, j;
    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            Pixel p = img1->getPixelAt((i * height) + j);
            img.setPixelAt((j * width) + i, p);
        }
    }
    //printf("DONE TRANSPOSING\n");
}

void Transpose::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void Invert::Execute()
{
    //printf("INVERTING\n");
    int height = img1->getHeight();
    int width = img1->getWidth();
    img.setWidth(width);
    img.setHeight(height);
    img.allocatePixels(3 * width * height * sizeof(unsigned char));
    //printf("INVERT WIDTH: %d\nINVERT HEIGHT: %d\n", width, height);
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int index = (i * width) + j;
            Pixel newPix = img1->getPixelAt(index);
            newPix.setPixelR( 255 - newPix.getR() );
            newPix.setPixelG( 255 - newPix.getG() );
            newPix.setPixelB( 255 - newPix.getB() );
            img.setPixelAt(index, newPix);
        }
    }
    //printf("DONE INVERTING\n");
}

void Invert::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to update input1", SourceName());
    Logger::LogEvent(msg);
    getInput()->Update();
    sprintf(msg, "%s: done updating input1", SourceName());
    Logger::LogEvent(msg);
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}