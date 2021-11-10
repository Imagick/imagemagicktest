#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <MagickWand/MagickWand.h>
#include <MagickWand/pixel-wand.h>

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

void makeImage(void) {
      
    MagickBooleanType status;
    
    MagickWand *canvas_wand;
    MagickWand *mask_wand;

    PixelWand *pixel_wand;
    PixelWand *stroke_color_wand;
    PixelWand *fill_color_wand;
    PixelWand *background_color_wand;
    DrawingWand *drawing_wand;

    MagickWandGenesis(); 

    canvas_wand = NewMagickWand();

    status = MagickSetSize(canvas_wand, 640, 480);
    if (status == MagickFalse) {
        ThrowWandException(canvas_wand);
    }

    printf("Create the canvas\n");
    if (MagickReadImage(canvas_wand, "magick:logo") == MagickFalse) {
        printf("Failed to generate canvas\n");
        ThrowWandException(canvas_wand);
    }
	status = MagickSetImageFormat(canvas_wand, "png");
	/* No magick is going to happen */
	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(canvas_wand);
	}

    printf("Create the mask\n");
    mask_wand = NewMagickWand();
    background_color_wand = makePixelWand("white");
    status = MagickNewImage(mask_wand, 640, 480, background_color_wand);

    drawing_wand = NewDrawingWand();
    stroke_color_wand = makePixelWand("black");
    fill_color_wand = makePixelWand("black");
    DrawSetStrokeColor(drawing_wand, stroke_color_wand);
    DrawSetFillColor(drawing_wand, fill_color_wand);
    DrawEllipse(drawing_wand,
        320,
        240,
        215,
        120,
        0,
        360
    );
    status = MagickDrawImage(mask_wand, drawing_wand);


    printf("setImageMask($mask, Imagick::PIXELMASK_WRITE);\n");
    status = MagickSetImageMask(
        canvas_wand,
        WritePixelMask,
        mask_wand
    );

    printf("brightnessContrastImage(-20, 10, Imagick::CHANNEL_ALL);\n");
    status = MagickBrightnessContrastImage(canvas_wand, -20, 10);

    printf("$imagick->unsharpMaskImage(1, 0.5, 1, 0);\n");
    status = MagickUnsharpMaskImage(
        canvas_wand,
        1,
        0.5,
        1,
        0
    );

    printf("write image output\n");

    status = MagickWriteImages(canvas_wand, "./output/bug503.png", MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(canvas_wand);
    }
        
    DestroyMagickWand(canvas_wand);
    DestroyMagickWand(mask_wand);
    MagickWandTerminus();
}


int main(int argc,char **argv) {
    makeImage();
    return (0);
}