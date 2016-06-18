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

	//This is a color image
	status = MagickReadImage(magick_wand, "./Biter_500.jpg");

	MagickScaleImage(magick_wand, 16, 16);

//	MagickQuantizeImage(
//		magick_wand,
//		//Changing to 255 makes the image change to grayscale
//		255,
//		GRAYColorspace,
//		0,
//		0,
//		0
//	);

	status = MagickWriteImages(magick_wand, "./67258.jpg", MagickTrue);
	MagickWandTerminus();
 
    return(0);
}