#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <PNMreader.h>
#include <logging.h>

PNMreader::PNMreader(char *filename)
{
    //printf("ALLOCATING FILENAME\n");
    this->filename = (char *) malloc(sizeof(filename));
    this->filename = filename;
}

PNMreader::~PNMreader()
{
}

void PNMreader::Execute()
{
    //printf("READING FILE\n");
    FILE *f = fopen(filename, "rb");
    char magicNum[128];
    int  width, height, maxval;
    
    if (filename == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
    
    fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    //printf("Magic num = %s width = %d, height = %d, maxval = %d\n", magicNum, width, height, maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
        return;
    }
    //printf("SETTING WIDTH\n");
    img.setWidth(width);
    //printf("SETTING HEIGHT\n");
    img.setHeight(height);
    //printf("img width:%d img height:%d\n", img.getWidth(), img.getHeight());
    int len = width * height;
    img.allocatePixels(3 * sizeof(unsigned char) * len);
    fread(img.getPixels(), 3 * sizeof(unsigned char), len, f);
    //printf("img width:%d img height:%d\n", img.getWidth(), img.getHeight());
    fclose(f);
    //printf("DONE READING FILE\n");
}

void PNMreader::Update()
{
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}
