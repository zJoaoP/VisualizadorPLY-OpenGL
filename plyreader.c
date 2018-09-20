#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "plyreader.h"

PLY *openPLY(char *fileName){
	PLY* myModel = (PLY*) malloc(sizeof(PLY));
	FILE *file = fopen(fileName, "rw+");
	char param[11];

	strcpy(myModel->fileName, fileName);
	while(fscanf(file, "%s", param) && strcmp(param, "end_header") != 0){
		if(!strcmp(param, "element")){
			char type[7];
			int count;
			fscanf(file, "%s %d", type, &count);
			if(!strcmp(type, "vertex"))
				myModel->vertexCount = count;
			else
				myModel->faceCount = count;
		}
		else
			continue;
	}
	//Read dots.
	//Read faces
	fclose(file);
	return myModel;
}

void drawPLY(PLY* model){
	return;
}