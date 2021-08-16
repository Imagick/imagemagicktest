
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include <wand/MagickWand.h>

//#if defined (IM_MAGICKWAND_HEADER_STYLE_SEVEN)
#include <MagickWand/MagickWand.h>
//#elif defined (IM_MAGICKWAND_HEADER_STYLE_OLD)
//#  include <wand/magick-wand.h>
//#else
//#  include <wand/MagickWand.h>
//#endif
    
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