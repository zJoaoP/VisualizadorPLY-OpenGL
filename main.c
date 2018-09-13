#include <stdio.h>
#include <GL/glut.h>

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

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw here!

	glFlush();
}

void mouse(int button, int state, int x, int y){
	if(state)
		printf("mouse(%d, %d, %d, %d)\n", button, state, x, y);
}

void keyboard(unsigned char key, int x, int y){
	printf("keyboard(%c, %d, %d)\n", key, x, y);
}

void initScene(){
	glMatrixMode(GL_PROJECTION);
	glOrtho(-10, 10, -10, 10, -10, 10);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv){
	// if(argc < 3 || argc > 5){
	// 	printf("Uso correto: %s [arquivo1.ply] [arquivo2.ply]\n", argv[0]);
	// 	return 1;
	// }

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Hello, world!");
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	initScene();

	glutMainLoop();
	return 0;
}