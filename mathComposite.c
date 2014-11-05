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

    MagickWandGenesis();
    
    magick_wand_a = NewMagickWand();
    status = MagickReadImage(magick_wand_a, "./mathComposite1.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_a);
    }
    
    magick_wand_b = NewMagickWand();
    status = MagickReadImage(magick_wand_b, "./mathComposite2.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_b);
    }

    MagickSetImageVirtualPixelMethod(magick_wand_a, TransparentVirtualPixelMethod);

    pixelWand = makePixelWand("none");
    status = MagickSetImageBackgroundColor(magick_wand_a, pixelWand);

//    MagickSetOption(magick_wand_a, "compose:args", "1,0,-0.5,0.5");
//    MagickSetOption(magick_wand_b, "compose:args", "1,0,-0.5,0.5");

    MagickSetImageArtifact(magick_wand_a, "compose:args", "1,0,-0.5,0.5");
    MagickSetImageArtifact(magick_wand_b, "compose:args", "1,0,-0.5,0.5");

    status = MagickCompositeImage(magick_wand_a, magick_wand_b, MathematicsCompositeOp, 0, 0);
    if (status == MagickFalse) {
        printf("Failed to composite image b");
        exit(-1); 
    }

    status = MagickWriteImages(magick_wand_a, "mathCompositeOutput.png", MagickTrue);

    MagickWandTerminus();
    
    printf("Finished - please compare displaceOutput.png with the result of:\n\n");
    
 //convert mathComposite1.png mathComposite2.png -compose mathematics -define compose:args="1,0,-0.5,0.5" -composite result.png    
    
    return(0);
}


