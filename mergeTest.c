#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    

void foo(int x) {
	MagickWand *magick_wand;
	MagickWand *magick_wand_green;

    char filename[1024];
	MagickWand *merged;
	MagickBooleanType status;

	magick_wand = NewMagickWand();
	magick_wand_green = NewMagickWand();

	//This is a color image
	status = MagickReadImage(magick_wand, "./Biter_500.jpg");
	status = MagickReadImage(magick_wand_green, "./greenDiscAlpha.png");
    status = MagickAddImage(magick_wand, magick_wand_green);
    
    
    
//      CoalesceLayer,
//      CompareAnyLayer,
//      CompareClearLayer,
//      CompareOverlayLayer,
//      DisposeLayer,
//      OptimizeLayer,
//      OptimizeImageLayer,
//      OptimizePlusLayer,
//      OptimizeTransLayer,
//      RemoveDupsLayer,
//      RemoveZeroLayer,
//      CompositeLayer,
//      MergeLayer,
//      FlattenLayer,
//      MosaicLayer,
//      TrimBoundsLayer
    
    sprintf(filename, "./mergeTest_%d.png", x);
    
    merged = MagickMergeImageLayers(magick_wand, x);
    MagickSetImageFormat(magick_wand, "png");
	status = MagickWriteImages(merged, filename, MagickTrue);
 
}

int main(int argc,char **argv) {

    int x;
    
    MagickWandGenesis();

    //for (x=0; x<TrimBoundsLayer ; x++) {
        foo(TrimBoundsLayer);
    //}
    
    MagickWandTerminus();
    return(0);
}