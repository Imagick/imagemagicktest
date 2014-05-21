#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>


void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}


int main(int argc,char **argv) {
    
    MagickBooleanType status;
    
    MagickWand *magick_wand, *pseudo_wand;
 
    int columns = 500;
    int rows = 500;
    
    /*
    Read an image.
    */
    MagickWandGenesis();
   
    pseudo_wand = NewMagickWand();

    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    printf("Step 1");

    if (MagickReadImage(pseudo_wand, "gradient:rgba(255,255,255,0)-white") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }

    printf("Step 2");

	status = MagickSetImageFormat(pseudo_wand, "png");

	/* No magick is going to happen */
	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(pseudo_wand);
	}

    printf("Step 3");

    status = MagickWriteImages(pseudo_wand, "gradientMemTest.png", MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
        
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}