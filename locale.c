#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <wand/MagickWand.h>


#include <locale.h>



int main(int argc,char **argv) {
    
    char *current_locale;
    
// 	printf ("hello\n");

 	current_locale = setlocale (LC_NUMERIC, NULL);

 	printf("current_locale is %s \n", current_locale);

	current_locale = setlocale (LC_NUMERIC, "fr_FR");

 	printf("current_locale is %s \n", current_locale);

	char * format = "line %.20g %.20g %.20g %.20g\n";

	float sx = 100,sy = 100;
	float ex = 10;
	float ey = 10.5;


	printf(format, sx, sy, ex, ey);


    return (0);
}
