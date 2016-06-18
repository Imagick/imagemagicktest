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
    
    MagickSizeType resource_size;

    MagickWandGenesis();
    resource_size = MagickGetResourceLimit(TimeResource);
    printf("TimeResource  : %lu\n", resource_size);
    MagickSetResourceLimit(TimeResource, 100);
    
    resource_size = MagickGetResourceLimit(TimeResource);
    printf("TimeResource  : %lu\n", resource_size);

    MagickWandTerminus();
 
    return(0);
}


