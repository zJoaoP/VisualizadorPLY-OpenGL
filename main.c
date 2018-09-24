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
	2. Desenvolver um sistema de rotação.
	3. Desenvolver um sistema de translação.
	4. Desenvolver um sistema de escala.
*/

PLY* objects[MODEL_COUNT];
int current = 0, mouse_x = -1, mouse_y = -1;
char operation = 'r';

void changeSelection(int previous, int current){
	changeColor(&(objects[previous]), 1.0, 1.0, 1.0); //Alterando a cor para branco.
	changeColor(&(objects[current]), 1.0, 0.0, 0.0); //Alterando a cor para vermelho.	
}

void performRotation(int current, int variationX, int variationY){
	printf("Performing rotation!!\n"); //O que fazer aqui??
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
	if(state == GLUT_DOWN){
		mouse_x = x;
		mouse_y = y;
	}
	else if(state == GLUT_UP){
		if(operation == 'r')
			performRotation(current, x - mouse_x, y - mouse_y);
	}
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 's':{ //Provisório.
			int previous = current;
			current = current + 1;
			if(current == MODEL_COUNT)
				current = 0;

			changeSelection(previous, current);
			glutPostRedisplay();
			break;
		}
	}
	// switch(key){
	// 	case 'x':{
	// 		angulo_x += 0.1;
	// 		glutPostRedisplay();
	// 		break;
	// 	}
	// 	case 'y':{
	// 		angulo_y += 0.1;
	// 		glutPostRedisplay();
	// 		break;
	// 	}
	// 	case 'z':{
	// 		angulo_z += 0.1;
	// 		glutPostRedisplay();
	// 		break;
	// 	}
	// }
}


void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.25, 0.25, -0.15, 0.35, -0.25, 0.25);
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
				changeColor(&(objects[0]), 1.0, 0.0, 0.0);

			i++;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Computação Gráfica 2018.2 (T1)");
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	initScene();

	glutMainLoop();
	return 0;
}