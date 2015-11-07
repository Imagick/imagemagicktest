#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>

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

void addImage(MagickWand *canvas, int offset, char *strokeColor) {
    MagickBooleanType status;
    MagickWand *pseudo_wand;
    DrawingWand *drawing_wand;
    PixelWand *fill_color_wand, *stroke_color_wand;

    int columns = 100;
    int rows = 100;

    char *fillColor = "black";
    char filename[1024];

    sprintf(filename, "./output/bug61806_%d.png", offset);
	drawing_wand = NewDrawingWand();

	DrawSetFontSize(drawing_wand, 96);

	stroke_color_wand = makePixelWand(strokeColor);
	DrawSetStrokeColor(drawing_wand, stroke_color_wand);

    fill_color_wand = makePixelWand(fillColor);
    DrawSetFillColor(drawing_wand, fill_color_wand);
    pseudo_wand = NewMagickWand();
    DrawSetStrokeWidth(drawing_wand, 1);

    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }

    if (MagickReadImage(pseudo_wand, "canvas:white") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }
    
    DrawSetFontWeight(drawing_wand, 100);
    
    
    status = MagickAnnotateImage(
    	pseudo_wand, drawing_wand, 
    	-50 + offset, 62, 0, 
    	"test"
    );

	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(pseudo_wand);
	}

	MagickScaleImage(pseudo_wand, 400, 400);

	status = MagickAddImage(canvas, pseudo_wand);
}

int main(int argc,char **argv) {

	MagickWand *canvas_wand;
	MagickWand *tmp_wand;
	DrawingWand *drawing_wand;
    MagickBooleanType status;
        char *family;

    MagickWand *pseudo_wand;

    MagickWandGenesis();
    
    drawing_wand = NewDrawingWand();

    status = DrawSetFontFamily(drawing_wand, "Nsdsds Mono asdsdasds");

    if (status == MagickFalse) {
        printf("Failed to setFontFamily\n");
    }
    else {
        printf("It's okay.\n");
    }

    family = DrawGetFontFamily(drawing_wand);
    

    printf("Family is now %s\n", family);
    
    PixelWand *pixel_wand = makePixelWand("red");
    
    DrawSetFillColor(drawing_wand, pixel_wand);

    DrawAnnotation(drawing_wand, 10, 20, "Hello there.");
    
    pseudo_wand = NewMagickWand();
    
    status = MagickSetSize(pseudo_wand, 300, 100);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }

    if (MagickReadImage(pseudo_wand, "canvas:white") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }
    
    MagickDrawImage(pseudo_wand, drawing_wand);
    
    
    MagickWriteImage(pseudo_wand, "./setFontFamily.png");
    
    MagickWandTerminus();
    return (0);
}
