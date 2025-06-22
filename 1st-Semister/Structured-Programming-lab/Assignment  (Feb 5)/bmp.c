#include <stdio.h>
#include <stdint.h>

void checkBMP(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }
    uint16_t fileType;
    fread(&fileType, sizeof(uint16_t), 1, file);

    if (fileType != 0x4D42) {
        printf("Invalid BMP file.\n");
        fclose(file);
        return;
    }
    uint32_t fileSize;
    fread(&fileSize, sizeof(uint32_t), 1, file);
    printf("Valid BMP file.\n");
    printf("Actual File Size: %u bytes\n", fileSize);

    fclose(file);
}

int main() {
    char *filename = "test.bmp";
    checkBMP(filename);
    return 0;
}