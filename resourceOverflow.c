#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define IM7 

#ifdef IM7
#include <MagickWand/MagickWand.h>
#else
#include <wand/MagickWand.h>
#endif


int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;
    PixelWand *pixel_wand;
    MagickSizeType resource_size;
    
    char formatString[1000];

    printf("Size of MagickSizeType is %d \n",
        sizeof(MagickSizeType)
    );
    sprintf(formatString, "MemoryResource  : %%%s \n", MagickSizeFormat);
    printf("Format string is %s\n", formatString);
    MagickWandGenesis();

    resource_size = MagickGetResourceLimit(MemoryResource);
    printf(formatString, resource_size);

    MagickSetResourceLimit(MemoryResource, 5000 * 5000);
    resource_size = MagickGetResourceLimit(MemoryResource);
    printf(formatString, resource_size);

    MagickSetResourceLimit(MemoryResource, 50000 * 5000);
    resource_size = MagickGetResourceLimit(MemoryResource);
    printf(formatString, resource_size);
    
    MagickSetResourceLimit(MemoryResource, 50000ULL * 50000);
    resource_size = MagickGetResourceLimit(MemoryResource);
    printf(formatString, resource_size);

    MagickWandTerminus();
 
    return(0);
}


