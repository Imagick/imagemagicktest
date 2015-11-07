#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>


static void printBits(void *c, size_t n)
{
  unsigned char *t = c;
  if (c == NULL)
    return;
  while (n > 0) {
    --n;
    printf("%02x", t[n]);
  }
  printf("\n");
}

   
int main(int argc,char **argv) {
    MagickWandGenesis();
      
    size_t version_number;
    char * versionString;
    double unity = 1.0;
    double red;
    char * color;
    int i; 

    PixelWand *pixel_wand = NULL;
    
    char *colors[] = {"red", "rgb(255, 0, 0)", "#ff0000", "rgb(100.0%, 0.0%, 0.0%)"};

    pixel_wand = NewPixelWand();
        
    for (i=0; i<((sizeof colors) / (sizeof color)) ; i++) {
    
        color = colors[i];
            
        PixelSetColor(pixel_wand, color);

        red = PixelGetRed(pixel_wand);

        printf("color '%s' %f bits are: ", color, red);
        printBits(&red, sizeof red);
    }
    
    printf("unity %f bits are: ", unity);
    printBits(&unity, sizeof unity);
    
    versionString = (char *)MagickGetVersion(&version_number);
    printf("Version is %s \n", versionString);
      
    MagickWandTerminus();
    
    return(0);
}