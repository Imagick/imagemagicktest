#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#include <wand/MagickWand.h>
    

int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;
    PixelWand *pixel_wand_input;
    PixelWand *pixel_wand_output;
    double hue, saturation, luminosity;
    double red, green, blue, alpha;

    char hslString[2028];
    char *inputColor = "rgb(158, 146, 130)";

    MagickWandGenesis();

    pixel_wand_input = NewPixelWand();

    if (PixelSetColor (pixel_wand_input, inputColor) == MagickFalse) {
        printf("Failed to set color");
        exit(-1);
    }

    PixelGetHSL(pixel_wand_input, &hue, &saturation, &luminosity);
    
    
    printf("hsl values are %.4f, %.4f, %.4f\n", hue, saturation, luminosity);
    
    sprintf(
        hslString,
        "hsl(%.4f, %.4f, %.4f)", 
        hue * 255,
        saturation * 255,
        luminosity * 255
    );

    

    pixel_wand_output = NewPixelWand();
    if (PixelSetColor(pixel_wand_output, hslString) == MagickFalse) {
        printf("Failed to set color");
        exit(-1);
    }

    red   = PixelGetRed(pixel_wand_output);
    green = PixelGetGreen(pixel_wand_output);
    blue  = PixelGetBlue(pixel_wand_output);
    
    
    printf("Input color: %s \n", inputColor);

    printf(
        "Final color: rgb(%.2f, %.2f, %.2f)\n", 
        red * 255,
        green * 255,
        blue * 255
    );


    MagickWandTerminus();
    MagickWandTerminus();
 
    return(0);
}