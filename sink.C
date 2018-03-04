#include <sink.h>

void Sink::SetInput(Image *input)
{
    img1 = input;
}

void Sink::SetInput2(Image *input)
{
    img2 = input;
}

void CheckSum::OutputCheckSum(char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
    int i, j;
    unsigned int RSUM = 0;
    unsigned int GSUM = 0;
    unsigned int BSUM = 0;
    int width = img1->getWidth();
    int height = img1->getHeight();
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            int index = (i* width) + j;
            Pixel p = img1->getPixelAt(index);
            RSUM += (int)p.getR();
            GSUM += (int)p.getG();
            BSUM += (int)p.getB();
        }
    fprintf(f, "CHECKSUM: %d, %d, %d", RSUM % 256, GSUM % 256, BSUM % 256);
    fclose(f);
}