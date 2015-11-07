//GetImageProperty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>

void ThrowWandError(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}



int main(int argc,char **argv) {
    MagickWand *magick_wand;
    
    MagickBooleanType status;
    
    MagickWandGenesis();
    
    magick_wand = NewMagickWand();
    
    status = MagickSetSize(magick_wand, 100, 100);

	if (status == MagickFalse) {
		printf("Failed to set size\n");
		return -1;
	}
    MagickReadImage(magick_wand, "xc:red");

//    status = MagickSetImageFormat(magick_wand, "png");

    status = MagickWriteImage(magick_wand, "./edge_omgwtf.png");
    MagickWandTerminus();

    return 0;
}

