//GetImageProperty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>


int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickWand *gradient_wand;
    MagickWandGenesis();

    magick_wand = NewMagickWand();
    //MagickReadImage(magick_wand, "./blurred_shape.jpg");
    //MagickReadImage(magick_wand, "./blurred_shape.png");
    MagickReadImage(magick_wand, "./clutImageSrc.png");

    gradient_wand = NewMagickWand();
    MagickReadImage(gradient_wand, "./gradient_border.png");

//    MagickSetImageInterpolateMethod(
//        magick_wand,
//        IntegerInterpolatePixel
//    );
//
//    MagickSetImageInterpolateMethod(
//        gradient_wand,
//        IntegerInterpolatePixel
//    );

    //MagickTransformImageColorspace(magick_wand, GRAYColorspace);

    //MagickSetImageAlphaChannel(magick_wand, DeactivateAlphaChannel);
   
    MagickClutImageChannel(
        magick_wand,
        RedChannel | BlueChannel | GreenChannel | AlphaChannel,
        gradient_wand
    );

    MagickSetImageFormat(magick_wand, "png");

    MagickWriteImage(magick_wand, "./clut_outputassdsd.png");
    MagickWandTerminus();

    return 0;
}

