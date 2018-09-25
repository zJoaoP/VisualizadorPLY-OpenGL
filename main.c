#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	1. Desenvolver uma forma simples de alterar a malha selecionada.
		(Adaptável para o mouse.) OK!
	2. Desenvolver um sistema de rotação. (Quase pronto.)
	3. Desenvolver um sistema de translação.
	4. Desenvolver um sistema de escala.
*/

PLY* objects[MODEL_COUNT];

int current = 0;
int currentX = 0, currentY = 0, dx = 0, dy = 0;
int isLeftButtonPressed = 0;

char operation = 'r';

void changeSelection(int previous, int current){
	changeColorPLY(&(objects[previous]), 1.0, 1.0, 1.0); //Alterando a cor para branco.
	changeColorPLY(&(objects[current]), 1.0, 0.0, 0.0); //Alterando a cor para vermelho.	
}

void performRotation(int id, int dx, int dy){
	performRotationPLY(&(objects[id]), dx, dy);
	glutPostRedisplay();
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	int i;
	for(i = 0; i < MODEL_COUNT; i++)
		drawPLY(objects[i]);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("OpenGL Error: %d\n", err);
	
	glFlush();
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isLeftButtonPressed = 1;

		//Inicializando o vetor de movimentação.
		currentX = x;
		currentY = y;
		dx = 0; //Deslocamento inicial igualado a 0.
		dy = 0;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		isLeftButtonPressed = 0; //Utilizar isso em "MouseMotion".
}

void mouseMotion(int x, int y){
	if(isLeftButtonPressed){
		//Atualizando o vetor de movimentação, independente do caso.
		dx = x - currentX;
		dy = y - currentY;
		currentX = x;
		currentY = y;
		switch(operation){
			case 'r':{ //Rotation.
				performRotation(current, dx, dy);
				break;
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 's':{ //Provisório. Alterar mais tarde.
			int previous = current;
			current = current + 1;
			if(current == MODEL_COUNT)
				current = 0;

			changeSelection(previous, current);
			glutPostRedisplay();
			break;
		}
	}
}


void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.25, 0.25, -0.15, 0.35, -0.25, 0.25);
	// glOrtho(-1, 1, -1, 1, -1, 1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void initObject(char *fileName, int position){
	objects[position] = openPLY(fileName);
}

int main(int argc, char **argv){
	srand(time(NULL));
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

	initScene();

	glutMainLoop();
	return 0;
}