#ifndef _COLOR_
#define _COLOR_ 2

typedef struct Color{
	float red, green, blue;
} Color;

Color* generateRandomColor();
Color* generateColor(float r, float g, float b);

#endif