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


void borkTheStack(int number) {

    int x;
    
    int *borking;
    int size = 200000;
    
    
    borking = malloc(sizeof(int) * 200000);
    
    for (x=0 ; x<size ; x++) {
        borking[x] = number + 0xcdcdcdcd;
    }

    //free(borking);
}
  


void makeImage(int number);

int main(int argc,char **argv) {
    
    makeImage(0);
     
//    int x;
//    
//    for(x=0 ; x<30 ; x++) {
//        makeImage(x);
//    }
    
    return (0);
}
    
void makeImage(int number) {
    
    MagickBooleanType status;
    
    MagickWand *pseudo_wand;
    
    char filename[1000];
        
    int columns = 127 + number;
    int rows = 400 + number;

    sprintf(filename, "gradientMemTest_%d.png", number);

    /*
    Read an image.
    */
    MagickWandGenesis();
   
    borkTheStack(number);
   
    pseudo_wand = NewMagickWand();

    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }

//    printf("Step 1");

    if (MagickReadImage(pseudo_wand, "gradient:black-rgb(128,0,255)") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }

//    if (MagickReadImage(pseudo_wand, "xc:pink") == MagickFalse) {
//        printf("Goodbye\n");
//        ThrowWandException(pseudo_wand);
//    }

    PixelWand *tint_wand, *opacity_wand;

	tint_wand = NewPixelWand();
	PixelSetColor(tint_wand, "rgb(100,0,100)");

    opacity_wand = NewPixelWand();
    PixelSetColor(opacity_wand, "rgba(128,0,128,0.5)");

    status = MagickTintImage(pseudo_wand, tint_wand, opacity_wand);

    if (status == MagickFalse) {
		printf("Failed to MagickTintImage");
		ThrowWandException(pseudo_wand);
	}


    //printf("Step 2");

	status = MagickSetImageFormat(pseudo_wand, "png");

	/* No magick is going to happen */
	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(pseudo_wand);
	}

//    printf("Step 3");


    

    status = MagickWriteImages(pseudo_wand, filename, MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }
        
    DestroyMagickWand(pseudo_wand);
    MagickWandTerminus();
}