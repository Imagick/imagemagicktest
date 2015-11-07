#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    

int main(int argc,char **argv) {
	MagickWand *magick_wand;
	MagickBooleanType status;

	MagickWandGenesis();
	magick_wand = NewMagickWand();

	int elements = 6;
	double samples[6];

	char factor[36];
	char outputFilename[500];

    double sizes[] = {1, 2, 4};
    
    int i = 0, j = 0;
    int h1, v1;
    int h2, v2;
    int h3, v3;
    
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
        
            h1 = sizes[i];
            v1 = sizes[i];
        
            for ( h2=1 ; h2<=2; h2++){
                for ( v2=1 ; v2<=2; v2++){
                    for ( h3=1 ; h3<=2; h3++){
                        for ( v3=1 ; v3<=2; v3++){
                            sprintf(
                                factor,
                                "%dx%d_%dx%d_%dx%d",
                                h1, v1,
                                h2, v2,
                                h3, v3
                            );
                            
                            sprintf(
                                outputFilename,
                                "./output/smapleOut_%s.jpg",
                                factor
                            );
                            
                            samples[0] = h1;
                            samples[1] = v1;
                            samples[2] = h2;
                            samples[3] = v2;
                            samples[4] = h3;
                            samples[5] = v3;

    status = MagickReadImage(magick_wand, "./Biter_500.jpg");
    MagickSetSamplingFactors(magick_wand, 6, samples);
    status = MagickWriteImage(magick_wand, outputFilename);


                        }
                    }
                }
            }
        }
    }
    int samplings[][3] = {
        {4,4,4},
        {4,4,0},
        {4,4,1},
        {4,4,0},
        {4,2,2},
        {4,2,0},
        {4,4,0},
        {4,2,1},
        {4,1,1},
        {4,2,2},
        {4,1,0},
        {4,2,0}
    };
    
    for (i=0 ; i<10 ; i++) {
    
        samples[0] = samplings[i][0];
        samples[1] = samplings[i][1];
        samples[2] = samplings[i][2];
        
    
        sprintf(
            outputFilename,
            "./output/fff%d_%d_%d.jpg",
            samplings[i][0],
            samplings[i][1],
            samplings[i][2]
        );
        
    
        status = MagickReadImage(magick_wand, "./Biter_500.jpg");
        MagickSetSamplingFactors(magick_wand, 3, samples);
        status = MagickWriteImage(magick_wand, outputFilename);
    }
    
    

	//This is a color image
	
	MagickWandTerminus();
 
    return(0);
}