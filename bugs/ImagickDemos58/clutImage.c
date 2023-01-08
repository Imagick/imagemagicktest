
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef IM7
#include <MagickWand/MagickWand.h>
#include <MagickWand/magick-image.h>
#else
#include <wand/MagickWand.h>
#include <wand/magick-image.h>
#endif

void process_clut(char *color)
{
    MagickWand *magick_wand;
    MagickWand *gradient_wand;
    char filename[2048];

    magick_wand = NewMagickWand();
    MagickReadImage(magick_wand, "./clut_drawn_image.png");

    gradient_wand = NewMagickWand();

    sprintf(filename, "./clut_gradient_image_%s.png", color);

    MagickReadImage(gradient_wand, filename);

    MagickClutImage(
        magick_wand,
        gradient_wand,
        BilinearInterpolatePixel
    );

    MagickSetImageFormat(magick_wand, "png");
    sprintf(filename, "./clut_magickwand_output_%s.png",  color);
    MagickWriteImage(magick_wand, filename);
}

int main(int argc,char **argv) {

    MagickWandGenesis();

    process_clut("blue");
    process_clut("transparent");

    MagickWandTerminus();

    return 0;
}

