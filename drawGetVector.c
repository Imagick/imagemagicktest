#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>


char * outputFormat = "tiff";

void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
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

void drawClipTest(int extraClipping, int writeFile, char *filename) {
    
    MagickBooleanType status;
    
    PixelWand *background_color_wand;
    DrawingWand *drawing_wand;
    PixelWand *fill_color_wand, *stroke_color_wand;

    char *backgroundColor = "rgb(225, 225, 225)";
    char *strokeColor = "rgb(0, 0, 0)";
    char *fillColor = "DodgerBlue2";
    char * vector = NULL;
    
    drawing_wand = NewDrawingWand();

    stroke_color_wand = makePixelWand(strokeColor);
    DrawSetStrokeColor(drawing_wand, stroke_color_wand);
    fill_color_wand = makePixelWand(fillColor);
    DrawSetFillColor(drawing_wand, fill_color_wand);
    DrawSetStrokeOpacity(drawing_wand, 1);
    DrawSetStrokeWidth(drawing_wand, 2);

    DrawRectangle(drawing_wand, 100, 100, 400, 400);

    vector = DrawGetVectorGraphics(drawing_wand);
    
    printf("Vector %s", vector);





//    MagickWand *magick_wand;
//    
//	magick_wand = NewMagickWand();
//
//	background_color_wand = makePixelWand(backgroundColor);
//
//	status = MagickNewImage(magick_wand, 500, 500, background_color_wand);
//
//	if (writeFile) {
//		MagickSetImageFormat(magick_wand, outputFormat);
//	
//		MagickDrawImage(magick_wand, drawing_wand);
//	
//		status = MagickWriteImages(magick_wand, filename, MagickTrue);
//	
//		if (status == MagickFalse) {
//			ThrowWandException(magick_wand);
//		}
//	}

//	magick_wand = DestroyMagickWand(magick_wand);

    return;
}



int main(int argc,char **argv) {

    char filename[1024];
    
    MagickWandGenesis();

    drawClipTest(1, 1, filename);

    MagickWandTerminus();
    return (0);
}
