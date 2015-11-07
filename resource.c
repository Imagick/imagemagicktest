

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;

    MagickWandGenesis();
    magick_wand = NewMagickWand();

    MagickSetResourceLimit(MemoryResource, 1000 * 1000);
    MagickSetResourceLimit(DiskResource, 1000 * 1000);
    

    status = MagickReadImage(magick_wand, "./images/picture-100M-6000x6000.png");

    if (status == MagickFalse) {
        printf("Failed to MagickReadImage");
        return -1;
    }

    printf("This shouldn't be reached - the image is larger than the area resource.\n");

    MagickSetImageFormat(magick_wand, "png");

    status = MagickWriteImages(magick_wand, "./output/resource_output.png", MagickTrue);
    if (status == MagickFalse) {
        printf("Failed to MagickWriteImages");
        return -1;
    }

    MagickWandTerminus();
 
    return(0);
}


