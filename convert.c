#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "rgba_bitmap/rgba_bitmap.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>

#define RGBA_BITMAP_MAGIC_NUMBER            0x52474241   /* 'RGBA' */

struct rgba_header {
    uint32_t magic;
    uint32_t width;
    uint32_t height;
};

int main(int argc, char **argv) {
    const char *infile = "/Users/enno/rgba/rgba_bitmap/sample.rgba";
    const char *outfile = "sample.png";
    int fdin = -1;
    void *src = NULL;
    int success;
    struct stat statbuf;
    struct rgba_header *header;

    success = ((fdin = open(infile, O_RDONLY)) >= 0);
    if (success)
        success = (fstat(fdin, &statbuf) >= 0);
    else
        perror("could not open");
    if (success)
        success = (src = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fdin, 0)) != (caddr_t)-1;
    else
        perror("could not fstat");

    header = (struct rgba_header *)src;
    if (success)
        success = (header->magic == RGBA_BITMAP_MAGIC_NUMBER);
    else
        perror("could not mmap");
    
    if (success)
        success = stbi_write_png(outfile, header->width, header->height, 4, header+1, 0);

    if (src != (caddr_t)-1)
        munmap(src, statbuf.st_size);

    return !success;
}
