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
	int c;
	int x = 48;
	char filename[1024];

	char *colors[] = {"red", "white", "none", "rgba(255, 0, 255, 0)", "black"};

    MagickWandGenesis();
    
    
    

    for (c=0; c<sizeof(colors)/sizeof(colors[0]); c++) {
		canvas_wand = NewMagickWand();
		MagickSetImageFormat(canvas_wand, "gif");
		addImage(canvas_wand, x * 2, colors[c]);

		sprintf(filename, "./output/61806_%s.gif", colors[c]);
		tmp_wand = MagickDeconstructImages(canvas_wand);
		if (c == 3) {
			MagickWriteImages(tmp_wand, "./output/61805_transparent_magenta.gif", MagickTrue);
		}
		else {
			MagickWriteImages(tmp_wand, filename, MagickTrue);
		}
    }
    
    MagickWandTerminus();
    return (0);
}
