//GetImageProperty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>


int main(int argc,char **argv) {
    MagickWand *magick_wand_background;
    MagickWand *magick_wand_foreground;
    MagickWandGenesis();
    
    magick_wand_background = NewMagickWand();
    magick_wand_foreground = NewMagickWand();

    MagickReadImage(magick_wand_background, "magick:logo");
    MagickReadImage(magick_wand_foreground, "magick:rose");
 
    MagickSetGravity(magick_wand_background, CenterGravity);
    MagickSetGravity(magick_wand_foreground, CenterGravity);
 
    MagickCompositeImage(
        magick_wand_background,
        magick_wand_foreground,
        AtopCompositeOp,
        0, 0
    );
    
    MagickSetFormat(magick_wand_background, "png");

    MagickWriteImage(magick_wand_background, "./output/gravity.png");
    MagickWandTerminus();

    return 0;
}

