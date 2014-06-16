#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>


char * outputFormat = "png";

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
    char *clip_mask;
    char *clip_mask_duplicate;
    int x;
    
    char *backgroundColor = "rgb(225, 225, 225)";
    char *strokeColor = "rgb(0, 0, 0)";
    char *fillColor = "DodgerBlue2";
    PixelWand *destroyed_wand;

	//	$draw = new \ImagickDraw();
    drawing_wand = NewDrawingWand();

	//    $draw->setStrokeColor($strokeColor);
    stroke_color_wand = makePixelWand(strokeColor);
    DrawSetStrokeColor(drawing_wand, stroke_color_wand);
    //destroyed_wand = DestroyPixelWand (stroke_color_wand);
    //clearWand(stroke_color_wand);
    
    //    $draw->setFillColor($fillColor);
    fill_color_wand = makePixelWand(fillColor);
    DrawSetFillColor(drawing_wand, fill_color_wand);
    //destroyed_wand = DestroyPixelWand (fill_color_wand);
    //clearWand(fill_color_wand);
    
    
    //    $draw->setStrokeOpacity(1);
   	DrawSetStrokeOpacity(drawing_wand, 1);
    //    $draw->setStrokeWidth(2);
    DrawSetStrokeWidth(drawing_wand, 2);


	//    $draw->pushClipPath($clipPathName);
	DrawPushClipPath(drawing_wand, "testClipPath");

	//    $draw->rectangle(0, 0, 250, 250);
	DrawRectangle(drawing_wand, 0, 0, 250, 250);


	if (extraClipping) {
		for (x=0 ; x<1000 ; x++) {
			int posX = (x * 23 * 53 ) % 500;
			int posY = (x * 7) % 500;
			DrawRectangle(drawing_wand, posX, posY, posX + 10, posY + 10);
		}
	} 

	//    $draw->popClipPath();
	DrawPopClipPath(drawing_wand);

	//DrawSetClipRule(internd->drawing_wand, fill_rule);
	status = DrawSetClipPath(drawing_wand, "testClipPath");


	if (status == MagickFalse) {
		printf("Failed to DrawSetClipPath ");
		exit(-1); 
	}
 
	//    $draw->rectangle(200, 200, 300, 300);
	//This is the only thing that should be drawn into the final image
    DrawRectangle(drawing_wand, 100, 100, 400, 400);

    MagickWand *magick_wand;
    
	magick_wand = NewMagickWand();

	background_color_wand = makePixelWand(backgroundColor);

	status = MagickNewImage(magick_wand, 500, 500, background_color_wand);

	if (writeFile) {
		MagickSetImageFormat(magick_wand, outputFormat);
	
		MagickDrawImage(magick_wand, drawing_wand);
	
		status = MagickWriteImages(magick_wand, filename, MagickTrue);
	
		if (status == MagickFalse) {
			ThrowWandException(magick_wand);
		}
	}

	magick_wand = DestroyMagickWand(magick_wand);

    return;
}

void makeGradientImage(int number, char * filename) {
    
    MagickBooleanType status;
    
    MagickWand *pseudo_wand;
            
    int columns = 400 + number;
    int rows = 400 + number;

    /*
    Read an image.
    */
    MagickWandGenesis();
   
    pseudo_wand = NewMagickWand();

    status = MagickSetSize(pseudo_wand, columns, rows);
    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }


    if (MagickReadImage(pseudo_wand, "gradient:rgb(255,200,200)-rgb(128,128,128)") == MagickFalse) {
        printf("Goodbye\n");
        ThrowWandException(pseudo_wand);
    }

    PixelWand *tint_wand, *opacity_wand;

	tint_wand = NewPixelWand();
	PixelSetColor(tint_wand, "rgb(100,0,100)");

    opacity_wand = NewPixelWand();
    PixelSetColor(opacity_wand, "rgba(128,0,128,0.5)");

    status = MagickTintImage(pseudo_wand, tint_wand, opacity_wand);

    if (status == MagickFalse) {
		printf("Failed to MagickTintImage");
		ThrowWandException(pseudo_wand);
	}


    //printf("Step 2");

	status = MagickSetImageFormat(pseudo_wand, outputFormat);

	/* No magick is going to happen */
	if (status == MagickFalse) {
		printf("Failed to set format");
		ThrowWandException(pseudo_wand);
	}

    status = MagickWriteImages(pseudo_wand, filename, MagickTrue);

    if (status == MagickFalse) {
        ThrowWandException(pseudo_wand);
    }
        
    DestroyMagickWand(pseudo_wand);
    
}


int main(int argc,char **argv) {
    
    int x;
    char filename[1024];
    
    MagickWandGenesis();
    
    for (x=0 ; x<10 ; x++) {
    	sprintf(filename, "./output/clipFirst_%d.%s", x, outputFormat);
		drawClipTest(1, 1, filename);

		sprintf(filename, "./output/gradient_%d.%s", x, outputFormat);
		makeGradientImage(x, filename);

		sprintf(filename, "./output/clipSecond_%d.%s", x, outputFormat);
		drawClipTest(0, 1, filename);

		
		printf("x = %d \n", x);
    }

    MagickWandTerminus();
    return (0);
}
