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

int main(int argc,char **argv) {
    
    MagickBooleanType status;
    
    MagickWand *magick_wand;
    MagickWand *hsl_wand;

    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, "./Biter_500.jpg");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
   
    hsl_wand = CloneMagickWand(magick_wand);
    
    if (hsl_wand == NULL) {
        printf("Failed to CloneMagickWand");
        ThrowWandException(magick_wand);
    }

    status = MagickSeparateImageChannel(magick_wand, RedChannel);
    
    status = MagickWriteImages(magick_wand, "channel1.rgb_before_%d.jpg", MagickTrue);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }


    //status = MagickSetImageColorspace(hsl_wand, HSLColorspace);
    status = MagickTransformImageColorspace(hsl_wand, HSLColorspace);
    if (status == MagickFalse) {
        printf("Failed to MagickSetImageColorspace");
        ThrowWandException(magick_wand);
    }
    
    
    status = MagickSeparateImageChannel(hsl_wand, BlueChannel);
    if (status == MagickFalse) {
        printf("Failed to MagickSeparateImageChannel");
        ThrowWandException(magick_wand);
    }

    status = MagickWriteImages(magick_wand, "channel1.rgb__after_%d.jpg", MagickTrue);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    
    status = MagickWriteImages(hsl_wand, "channel1.hsl_%d.jpg", MagickTrue);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
        
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}