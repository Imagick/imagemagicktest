#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    

int main(int argc,char **argv) {
	MagickWand *magick_wand;
	MagickBooleanType status;

	MagickWandGenesis();
	magick_wand = NewMagickWand();

    //chdir("/home/github/imagemagicktest/images");

	//This is a color image
	status = MagickReadImage(magick_wand, "./images/red.svg");
	
	if (status == MagickFalse) {
        printf("Failed to MagickReadImage");
        return -1;
    }


    MagickSetImageFormat(magick_wand, "png");

	status = MagickWriteImages(magick_wand, "./67125.png", MagickTrue);
	if (status == MagickFalse) {
        printf("Failed to MagickWriteImages");
        return -1;
    }
	
	
	MagickWandTerminus();
 
    return(0);
}