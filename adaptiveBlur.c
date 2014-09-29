#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    
 
void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}
 

void foo() {

   MagickWand *magick_wand;
    MagickBooleanType status;
    //unsigned char *image_contents;
    //size_t image_size;
    
    long channel = DefaultChannels;
    double radius, sigma, threshold;

    radius = 5;
    sigma = 1;
    threshold = 0.5;

    mallopt (M_PERTURB, 0x12); 

    MagickWandGenesis();
    magick_wand = NewMagickWand();
    //status = MagickReadImage(magick_wand, "./Biter_500.jpg");
    status = MagickReadImage(magick_wand, "./separate_HSL_1.gif");

    status = MagickSelectiveBlurImageChannel(magick_wand, channel, radius, sigma, threshold);

    

//    image_contents = MagickGetImageBlob(magick_wand, &image_size);
//    printf("Image size is %lu\n", image_size);
 
    MagickWandTerminus();
    

}

int main(int argc,char **argv) {

    foo();
 
    return(0);
}