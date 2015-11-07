

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>


void testSimilar(char *color1, char *color2, float distance, int expectedResult) {

    float fuzz ;
    int status;

    PixelWand *pixel_wand_1 = NULL;
    PixelWand *pixel_wand_2 = NULL;

    pixel_wand_1 = NewPixelWand();    

    PixelSetColor(pixel_wand_1, color1);

    pixel_wand_2 = NewPixelWand();    
    PixelSetColor(pixel_wand_2, color2);

    fuzz = distance / sqrt(3);

    status = IsPixelWandSimilar(pixel_wand_1, pixel_wand_2, fuzz * QuantumRange);
    
    //Removing the quantum range makes the first test work, and the others fail... 
    //status = IsPixelWandSimilar(pixel_wand_1, pixel_wand_2, fuzz );

    printf("Expected %d actual %d for colors %s %s distance %f \n", expectedResult, status, color1, color2, distance);
}

#warning "shits fucked up yo" 

int main(int argc,char **argv) {

    MagickWandGenesis();

    //Distance between points is 9.899494936611665
    testSimilar("rgba(0, 0, 0, 1)", "rgba(7, 7, 0, 1)", 9, 0);
    testSimilar("rgba(0, 0, 0, 1)", "rgba(7, 7, 0, 1)", 10, 1);
    
    //Distance between points is 10
    testSimilar("black", "rgba(10, 0, 0, 1.0)", 11, 1);

    //Distance between points is 10
    testSimilar("rgb(245, 0, 0)", "rgb(255, 0, 0)", 10, 1);

    MagickWandTerminus();
    
    return(0);
}