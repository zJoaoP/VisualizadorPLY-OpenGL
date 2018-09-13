#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "pontos.h"

/*
###################################################
	Universidade Federal da Bahia
	Departamento de Ciência da Computação
	MATA65 - Computação Gráfica (2018.2)
	Aluno: João Pedro Brito Silva
	Atividade: Trabalho prático 1
###################################################
Objetivos:
	1. Desenvolver um parser para arquivos .PLY
	2. Exibir um modelo importado via arquivo .PLY (Observar a meta 1) na tela. (Malha de triângulos)
	3. Como saber em qual malha cliquei, dado que um clique na tela retorna apenas uma posição 2D?
		(A posição atual da câmera pode ajudar nisso.)
	
	n. ????? (Rotacionar e alinhar)
	n + 1. Como facilitar a vida do usuário?
*/
struct listaDePontos *p = NULL;

float angulo_x = 0, angulo_y = 0;

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	struct listaDePontos *aux = p;
	int c = 1;
	while(aux != NULL){
		// printf("Desenhando %d\n", c++);
		glBegin(GL_POINTS);
		glVertex3f(aux->x, aux->y, aux->z);
		glEnd();

		aux = aux->next;
	}

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


void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	int pontos, i;
	if(scanf("%d", &pontos)){
		for(i = 0; i < pontos; i++){
			float x, y, z;
			scanf("%f %f %f", &x, &y, &z);
			inserirPonto(&p, x, y, z);
		}
		printf("Pontos lidos: %d\n", sizeListaDePontos(p));		
	}
}

int main(int argc, char **argv){
	// if(argc < 3 || argc > 5){
	// 	printf("Uso correto: %s [arquivo1.ply] [arquivo2.ply]\n", argv[0]);
	// 	return 1;
	// }

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