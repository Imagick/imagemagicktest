//GetImageProperty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    


void composite(int type) {
    MagickWand *magick_wand, *clone_wand;
    char filename[2048];
    
    magick_wand = NewMagickWand();
    MagickReadImage(magick_wand, "./pngtrans.png");
    clone_wand = CloneMagickWand(magick_wand);

    //MagickReduceNoiseImage(magick_wand, 2);
    //MagickDespeckleImage(magick_wand);
    
    MagickGaussianBlurImageChannel(magick_wand,
        DefaultChannels, 5, 2);
    

    MagickCompositeImageChannel(
        magick_wand,
        AlphaChannel,
        clone_wand,
        type,
        0, 0
    );

    sprintf(filename, "./pngtrans/pngtrans_%d_out.png", type);
    MagickWriteImage(magick_wand, filename);

}
 

int main(int argc,char **argv) {
    
    int x;

    MagickWandGenesis();
    
    
    for (x=0 ; x<50 ; x++) {
        composite(x);
    }

    MagickWandTerminus();
    
    return 0;
}

