#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wand/MagickWand.h>

int main(int argc,char **argv) {

    PixelWand *pixel_wand;
    
    int red, green, blue;

    MagickWandGenesis();

    pixel_wand = NewPixelWand();  
    PixelSetColor(pixel_wand, "rgb(50%, 50%, 50%)");
    red   = PixelGetRedQuantum(pixel_wand);
    green = PixelGetGreenQuantum(pixel_wand);
    blue  = PixelGetBlueQuantum(pixel_wand);
    printf("50  percent is %d, %d, %d\n", red, green, blue);

   
    PixelSetColor(pixel_wand, "rgb(100%, 100%, 100%)");  
    red   = PixelGetRedQuantum(pixel_wand);
    green = PixelGetGreenQuantum(pixel_wand);
    blue  = PixelGetBlueQuantum(pixel_wand);
    printf("100 percent is %d, %d, %d\n", red, green, blue);
    
    
// Output on  CentOS-6.4-i386
// http://developer.nrel.gov/downloads/vagrant-boxes/CentOS-6.4-i386-v20131103.box
//50  percent is 32768, 32768, 32768
//100 percent is 65535, 65535, 65535
  
// Output on CentOS-6.4-x86_64
// http://developer.nrel.gov/downloads/vagrant-boxes/CentOS-6.4-x86_64-v20130427.box
//50  percent is 32767, 32767, 32767
//100 percent is 65535, 65535, 65535

    MagickWandTerminus();
    return (0);
}


// Both were compiled with:
//
// ./configure --with-quantum-depth=16 \
//           --with-magick-plus-plus=no \
//           --without-perl \
//           --disable-static \
//           --exec-prefix=/usr/sbin \
//           --disable-hdri \
//           --disable-docs \
//           --disable-openmp 

