#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "plyreader.h"
#include "color.h"

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
	myModel->faces = (GLuint*) malloc(sizeof(GLuint) * (myModel->faceCount * 3));

	if(myModel->vertex == NULL || myModel->faces == NULL)
		return NULL;

	float a, b, c;
	int pos;
	for(i = 0, pos = 0; i < myModel->vertexCount; i++, pos += 3){
		fscanf(file, "%f %f %f", &a, &b, &c);
		myModel->vertex[pos] = a;
		myModel->vertex[pos + 1] = b;
		myModel->vertex[pos + 2] = c;
	}
	unsigned int q, x, y, z;
	for(i = 0, pos = 0; i < myModel->faceCount; i++, pos += 3){
		fscanf(file, "%u %u %u %u", &q, &x, &y, &z);
		myModel->faces[pos] = x;
		myModel->faces[pos + 1] = y;
		myModel->faces[pos + 2] = z;
	}
	fclose(file);
	myModel->color = generateColor(1.0, 1.0, 1.0);
	return myModel;
}

void drawPLY(PLY* object){
	Color *c = object->color;
	glColor3f(c->red, c->green, c->blue);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, object->vertex);
	glDrawElements(GL_TRIANGLES, object->faceCount * 3, GL_UNSIGNED_INT, object->faces);

	glDisableClientState(GL_VERTEX_ARRAY);
	return;
}

void changeColor(PLY** object, float r, float g, float b){
	Color *c = (*object)->color;
	
	c->red = r;
	c->green = g;
	c->blue = b;
}