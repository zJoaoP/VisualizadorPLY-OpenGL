#ifndef _PLY_READER_
#define _PLY_READER_ 1

#define MAX_FILE_NAME 34

#include <GL/glut.h>
#include "color.h"

typedef struct PLY{
	char fileName[MAX_FILE_NAME];
	int vertexCount, faceCount;
	GLfloat* vertex;
	GLuint* faces;
	Color* color;
} PLY;

void drawPLY(PLY* object);
void changeColor(PLY** object, float r, float g, float b);
PLY* openPLY(char *filename);

#endif