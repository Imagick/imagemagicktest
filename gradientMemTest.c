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


void makeImage(int number);

int main(int argc,char **argv) {

    int i;

    //http://man7.org/linux/man-pages/man3/mallopt.3.html
    //http://www.gnu.org/software/libc/manual/html_node/Hooks-for-Malloc.html

    for (i=0; i<16 ; i++) {
        mallopt (M_PERTURB, i);
        makeImage(i);
    }

    return (0);
}
    
void makeImage(int number) {
    
    MagickBooleanType status;
    
    MagickWand *pseudo_wand;
    
    char filename[1000];
        
    int columns = 256 + number;
    int rows = 256 + number;

    MagickWandGenesis();

    pseudo_wand = NewMagickWand();
 
    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }

    if (MagickReadImage(pseudo_wand, "gradient:rgb(255,127,255)-rgb(128,0,255)") == MagickFalse) {
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