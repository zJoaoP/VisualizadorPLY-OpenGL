#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "plyreader.h"

#define INF (1 << 30)

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

	float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
	float x, y, z;
	int pos;
	for(i = 0, pos = 0; i < myModel->vertexCount; i++, pos += 3){
		fscanf(file, "%f %f %f", &x, &y, &z);
		myModel->vertex[pos] = x;
		myModel->vertex[pos + 1] = y;
		myModel->vertex[pos + 2] = z;

		sumX += x;
		sumY += y;
		sumZ += z;
	}
	unsigned int q, a, b, c;
	for(i = 0, pos = 0; i < myModel->faceCount; i++, pos += 3){
		fscanf(file, "%u %u %u %u", &q, &a, &b, &c);
		myModel->faces[pos] = a;
		myModel->faces[pos + 1] = b;
		myModel->faces[pos + 2] = c;
	}
	fclose(file);

	myModel->color[0] = myModel->color[1] = myModel->color[2] = 1.0;
	
	myModel->angleX = 0;
	myModel->angleY = 0;

	myModel->center[0] = sumX / myModel->vertexCount;
	myModel->center[1] = sumY / myModel->vertexCount;
	myModel->center[2] = sumZ / myModel->vertexCount;
	myModel->scaleFactor = 1.0;

	myModel->translatedX = 0.0;
	myModel->translatedZ = 0.0;
	return myModel;
}

void performRotationPLY(PLY** object, int dx, int dy){
	(*object)->angleX += dy;
	(*object)->angleY += dx;
}

void performScalePLY(PLY** object, float scaleFactor){
	(*object)->scaleFactor = scaleFactor;
}

void performTranslationPLY(PLY** object, float dx, float dz){
	printf("Translation: (%.2f, 0, %.2f)\n", dx, dz);
	(*object)->translatedX += dx;
	(*object)->translatedZ += dz;

	printf("Current translation: (%.2f, %.2f)\n", (*object)->translatedX, (*object)->translatedZ);
}

void drawPLY(PLY* object){
	glColor3f(object->color[0], object->color[1], object->color[2]);

	glPushMatrix();

	glLoadIdentity();
	
	glTranslatef(object->translatedX, 0, object->translatedZ);
	glTranslatef(object->center[0], object->center[1], object->center[2]);

	glRotatef((GLfloat) object->angleX, 1.0, 0.0, 0.0);
	glRotatef((GLfloat) object->angleY, 0.0, 1.0, 0.0);
	glScalef(object->scaleFactor, object->scaleFactor, object->scaleFactor);

	glTranslatef(-object->center[0], -object->center[1], -object->center[2]);
	glTranslatef(-object->translatedX, 0, -object->translatedZ);	
	
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, object->vertex);
	glDrawElements(GL_TRIANGLES, object->faceCount * 3, GL_UNSIGNED_INT, object->faces);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
	return;
}

void changeColorPLY(PLY** object, float r, float g, float b){
	(*object)->color[0] = r;	
	(*object)->color[1] = g;
	(*object)->color[2] = b;
}