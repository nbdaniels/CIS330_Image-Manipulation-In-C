#include <PNMwriter.h>

PNMwriter::PNMwriter()
{
}

PNMwriter::~PNMwriter()
{
    
}

void PNMwriter::Write(char *filename)
{
    //printf("WRITING IMAGE\n");
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
    int len = img1->getWidth() * img1->getHeight();
    //printf("START WRITING TO FILE\n");
    fprintf(f, "P6\n%d %d\n%d\n", img1->getWidth(), img1->getHeight(), 255);
    //printf("START WRITING IMAGE TO FILE\n");
    fwrite(img1->getPixels(), 3 * sizeof(unsigned char), len, f);
    fclose(f);
    //printf("DONE WRITING IMAGE\n");
}