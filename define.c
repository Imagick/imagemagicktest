
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    
    
#if defined(MagickQuantumRange)
	#error yes it is defined
#else 
	#error no it is NOT defined
#endif


int main(int argc,char **argv) {
	MagickWand *magick_wand;
	MagickBooleanType status;

	MagickWandGenesis();
	magick_wand = NewMagickWand();

	MagickWandTerminus();
 
    return(0);
}