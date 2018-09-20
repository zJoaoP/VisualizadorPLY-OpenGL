#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "plyreader.h"

PLY *openPLY(char *fileName){
	PLY* myModel = (PLY*) malloc(sizeof(PLY));
	if(myModel == NULL)
		return NULL;

	FILE *file = fopen(fileName, "rw+");
	char param[11], type[7];
	int count, i;

	strcpy(myModel->fileName, fileName);
	while(fscanf(file, "%s", param) == 1){
		if(!strcmp(param, "end_header"))
			break;

		if(!strcmp(param, "element") && fscanf(file, "%s %d", type, &count)){
			if(!strcmp(type, "vertex"))
				myModel->vertexCount = count;
			else
				myModel->faceCount = count;
		}
		else
			continue;
	}
	
	myModel->vertex = (GLfloat*) malloc(myModel->vertexCount * 3);
	myModel->faces = (GLubyte*) malloc(myModel->faceCount * 3);

	if(myModel->vertex == NULL || myModel->faces == NULL)
		return NULL;

	float a, b, c;
	for(i = 0; i < myModel->vertexCount; i += 3){
		fscanf(file, "%f %f %f", &a, &b, &c);

		myModel->vertex[i] = a;
		myModel->vertex[i + 1] = b;
		myModel->vertex[i + 2] = c;
		printf("%d (%d)\n", i, myModel->vertexCount);
	}
	// for(i = 0; i < myModel->faceCount; i++){

	// }
	fclose(file);
	return myModel;
}

void drawPLY(PLY* model){
	return;
}