#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>


int main(int argc,char **argv) {
	MagickWand *canvas_wand;
	double *metrics;
	DrawingWand *drawing_wand;
	int i = 0;
	char *text = "Hello \nHello";

    char *metricText[] = {
        "character width",//                            0 character width
        "character height",//                          1 character height
        "ascender",//                                  2 ascender
        "descender",//                                 3 descender
        "text width",//                                4 text width
        "text height",//                               5 text height
        "maximum horizontal advance",//                6 maximum horizontal advance
        "bounding box: x1",//                          7 bounding box: x1
        "bounding box: y1",//                          8 bounding box: y1
        "bounding box: x2",//                          9 bounding box: x2
        "bounding box: y2",//                         10 bounding box: y2
        "origin: x",//                                11 origin: x
        "origin: y",//                                12 origin: y
    };

    MagickWandGenesis();
    drawing_wand = NewDrawingWand();
    canvas_wand = NewMagickWand();
    MagickReadImage(canvas_wand, "magick:logo");

    metrics = MagickQueryFontMetrics(canvas_wand, drawing_wand, text);
    printf("Single line\n");
    for (i=7; i<=10; i++) {
        printf("%s : %f \n", metricText[i], metrics[i]);
    }

    metrics = MagickQueryMultilineFontMetrics(canvas_wand, drawing_wand, text);
    printf("Multi-line\n");
    for (i=7; i<=10; i++) {
        printf("%s : %f \n", metricText[i], metrics[i]);
    }

    MagickWandTerminus();
    return (0);
}
