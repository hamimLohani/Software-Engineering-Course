#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t bfType;      
    uint32_t bfSize;      
    uint16_t bfReserved1; 
    uint16_t bfReserved2; 
    uint32_t bfOffBits;   
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;         
    int32_t biWidth;         
    int32_t biHeight;        
    uint16_t biPlanes;       
    uint16_t biBitCount;     
    uint32_t biCompression;  
    uint32_t biSizeImage;    
    int32_t biXPelsPerMeter; 
    int32_t biYPelsPerMeter; 
    uint32_t biClrUsed;      
    uint32_t biClrImportant; 
} BITMAPINFOHEADER;

#pragma pack(pop)

void convertToGrayscale(const char *filename) {
    FILE *file = fopen(filename, "rb");
    FILE *file2 = fopen("abc.bmp", "wb");
    if (!file) {
        printf("Error: Unable to open file!\n");
        return;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    if (infoHeader.biBitCount != 24) {
        printf("Unsupported BMP format (must be 24-bit BMP).\n");
        fclose(file);
        return;
    }
    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file2);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file2);

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int padding = (4 - (width * 3) % 4) % 4;

    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    for (int )

    fclose(file);
    printf("Successfully converted to grayscale!\n");
}

int main() {
    convertToGrayscale("lena.bmp");
    return 0;
}