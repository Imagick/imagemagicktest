#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>


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
  
    MagickWand *magick_wand;
    char *filename = "./output/memTest.png";
    PixelWand *stroke_color_wand;
    MagickWandGenesis();
    stroke_color_wand = makePixelWand("red");
    magick_wand = NewMagickWand();
    
    MagickNewImage(magick_wand, 400, 200, stroke_color_wand);
    MagickSetImageFormat(magick_wand, "png");
    MagickThumbnailImage(magick_wand, 50, 25);
    MagickWriteImages(magick_wand, filename, MagickTrue);

    MagickWandTerminus();
    return (0);
}
