#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

typedef struct
{
    unsigned char signature[2];
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int data_off_set;

} BMPFileHeader;

typedef struct
{
    unsigned int headerSize;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitperpixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorUsed;
    unsigned int colorImportant;
} BMPInfoHeader;

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGBPixel;
#pragma pack(1)

int main()
{
    FILE *inputfile = fopen("lena.bmp", "rb");
    FILE *outputfile = fopen("lena_grayscale.bmp", "wb");

    if (inputfile == NULL || outputfile == NULL)
    {
        printf("Error opening files\n");
        return 1;
    }
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    fread(&fileHeader, sizeof(BMPFileHeader), 1, inputfile);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, inputfile);
    if (infoHeader.bitperpixel != 24)
    {
        printf("Image is not 24-bit\n");
        fclose(inputfile);
        fclose(outputfile);
        return 1;
    }
    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, outputfile);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, outputfile);
    int width = infoHeader.width;
    int height = infoHeader.height;
    int si = width * height * 3;

    unsigned char *c = malloc(si); // **IMPORTANT unsigned char**
    fread(c, si, 1, inputfile);

    for (int i = 0; i < si; i += 3) {
        uint32_t gr =  (.299 * c[i + 2] + .587 * c[i + 1] + .114 * c[i]);
        c[i] = c[i + 1] = c[i + 2] = gr;
    }
    fwrite(c, si, 1, outputfile);
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}