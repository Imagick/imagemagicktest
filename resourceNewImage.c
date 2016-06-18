#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//#define IM7 

#ifdef IM7
#include <MagickWand/MagickWand.h>
#else
#include <wand/MagickWand.h>
#endif

void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}

void checkResources() {
    MagickSizeType resource_size;

    MagickSetResourceLimit(MemoryResource,  50000ULL * 50000);
    MagickSetResourceLimit(DiskResource, 50000ULL * 50000);
    MagickSetResourceLimit(AreaResource, 50000ULL * 50000);
    MagickSetResourceLimit(WidthResource, 50000ULL);
    MagickSetResourceLimit(HeightResource, 50000ULL);
    MagickSetResourceLimit(TimeResource, 100);

    resource_size = MagickGetResourceLimit(MemoryResource);
    printf("MemoryResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(DiskResource);
    printf("DiskResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(AreaResource);
    printf("AreaResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(WidthResource);
    printf("WidthResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(HeightResource);
    printf("HeightResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(TimeResource);
    printf("TimeResource  : %lu\n", resource_size);
    
    resource_size = MagickGetResourceLimit(MapResource);
    printf("MapResource  : %lu\n", resource_size);
}

int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;
    PixelWand *pixel_wand;

    MagickWandGenesis();
    magick_wand = NewMagickWand();
    //checkResources();

    pixel_wand = NewPixelWand();  
    PixelSetColor(pixel_wand, "white");

    status = MagickNewImage(magick_wand, 400, 200, pixel_wand);

    if (status == MagickFalse) {
        printf("Failed to MagickReadImage");
        ThrowWandException(magick_wand);
        return -1;
    }

    MagickSetImageFormat(magick_wand, "png");

    status = MagickWriteImage(magick_wand, "./resource_new_output.png");
    if (status == MagickFalse) {
        printf("Failed to MagickWriteImages");
        ThrowWandException(magick_wand);
        return -1;
    }

    MagickWandTerminus();
 
    return(0);
}


