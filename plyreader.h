#ifndef _PLY_READER_
#define _PLY_READER_ 1

#define MAX_FILE_NAME 34

#include <GL/glut.h>

typedef struct Color{
	float red, green, blue;
} Color;

typedef struct PLY{
	char fileName[MAX_FILE_NAME];
	int vertexCount, faceCount;
	GLfloat* vertex;
	GLuint* faces;
	Color* color;
} PLY;

PLY* openPLY(char *filename);
void drawPLY(PLY* object);
Color* generateRandomColor();

#endif