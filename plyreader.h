#ifndef _PLY_READER_
#define _PLY_READER_ 1

#define MAX_FILE_NAME 48

typedef struct PLY{
	char fileName[MAX_FILE_NAME];
	
	int vertexCount, faceCount;
} PLY;

PLY* openPLY(char *filename);
void drawPLY(PLY* model);

#endif