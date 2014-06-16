

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
    
    MagickWand *magick_wand, *pseudo_wand;
    char *filename;
        
    MagickWandGenesis();
    
    
    PixelWand *pixel_wand = NULL;
    pixel_wand = NewPixelWand();    
    PixelSetColor(pixel_wand, "white");
    
    
    magick_wand = NewMagickWand();



  	//status = DrawSetClipPath(internd->drawing_wand, clip_mask);
  
  
    int columns = 16;
    int rows = 16;
    
    status = MagickNewImage(magick_wand, columns, rows, pixel_wand);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    char *identify;
    identify = MagickIdentifyImage (magick_wand);

    //Never gets here

    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}