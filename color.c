#include <stdlib.h>
#include "color.h"

Color* generateRandomColor(){
	Color *color = (Color*) malloc(sizeof(Color));
	if(color == NULL)
		return NULL;

	color->red = (rand() % 101) / 100.0;
	color->green = (rand() % 101) / 100.0;
	color->blue = (rand() % 101) / 100.0;
	return color;
}

Color* generateColor(float r, float g, float b){
	Color *color = (Color*) malloc(sizeof(Color));
	if(color == NULL)
		return NULL;

	color->red = r;
	color->green = g;
	color->blue = b;
	return color;	
}