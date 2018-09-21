#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	2. Exibir um objecto importado via arquivo .PLY (Observar a meta 1) na tela. (Malha de triângulos)
	3. Como saber em qual malha cliquei, dado que um clique na tela retorna apenas uma posição 2D?
		(A posição atual da câmera pode ajudar nisso.)
	
	n. ????? (Rotacionar e alinhar)
	n + 1. Como facilitar a vida do usuário?
*/

float angulo_x = 0, angulo_y = 0, angulo_z = 0;
PLY* objects[MODEL_COUNT];

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	int i;
	for(i = 0; i < MODEL_COUNT; i++)
		drawPLY(objects[i]);

	glRotatef(angulo_x, 1, 0, 0);
	glRotatef(angulo_y, 0, 1, 0);
	glRotatef(angulo_z, 0, 0, 1);

	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL Error: %d\n", err);
    }
	glFlush();
}

void mouse(int button, int state, int x, int y){
	if(!state)
		printf("mouse(%d, %d, %d, %d) pressed.\n", button, state, x, y);
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
		case 'z':{
			angulo_z += 0.1;
			glutPostRedisplay();
			break;
		}
	}
}


void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.25, 0.25, -0.25, 0.25, -0.25, 0.25);
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
			objects[i] = NULL;
			initObject(argv[i + 1], i);
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