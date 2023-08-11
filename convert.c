#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "rgba_bitmap/rgba_bitmap.h"

#include <stdio.h>

int main(int argc, char **argv) {
    FILE *F;
    unsigned char *bitmap;
    long size;
    unsigned long width, height;
    size_t num_pixels;
    unsigned char * pixels;

    F = fopen("sample.rgba", "rb+");
    if (F) {
        if (0 == fseek(F, 0, SEEK_END)) {
            size = ftell(F);
            rewind(F);
        }
        else perror("fseek");
        bitmap = malloc(size);
        if (bitmap) {
            fread(bitmap, 1, size, F);
            pixels = rgba_decode_file_data_to_bitmap(bitmap, size, bitmap_buffer_format_RGBA, 0, &width, &height, &num_pixels);
            if (pixels && 0 == stbi_write_png("sample.png", width, height, 4, pixels, width * 4))
            {
                perror("write_png");
            }
            free(bitmap);
        }
        fclose(F);
    }
    else perror("fopen");
    return 0;
}
