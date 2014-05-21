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
    char filename[1024];
    
    if (argc != 2) {
        (void) fprintf(stdout,"Usage: %s image \n",argv[0]);
        exit(0);
    }
    
    /*
    Read an image.
    */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    /*
    Turn the images into a thumbnail sequence.
    */
  
    int columns = MagickGetImageWidth(magick_wand);
    int rows = MagickGetImageHeight(magick_wand);
    
  
    pseudo_wand = NewMagickWand();

    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    if (MagickReadImage(pseudo_wand, "gradient:rgba(255,255,255,0)-white") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }
    
    


    MagickCompositeImage(magick_wand, pseudo_wand, BlendCompositeOp, 0, 0);

    sprintf(filename, "%s.correct.png", argv[1]);
    
    status = MagickWriteImages(magick_wand, filename, MagickTrue);
    
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    status = MagickSetImageOpacity(magick_wand, 0.5);

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    
    sprintf(filename, "%s.wrong.png", argv[1]);
    

    status = MagickWriteImages(magick_wand, filename, MagickTrue);
    
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
        
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}