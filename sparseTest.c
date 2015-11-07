#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// Use this one for IM7
#include <MagickWand/MagickWand.h>

// Use this one for IM6
//#include <wand/MagickWand.h>

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
  
    MagickWand *magick_wand;
    char *filename;
    PixelWand *stroke_color_wand;
    MagickBooleanType status;
    int num_elements;
#if MagickLibVersion < 0x700    
    long channel = RedChannel | GreenChannel | BlueChannel | AlphaChannel;
#else
    ChannelType channel = RedChannel | GreenChannel | BlueChannel | AlphaChannel;
    //ChannelType channel = RedChannel | GreenChannel | BlueChannel;
#endif
    
    double double_array[] = {
        150.000000, 50.000000, 
        1.000000, 0.000000, 0.000000, 1.0,
        50.000000, 400.000000, 
        0.000000, 0.000000, 1.000000, 0.5,
        350.000000,  300.000000, 
        0.000000, 1.000000, 0.000000, 1.0,
        400.000000,  100.000000, 
        1.000000,  1.000000, 0.000000, 0.1,
    };

    num_elements = sizeof(double_array) / sizeof(double);

    MagickWandGenesis();

    stroke_color_wand = makePixelWand("rgba(255, 255, 255, 1)");
    magick_wand = NewMagickWand();

    MagickNewImage(magick_wand, 500, 500, stroke_color_wand);

#if MagickLibVersion >= 0x700
    printf("I choose you IM 7 \n");
    filename = "./sparseTest_7.png";
    MagickSetImageChannelMask(magick_wand, channel);
    status = MagickSparseColorImage(
        magick_wand,
        BilinearColorInterpolate,
        num_elements,
        double_array
    );
#else
    printf("I choose you IM 6 \n");
    filename = "./sparseTest_6.png";
    status = MagickSparseColorImage(
        magick_wand, 
        channel,
        BilinearColorInterpolate,
        num_elements,
        double_array
    );
#endif

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    MagickWriteImages(magick_wand, filename, MagickTrue);
    MagickWandTerminus();
    
    printf("fin\n");
    return (0);
}
