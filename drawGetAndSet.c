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

int main(int argc,char **argv)
{
    DrawingWand *drawing_wand;
    MagickWand *magick_wand;
    PixelWand *background_color_wand;
    MagickBooleanType status;

    MagickWandGenesis();
    
    drawing_wand = NewDrawingWand();

    //DrawSetDensity(drawing_wand,"200x200");
    DrawSetDensity(drawing_wand,"200,200");

    magick_wand = NewMagickWand();
    background_color_wand = makePixelWand("red");
    MagickNewImage(magick_wand, 500, 500, background_color_wand);
    DrawRectangle(drawing_wand, 100, 100, 400, 400);

    status = MagickDrawImage(magick_wand, drawing_wand);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    
    MagickWriteImages(magick_wand, "./output/setDensity.png", MagickTrue);

    MagickWandTerminus();
    return (0);
}
