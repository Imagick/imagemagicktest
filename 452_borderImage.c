
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <MagickWand/MagickWand.h>


int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickWand *clone_wand;
    MagickBooleanType status;
    PixelWand *pixel_wand;
    CompositeOperator compositeOperator;

    MagickWandGenesis();

    magick_wand = NewMagickWand();

	status = MagickSetSize(magick_wand, 400, 300);
	if (status == MagickFalse) {
		printf("Failed to set size");
		exit(-1);
	}

	if (MagickReadImage(magick_wand, "LOGO:") == MagickFalse) {
		printf("Failed to set create psedoimage");
		exit(-1);
	}


	pixel_wand = NewPixelWand();


    if (PixelSetColor(pixel_wand, "rgba(255,255,255,0)") == MagickFalse) {
        printf("Failed to set color of pixel wand");
        exit(-1);
    }

    CompositeOperator operators[] = {
      AlphaCompositeOp,
      AtopCompositeOp,
      BlendCompositeOp,
      DstOverCompositeOp,
      OverCompositeOp,
      OverlayCompositeOp,
    };

	size_t number_of_ops = sizeof(operators)/sizeof(operators[0]);

	for (unsigned int i=0; i<number_of_ops; i+=1 ) {
		compositeOperator = operators[i];
		clone_wand = CloneMagickWand(magick_wand);
		if (MagickBorderImage(
			clone_wand, pixel_wand,
			50, 50, compositeOperator) == MagickFalse) {
			printf("Failed to border image for op index %d value %d", i, operators[i]);
			exit(-1);
		}

		char filename[1024];
		sprintf(filename, "./452_output_%d.jpg", i);
		MagickWriteImage(clone_wand, filename);
    }

    MagickWandTerminus();

    return 0;
}

