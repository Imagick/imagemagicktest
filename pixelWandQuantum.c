

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>


 
int main(int argc,char **argv) {
    
    int i;
    double blueValue;
    Quantum blueQuantum; 
   
    MagickWandGenesis();
    char * color;
    size_t version_number;
    char * versionString;

    PixelWand *pixel_wand = NULL;

    char *colors[] = {"pink", "purple", "red", "blue", "rgb(13, 13, 13)"};

    for (i=0; i<4 ; i++) {
        color = colors[i];
        
        pixel_wand = NewPixelWand();    
        PixelSetColor(pixel_wand, color);
    
        blueValue = PixelGetBlue(pixel_wand);
        blueQuantum = PixelGetBlueQuantum(pixel_wand);
 
        printf("Color %s \t Blue value is %f, quantum as decimal %d, as float %g\n", color, blueValue, blueQuantum, blueQuantum);
    }

    versionString = (char *)MagickGetVersion(&version_number);

    printf("Version is %s \n", versionString);
      
    MagickWandTerminus();
    
    return(0);
}