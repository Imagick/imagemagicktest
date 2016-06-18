#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <wand/MagickWand.h>
 
#define IM7 

#ifdef IM7
#include <MagickWand/MagickWand.h>
#else
#include <wand/MagickWand.h>
#endif
 
 
int main(int argc,char **argv) {

    MagickWand *original_wand;
    MagickWandGenesis(); 
    original_wand = NewMagickWand();
    
    
    
    MagickReadImage(original_wand, "http://any/url/here");
    
    printf("wat\n");
    return (0);
    
    MagickSetLastIterator(original_wand);

    MagickSetImageFormat(original_wand, "png");
    MagickWriteImage(original_wand, "./im147.png");
    
    MagickWandTerminus();
    return (0);
}

