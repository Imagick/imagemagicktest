#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    

int main(int argc,char **argv) {
    MagickWand *magick_wand;

    MagickWandGenesis();

    magick_wand = NewMagickWand();
    MagickReadImage(magick_wand, "./images/test_cmyk.pdf");
    MagickSetImageFormat(magick_wand, "png");
    MagickWriteImage(magick_wand, "./test_cmyk.png");

    magick_wand = NewMagickWand();
    MagickReadImage(magick_wand, "./images/test_rgb.pdf");
    MagickSetImageFormat(magick_wand, "png");
    MagickWriteImage(magick_wand, "./test_rgb.png");

    MagickWandTerminus();
 
    return(0);
}

// convert test_cmyk.pdf out_convert_cmyk.png