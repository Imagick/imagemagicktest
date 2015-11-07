#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define IM7 

#ifdef IM7
#include <MagickWand/MagickWand.h>
#else
#include <wand/MagickWand.h>
#endif

int main(int argc,char **argv) {

    MagickWand *small_sample_wand;
    MagickWand *original_wand;
    MagickWand *comparison_wand;
    
    MagickWand *tmp_wand;
    int c;
    int x = 48;
    char filename[1024];
    
    MetricType metric = AbsoluteErrorMetric;
    double similarity_threshold = 1.0;

    RectangleInfo best_match_offset;
    double similarity = -1;

    MagickWandGenesis();
    
    original_wand = NewMagickWand();
    
    //$imagick->newPseudoImage(640, 480, "magick:logo");
    MagickSetSize(original_wand, 640, 480);
    MagickReadImage(original_wand, "magick:logo");

    //$imagick->adaptiveResizeImage(100, 100, true);
    MagickAdaptiveResizeImage(original_wand, 100, 75);
    //$imagick->setImageAlphaChannel(Imagick::ALPHACHANNEL_DEACTIVATE);
    MagickSetImageAlphaChannel(original_wand, DeactivateAlphaChannel);

    small_sample_wand = CloneMagickWand(original_wand);

    MagickCropImage(small_sample_wand, 25, 25, 50, 50);
    MagickSetImageFormat(small_sample_wand, "png");
    MagickSetImagePage(small_sample_wand, 25, 25, 0, 0);
    MagickVignetteImage(small_sample_wand, 0.25, 0.75, 3, 3);

    comparison_wand = MagickSimilarityImage(
        original_wand,
        small_sample_wand,
#ifdef IM7
        metric,
        similarity_threshold,
#endif

        &best_match_offset, 
        &similarity
    );
 
    printf("Similarity is %f \n", similarity);

    //For IM7 compiled from master output is:
    //Similarity is 390.000000
    //For ImageMagick-6.9.2-5 output is:
    //Similarity is 0.558027

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

