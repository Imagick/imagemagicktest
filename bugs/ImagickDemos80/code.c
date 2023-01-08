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


void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}


int main(int argc,char **argv) {

    MagickBooleanType status;


    MagickWand *magick_wand, *canvas_wand;
    MagickWand *channel1_wand, *channel2_wand, *channel3_wand;


    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, "Biter_500.png");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    int width = MagickGetImageWidth(magick_wand);
    int height = MagickGetImageHeight(magick_wand);

    // Transform the image to the color space that we're going to separate
    // the channel in.
//    $imagick->transformImageColorspace($colorspace);

    channel1_wand = NewMagickWand();
    channel1_wand = CloneMagickWand(magick_wand);
#ifdef IM7
    MagickSeparateImage(channel1_wand, RedChannel);
#else
    MagickSeparateImageChannel(channel1_wand, RedChannel);
#endif

    channel2_wand = NewMagickWand();
    channel2_wand = CloneMagickWand(magick_wand);
    #ifdef IM7
        MagickSeparateImage(channel2_wand, GreenChannel);
    #else
        MagickSeparateImageChannel(channel2_wand, GreenChannel);
    #endif

    channel3_wand = NewMagickWand();
    channel3_wand = CloneMagickWand(magick_wand);
    #ifdef IM7
        MagickSeparateImage(channel3_wand, BlueChannel);
    #else
        MagickSeparateImageChannel(channel3_wand, BlueChannel);
    #endif

    // Create an empty canvas that we will use to recombine the separate images.
    canvas_wand = NewMagickWand();

    status = MagickSetSize(canvas_wand, width * 2, height * 2);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    if (MagickReadImage(canvas_wand, "canvas:black") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(canvas_wand);
    }

    status = MagickSetImageColorspace(canvas_wand, RGBColorspace);



#ifdef IM7
    // Copy the individual channels into the canvas.
    MagickCompositeImage(canvas_wand, channel1_wand, CopyRedCompositeOp, MagickTrue, 0, 0);
    MagickCompositeImage(canvas_wand, channel1_wand, CopyRedCompositeOp, MagickTrue, width, 0);

    MagickCompositeImage(canvas_wand, channel2_wand, CopyGreenCompositeOp, MagickTrue, 0, 0);
    MagickCompositeImage(canvas_wand, channel2_wand, CopyGreenCompositeOp, MagickTrue, 0, height);

    MagickCompositeImage(canvas_wand, channel3_wand, CopyBlueCompositeOp, MagickTrue, 0, 0);
    MagickCompositeImage(canvas_wand, channel3_wand, CopyBlueCompositeOp, MagickTrue, width, height);
#else
    // Copy the individual channels into the canvas.
    MagickCompositeImage(canvas_wand, channel1_wand, CopyRedCompositeOp, 0, 0);
    MagickCompositeImage(canvas_wand, channel1_wand, CopyRedCompositeOp, width, 0);

    MagickCompositeImage(canvas_wand, channel2_wand, CopyGreenCompositeOp, 0, 0);
    MagickCompositeImage(canvas_wand, channel2_wand, CopyGreenCompositeOp, 0, height);

    MagickCompositeImage(canvas_wand, channel3_wand, CopyBlueCompositeOp, 0, 0);
    MagickCompositeImage(canvas_wand, channel3_wand, CopyBlueCompositeOp, width, height);
#endif








#ifdef IM7
    status = MagickWriteImages(canvas_wand, "output_im7.png", MagickTrue);
#else
    status = MagickWriteImages(canvas_wand, "output_im6.png", MagickTrue);
#endif

    if (status == MagickFalse) {
        ThrowWandException(canvas_wand);
    }

    magick_wand = DestroyMagickWand(magick_wand);
    magick_wand = DestroyMagickWand(canvas_wand);

    MagickWandTerminus();

    return(0);
}