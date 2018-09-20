#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define MODEL_COUNT 2

#include "plyreader.h"
/*
###################################################
	Universidade Federal da Bahia
	Departamento de Ciência da Computação
	MATA65 - Computação Gráfica (2018.2)
	Aluno: João Pedro Brito Silva
	Atividade: Trabalho Prático 1
###################################################
Objetivos:
	1. Desenvolver um parser para arquivos .PLY
	2. Exibir um modelo importado via arquivo .PLY (Observar a meta 1) na tela. (Malha de triângulos)
	3. Como saber em qual malha cliquei, dado que um clique na tela retorna apenas uma posição 2D?
		(A posição atual da câmera pode ajudar nisso.)
	
	n. ????? (Rotacionar e alinhar)
	n + 1. Como facilitar a vida do usuário?
*/

float angulo_x = 0, angulo_y = 0;

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(angulo_x, 1, 0, 0);
	glRotatef(angulo_y, 0, 1, 0);
	glFlush();
}

void mouse(int button, int state, int x, int y){
	if(state)
		printf("mouse(%d, %d, %d, %d)\n", button, state, x, y);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'x':{
			angulo_x += 0.1;
			glutPostRedisplay();
			break;
		}
		case 'y':{
			angulo_y += 0.1;
			glutPostRedisplay();
			break;
		}
	}
}

PLY* models[MODEL_COUNT];

void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void initModel(char *fileName, int position){
	models[position] = openPLY(fileName);
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
			initModel(argv[i + 1], i);
			i++;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("PLY Reader!");
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	initScene();

	glutMainLoop();
	return 0;
}