#ifndef _PLY_READER_
#define _PLY_READER_ 1

#define MAX_FILE_NAME 34

#include <GL/glut.h>

typedef struct PLY{
	char fileName[MAX_FILE_NAME];
	int vertexCount, faceCount;
	float center[3]; //Coordenadas aproximadas do centro.
	float color[3]; //R G B
	
	GLfloat* vertex;
	GLuint* faces;
	GLfloat angleX, angleY; //Ângulo das rotações.
} PLY;

void performRotationPLY(PLY** object, int dx, int dy);
void changeColorPLY(PLY** object, float r, float g, float b);
void drawPLY(PLY* object);

PLY* openPLY(char *filename);

#endif