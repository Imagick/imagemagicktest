#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>

#include <wand/pixel-wand.h>
  
 
void ThrowWandException(MagickWand *wand) { 
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}
 
     
void makeImage(int number);

  
int main(int argc,char **argv) { 

    int i;  
   
    // http://man7.org/linux/man-pages/man3/mallopt.3.html
    // http://www.gnu.org/software/libc/manual/html_node/Hooks-for-Malloc.html
   
    for (i=0; i<16 ; i++) { 
        mallopt (M_PERTURB, i); 
        makeImage(i);
    }

    return (0);    
}     
      
void makeImage(int number) {
      
    MagickBooleanType status;
    
    MagickWand *pseudo_wand;
    PixelWand *pixel_wand;
        char filename[1000];
        
    int columns = 512 + number; 
    int rows = 512 + number; 

    MagickWandGenesis(); 
 
    pixel_wand = NewPixelWand();  
    PixelSetColor(pixel_wand, "blue");

    pseudo_wand = NewMagickWand(); 
    MagickSetImageBackgroundColor(pseudo_wand, pixel_wand);
     
    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }

    if (MagickReadImage(pseudo_wand, "gradient:rgba(255,0,0, 0.25)-rgb(255,0,0,1)") == MagickFalse) {
        printf("Failed to generate gradient\n");
        ThrowWandException(pseudo_wand);
    }

	status = MagickSetImageFormat(pseudo_wand, "png");

	/* No magick is going to happen */
	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(pseudo_wand);
	}

    sprintf(filename, "./output/gradientMemTest_%x.png", number);

    status = MagickWriteImages(pseudo_wand, filename, MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }
        
    DestroyMagickWand(pseudo_wand);
    MagickWandTerminus();
}