#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>

int main(int argc,char **argv) {

	MagickWand *canvas_wand;
	MagickWand *coalesced_wand;
	MagickWand *current_wand;
	MagickWand *output_wand;
	
	MagickWand *tmp_wand;
	int c;
	int x = 48;
	char filename[1024];

	char *colors[] = {"red", "white", "none", "rgba(255, 0, 255, 0)", "black"};

    MagickWandGenesis();
    
    canvas_wand = NewMagickWand();
    output_wand = NewMagickWand();
    
    MagickReadImage(canvas_wand, "./SeriouslyBurned.gif");

    coalesced_wand = MagickCoalesceImages(canvas_wand);

    MagickResetIterator(coalesced_wand);

	/* Loop all images to make sure they have a format */
	while (MagickNextImage(coalesced_wand)) {
	    current_wand = MagickGetImage(coalesced_wand);
		MagickAddImage(output_wand, current_wand);
	}
 
    MagickSetImageFormat(output_wand, "gif");
    MagickWriteImages(output_wand, "./output/gifSegfault/test.gif", MagickTrue);
    
    MagickWandTerminus();
    return (0);
}

