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
 
    MagickWand *magick_wand;
    MagickBooleanType status;
    unsigned long range;
    double kernel[] = { -0.70,0,0.70,-0.70,0,0.70,-0.70,0,0.70 };
    
    ExceptionInfo exception;

    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, "./stack.jpg");
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    
    InitImageMagickOpenCL(MAGICK_OPENCL_OFF, NULL, NULL, &exception);

    //status = MagickTransformImageColorspace(magick_wand, GRAYColorspace);

    MagickGetQuantumRange(&range);
    
    MagickSetOption(magick_wand, "convolve:scale", "0.1");
    
    status = MagickSetImageArtifact(magick_wand, "convolve:scale", "0.1");
//    if (status == MagickFalse) {
//        printf("boo");
//        exit(-1);
//    }  

    //status = MagickSetImageBias(magick_wand, 0.5);

    
    //Not sure if this is meant to be a quantum value
    //It makes no difference
    status = MagickSetImageBias(magick_wand, 0.5);
    
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    //status = MagickConvolveImage(magick_wand, 3, kernel);
     
    
    
    status = MagickConvolveImageChannel(magick_wand, DefaultChannels, 3, kernel);

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    
    status = MagickWriteImages(magick_wand, "setImageBias_%d.jpg", MagickTrue);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}