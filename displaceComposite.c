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
    MagickWand *magick_wand_c;

    MagickWandGenesis();
    
//    $a = new Imagick('../a.png');
//    $b = new Imagick('../b.png');
//    $c = new Imagick('../c.png');


    magick_wand_a = NewMagickWand();
    status = MagickReadImage(magick_wand_a, "./displaceCompositeA.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_a);
    }
    
    magick_wand_b = NewMagickWand();
    status = MagickReadImage(magick_wand_b, "./displaceCompositeB.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_b);
    }
        
        
    magick_wand_c = NewMagickWand();
    status = MagickReadImage(magick_wand_c, "./displaceCompositeC.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand_c);
    }

    // $a->setImageVirtualPixelMethod(Imagick::VIRTUALPIXELMETHOD_TRANSPARENT);
    MagickSetImageVirtualPixelMethod(magick_wand_a, TransparentVirtualPixelMethod);


    // $a->setImageBackgroundColor(new ImagickPixel('none'));
    pixelWand = makePixelWand("none");
    status = MagickSetImageBackgroundColor(magick_wand_a, pixelWand);

    //    $a->setOption('compose:args', '300x53.033');
    MagickSetOption(magick_wand_a, "compose:args", "300x53.033");

    // $a->compositeImage($c, Imagick::COMPOSITE_DSTIN, 0, 0, Imagick::CHANNEL_ALPHA);
    // "COMPOSITE_DSTIN", DstInCompositeOp);
    status = MagickCompositeImageChannel(magick_wand_a, AlphaChannel, magick_wand_c, DstInCompositeOp, 0, 0);
    if (status == MagickFalse) {
        printf("Failed to composite image b");
        exit(-1); 
    }

    // $a->compositeImage($b, Imagick::COMPOSITE_DISPLACE, 0, 0);
    // "COMPOSITE_DISPLACE", DisplaceCompositeOp);
    status = MagickCompositeImage(magick_wand_a, magick_wand_b, DisplaceCompositeOp, 0, 0);
    if (status == MagickFalse) {
        printf("Failed to composite image b");
        exit(-1); 
    }
    
      
    status = MagickWriteImages(magick_wand_a, "displaceOutput.png", MagickTrue);

    // magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    printf("Finished - please compare displaceOutput.png with the result of:\n\n");
    
    printf("convert ./displaceCompositeA.png ./displaceCompositeB.png ./displaceCompositeC.png  -virtual-pixel transparent -channel rgba -alpha on -background transparent -define compose:args=300x53.033 -compose displace -composite ./displaceFinal.png\n");
    
    
    return(0);
}


