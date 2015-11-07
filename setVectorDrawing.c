#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>

void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity);
     
    printf("description is %s \n", description);
     
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}

PixelWand *makePixelWand(char *string) {
	PixelWand *pixel_wand;
	pixel_wand = NewPixelWand();

	if (PixelSetColor (pixel_wand, string) == MagickFalse) {
		printf("Failed to set color");
		exit(-1);
	}

	return pixel_wand;
}



int main(int argc,char **argv) {

    PixelWand *stroke_color_wand;
    PixelWand *fill_color_wand;
    PixelWand *background_color_wand;
    MagickBooleanType status;
    DrawingWand *drawing_wand_src;
    DrawingWand *drawing_wand_dst;
    char *filename = "vector.png";

    char *vector;
    char encapsulatedGraphics[4096];

    MagickWandGenesis();
  
    drawing_wand_src = NewDrawingWand();

    stroke_color_wand = makePixelWand("red");
    fill_color_wand = makePixelWand("blue");
    DrawSetStrokeColor(drawing_wand_src, stroke_color_wand);
    DrawSetFillColor(drawing_wand_src, fill_color_wand);

    DrawCircle(drawing_wand_src, 50, 50, 100, 100);

    vector = DrawGetVectorGraphics(drawing_wand_src);


    drawing_wand_dst = NewDrawingWand();
    
    //This should work, but doesn't
    status = DrawSetVectorGraphics(drawing_wand_dst, vector);

    //This works, but isn't documented as needed.
    //sprintf(encapsulatedGraphics, "<root>%s</root>", vector);
    //status = DrawSetVectorGraphics(drawing_wand_dst, encapsulatedGraphics);


    if (status == MagickFalse) {
        printf("DrawSetVectorGraphics failed.\n");
        return(-1);
    }
    else {
        printf("DrawSetVectorGraphics succeeded.\n");
    }
    
    
    printf("Vector graphics is:\n");
    
    printf("%s", vector);
    
    MagickWand *magick_wand;
  
    magick_wand = NewMagickWand();

    background_color_wand = makePixelWand("white");

    status = MagickNewImage(magick_wand, 500, 500, background_color_wand);


    MagickSetImageFormat(magick_wand, "png");

    status = MagickDrawImage(magick_wand, drawing_wand_dst);

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }
    

    status = MagickWriteImages(magick_wand, filename, MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(magick_wand);
    }

    
    MagickWandTerminus();
    return (0);
}