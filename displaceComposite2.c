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


PixelWand *makePixelWand(char *string) {

	PixelWand *pixel_wand;
	pixel_wand = NewPixelWand();

	if (PixelSetColor (pixel_wand, string) == MagickFalse) {
		printf("Failed to set color");
		exit(-1);
	}

	return pixel_wand;
}


int main(int argc,char **argv) {
    
    MagickBooleanType status;
    PixelWand *pixelWand;

    MagickWand *magick_wand_a;
    MagickWand *magick_wand_b;
    //MagickWand *magick_wand_c;

    MagickWandGenesis();

    magick_wand_a = NewMagickWand();
    status = MagickReadImage(magick_wand_a, "./displaceCompositeA.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_a);
    }
    
    magick_wand_b = NewMagickWand();
    status = MagickReadImage(magick_wand_b, "./displaceMask.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_b);
    }
    
    MagickSetImageVirtualPixelMethod(magick_wand_a, TransparentVirtualPixelMethod);

    pixelWand = makePixelWand("none");
    status = MagickSetImageBackgroundColor(magick_wand_a, pixelWand);
    
    MagickSetOption(magick_wand_a, "compose:args", "300x53.033");
    status = MagickCompositeImage(magick_wand_a, magick_wand_b, DisplaceCompositeOp, 0, 0);
    if (status == MagickFalse) {
        printf("Failed to composite image b");
        exit(-1); 
    }
      
    status = MagickWriteImages(magick_wand_a, "displaceOutputMerged.png", MagickTrue);

    MagickWandTerminus();
    
    printf("Finished - please compare displaceOutputMerged.png with the result of:\n\n");

    printf("convert displaceCompositeA.png displaceMask.png -virtual-pixel transparent -channel rgba -alpha on -background transparent -define compose:args=300x53.033 -compose displace -composite displaceMerged.png");
    
    return(0);
}


