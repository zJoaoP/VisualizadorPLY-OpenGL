#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "plyreader.h"

#define MODEL_COUNT 2

/*
###################################################
	Universidade Federal da Bahia
	Departamento de Ciência da Computação
	MATA65 - Computação Gráfica (2018.2)
	Aluno: João Pedro Brito Silva
	Atividade: Trabalho Prático 1
###################################################

Objetivos:
	1. Desenvolver um sistema de translação.
	2. Selecionar com o mouse.
	3. Mover todos os codigos para um só arquivo.

http://professor.unisinos.br/ltonietto/jed/cgr/selection.pdf
*/

PLY* objects[MODEL_COUNT];

int current = 0;
int currentX = 0, currentY = 0, dx = 0, dy = 0;
int startX = 0.0, startY = 0.0;
int isRightButtonPressed = 0;
int isLeftButtonPressed = 0;

float theta = 0.0, phi = 0.0, distance = 2.0;
float ratio = 1.0;
char operation = 'r';

void changeSelection(int previous, int current){
	changeColorPLY(&(objects[previous]), 1.0, 1.0, 1.0); //Alterando a cor para branco.
	changeColorPLY(&(objects[current]), 1.0, 0.0, 0.0); //Alterando a cor para vermelho.	
}

void performRotation(int id, int dx, int dy){
	performRotationPLY(&(objects[id]), -dx, dy);
	glutPostRedisplay();
}

float getDistance(float xA, float yA, float xB, float yB){
	return sqrt(pow(xA - xB, 2) + pow(yA - yB, 2));
}

void performScale(int id, int currentX, int currentY){
	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	int w = m_viewport[2], h = m_viewport[3];
	float originalDistance = getDistance(w/2, h/2, startX, startY);
	float currentDistance = getDistance(w/2, h/2, currentX, currentY);

	performScalePLY(&(objects[id]), currentDistance / originalDistance);
	glutPostRedisplay();
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	float cameraX = distance * -sinf(theta*(M_PI/180)) * cosf((phi)*(M_PI/180));
	float cameraY = distance * -sinf((phi)*(M_PI/180));
	float cameraZ = -distance * cosf((theta)*(M_PI/180)) * cosf((phi)*(M_PI/180));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0f, ratio, 0.1, 50);
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	int i;
	for(i = 0; i < MODEL_COUNT; i++)
		drawPLY(objects[i]);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("OpenGL Error: %d\n", err);

	glFlush();
}

void mouse(int button, int state, int x, int y){
	currentX = x, currentY = y;
	dx = 0, dy = 0;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isLeftButtonPressed = 1;
		startX = x;
		startY = y;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		isLeftButtonPressed = 0; //Utilizar isso em "MouseMotion".
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		isRightButtonPressed = 1;
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		isRightButtonPressed = 0;
	else if(button == 3){
		distance += 0.05;
		glutPostRedisplay();
	}
	else if(button == 4){
		distance -= 0.05;
		glutPostRedisplay();
	}
}

void mouseMotion(int x, int y){
	dx = x - currentX;
	dy = y - currentY;
	currentX = x;
	currentY = y;

	if(isLeftButtonPressed){
		//Atualizando o vetor de movimentação, independente do caso.
		switch(operation){
			case 'r':{ //Rotation.
				performRotation(current, dx, dy);
				break;
			}
			case 's':{
				performScale(current, currentX, currentY);
				break;
			}
		}
	}
	else if(isRightButtonPressed){
		theta += dx;
		phi += dy;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'q':{ //Provisório. Alterar mais tarde.
			int previous = current;
			current = current + 1;
			if(current == MODEL_COUNT)
				current = 0;

			changeSelection(previous, current);
			glutPostRedisplay();
			break;
		}
		case 'r':
		case 's':
		case 't':{
			operation = key;
			break;
		}
	}
}

void initScene(){
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void initObject(char *fileName, int position){
	objects[position] = openPLY(fileName);
}

void reshape(int w, int h){
	ratio = (float) w / h;

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){
	if(argc != MODEL_COUNT + 1){
		int i;
		printf("Uso correto: %s", argv[0]);
		for(i = 0; i < MODEL_COUNT; i++)
			printf(" [arquivo%d.PLY]", i + 1);

		printf("\n");
		return 1;
	}
	else{
		int i = 0;
		while(i < argc - 1){
			initObject(argv[i + 1], i);
			if(i == current)
				changeColorPLY(&(objects[0]), 1.0, 0.0, 0.0);

			i++;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("CG 2018.2");
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);

	initScene();

	glutMainLoop();
	return 0;
}