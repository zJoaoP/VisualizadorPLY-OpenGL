#ifndef _PLY_READER_
#define _PLY_READER_ 1

#define MAX_FILE_NAME 32

#include <GL/glut.h>

typedef struct PLY{
	char fileName[MAX_FILE_NAME];
	GLfloat* vertex;
	GLubyte* faces;
	int vertexCount, faceCount;
} PLY;

PLY* openPLY(char *filename);
void drawPLY(PLY* model);

#endif