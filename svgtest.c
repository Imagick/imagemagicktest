



#include <stdio.h>
#include <stdlib.h>
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
    
    MagickWand *magick_wand;
    
    char *svg =  
    "<?xml version=\"1.0\" encoding=\"utf-8\"?> \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"> \
<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\" width=\"158px\" height=\"92px\" viewBox=\"0 0 158 92\" enable-background=\"new 0 0 158 92\" xml:space=\"preserve\"> \
<text transform=\"matrix(1 0 0 1 32 58)\" font-family=\"Lobster\" font-style=\"normal\" font-size=\"20px\" font-weight=\"400\">Lobster</text> \
</svg>";
     
     
     
    
    magick_wand = NewMagickWand();
    
    status = MagickReadImageBlob(magick_wand, svg, strlen(svg));



    

    status = MagickWriteImages(magick_wand, "svg.out.png", MagickTrue);
    
    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
        
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return(0);
}



 