#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "plyreader.h"

PLY *openPLY(char *fileName){
	PLY* myModel = (PLY*) malloc(sizeof(PLY));
	if(myModel == NULL)
		return NULL;

	char *param = malloc(sizeof(char) * 12), *type = malloc(sizeof(char) * 7);
	int count, i;
	if(param == NULL || type == NULL)
		return NULL;
	

	FILE *file = fopen(fileName, "rw+");
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
	free(param);
	free(type);
	
	myModel->vertex = (GLfloat*) malloc(sizeof(GLfloat) * (myModel->vertexCount * 3));
	myModel->faces = (GLubyte*) malloc(sizeof(GLubyte) * (myModel->faceCount * 3));

	if(myModel->vertex == NULL || myModel->faces == NULL)
		return NULL;

	float a, b, c;
	for(i = 0; i < myModel->vertexCount; i += 3){
		int x = fscanf(file, "%f %f %f", &a, &b, &c);

		myModel->vertex[i] = a;
		myModel->vertex[i + 1] = b;
		myModel->vertex[i + 2] = c;
		printf("Posição = %d (Tamanho = %d)\n", i, myModel->vertexCount);
	}
	for(i = 0; i < myModel->faceCount; i += 3){
		int q, x, y, z;
		q = fscanf(file, "%d %d %d %d", &q, &x, &y, &z);
		myModel->faces[i] = x;
		myModel->faces[i + 1] = y;
		myModel->faces[i + 2] = z;
	}
	fclose(file);
	return myModel;
}

void drawPLY(PLY* model){
	return;
}