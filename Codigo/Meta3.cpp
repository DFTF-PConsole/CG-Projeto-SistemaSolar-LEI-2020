/* Projeto Meta 3 - Sistema Solar (C++ File - MAIN) ||| CG - LEI / FCTUC 2020/21 | Dario Filipe Torres Felix N.2018275530 */



/* ***** BIBLIOTECAS ***** */
#include <windows.h>
#include <stdio.h>
#include <fstream>

#include <string>
#include <fstream>

#include <errno.h>
#include <GL\glew.h>			// openGL
#include <GL\freeGlut.h>		// openGL

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")



/* ***** CONSTANTES / MACROS ***** */
// Cores com Alpha Opaco
#define VERMELHO_ESCURO			0.5, 0.0, 0.0
#define VERMELHO				1.0, 0.0, 0.0
#define LARANJA					1.0, 0.502, 0.0
#define AMARELO					1.0, 1.0, 0.0
#define VERDE_CLARO				0.502, 1.0, 0.0
#define VERDE_ESCURO			0.0, 0.4, 0.0
#define VERDE					0.0, 1.0, 0.0
#define VERDE_AGUA				0.0, 1.0, 0.502
#define CIANO					0.0, 1.0, 1.0
#define AZUL_CLARO				0.0, 0.502, 1.0
#define AZUL_VIDRO				0.8, 1.0, 1.0
#define AZUL					0.0, 0.0, 1.0
#define AZUL_ESCURO				0.0, 0.0, 0.6
#define ROXO					0.498, 0.0, 1.0
#define ROSA					1.0, 0.0, 1.0
#define MAGENTA					1.0, 0.0, 0.498
#define BRANCO					1.0, 1.0, 1.0
#define CINZENTO_CLARO			0.878, 0.878, 0.878
#define CINZENTO				0.502, 0.502, 0.502
#define CINZENTO_ESCURO			0.251, 0.251, 0.251
#define CINZENTO_SUPER_ESCURO	0.1, 0.1, 0.1
#define PRETO					0.0, 0.0, 0.0
#define CASTANHO_SUPER_ESCURO	0.1, 0.01, 0.0
#define CASTANHO_ESCURO			0.2, 0.098, 0.0
#define CASTANHO				0.4, 0.2, 0.0
#define CASTANHO_CLARO			0.6, 0.298, 0.0
#define CASTANHO_VERDADEIRO		0.545, 0.271, 0.075

// Constantes Matematicas
#define PI						3.14159

// Valores Iniciais
#define RAIO_INIT				25.0													// Observador: raio / distancia
#define ANGULO_INIT				PI/2													// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz
#define PROJECAO_INIT			0														// boolean: qual projecao? ortog Vs persp
#define EIXOS_INIT				1														// boolean: ignorar eixos? sim Vs nao
#define DEBUG_INIT				1														// boolean: ignorar debug? sim Vs nao
#define LEGENDA_INIT			0														// boolean: ignorar legenda? sim Vs nao
#define Y_ALVO_INIT				0.0														// yAlvo (e yObservador)
#define X_ALVO_INIT				0.0														// xAlvo (e xObservador)
#define Z_ALVO_INIT				0.0														// zAlvo (e zObservador)
#define X_LUZ_1_INIT			0.0	
#define Y_LUZ_1_INIT			0.0	
#define Z_LUZ_1_INIT			0.0

// Constantes Programa
#define MSEC					33														// refresh
#define W_SCREEN				700														// janela largura
#define H_SCREEN				600														// janela altura
#define TIPO_PHONG				1
#define TIPO_GOURAD				2
#define TIPO_ESTATICO			3

// Valores Cenario Constantes
#define DIM_MUNDO_X				100.0
#define DIM_MUNDO_Y				100.0													// altura maxima mundo (perspetiva)
#define DIM_MUNDO_Z				100.0
#define ANGULO_Z				95														// Angulo Observador
#define X_ALVO_MAX				DIM_MUNDO_X											// MAX xAlvo (e xObservador)
#define Y_OBS_MAX				DIM_MUNDO_Y												// MAX yObservador
#define Z_ALVO_MAX				DIM_MUNDO_Z											// MAX zAlvo (e zObservador)
#define RAIO_MAX				50.0													// MAX ZOOM Observador: raio / distancia
#define RAIO_MIN				0.1														// MIN ZOOM Observador: raio / distancia
#define RAIO_INC				2.0														// INC raio / distancia de visao
#define ANGULO_INC				0.1														// INC angulo de visao
#define MOVE_INC				2.0													// INC <setas> em xOx e zOz (e yObs)



/* ***** VARIAVEIS GLOBAIS ***** */
GLfloat		rVisao;																		// Observador: raio / distancia
GLfloat		aVisao;																		// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz

GLfloat		xObs;																		// xObservador - Local Onde o Observador Esta  | Coordenadas Plano xOz
GLfloat		yObs;																		// yObservador (Altura)
GLfloat		zObs;																		// zObservador | Coordenadas Plano xOz

GLfloat		xAlvo;																		// xAlvo - Para Onde o Observador Esta a Olhar
GLfloat		yAlvo;																		// yAlvo
GLfloat		zAlvo;																		// zAlvo

GLfloat		xLuz;
GLfloat		yLuz;
GLfloat		zLuz;

int			ignorar_eixos;																// boolean: ignorar eixos? sim Vs nao

GLint  unitempo;
float  tempo;

GLint  uniTipo;
int tipo;

GLint  unixObs;
GLint  uniyObs;
GLint  unizObs;

GLint  unixLuz;
GLint  uniyLuz;
GLint  unizLuz;

int raio_real_sol = 696; // dividido por 10^3 em todos
GLfloat r_sol_aux = 25.0;
GLfloat r_sol = r_sol_aux/5.0;
GLfloat r_mercurio = (2.0 * r_sol_aux)/raio_real_sol;
GLfloat r_venus = (6.0 * r_sol_aux) / raio_real_sol;
GLfloat r_terra = (6.0 * r_sol_aux) / raio_real_sol;
GLfloat r_marte = (3.0 * r_sol_aux) / raio_real_sol;
GLfloat r_jupiter = (69.0 * r_sol_aux) / raio_real_sol;
GLfloat r_saturno = (58.0 * r_sol_aux) / raio_real_sol;
GLfloat r_urano = (25.0 * r_sol_aux) / raio_real_sol;
GLfloat r_neptuno = (24.0 * r_sol_aux) / raio_real_sol;

int d_real_neptuno = 4000000 - raio_real_sol; // dividido por 10^3 em todos
GLfloat d_neptuno_aux = DIM_MUNDO_X - r_neptuno - r_sol;
GLfloat d_neptuno = d_neptuno_aux + r_sol;
GLfloat shift_raio_sol = r_sol;
GLfloat d_mercurio = shift_raio_sol + (58000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_venus = shift_raio_sol + (108000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_terra = shift_raio_sol + (149000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_marte = shift_raio_sol + (228000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_jupiter = shift_raio_sol + (779000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_saturno = shift_raio_sol + (1434000.0 * d_neptuno_aux) / d_real_neptuno;
GLfloat d_urano = shift_raio_sol + (2871000.0 * d_neptuno_aux) / d_real_neptuno;

GLint  unid_mercurio, unid_venus, unid_terra, unid_marte, unid_jupiter, unid_saturno, unid_urano, unid_neptuno;

GLint  unin_planeta;
int n_planeta;

GLint  univelocidade;
float velocidade;

// Definicoes dos ficheiros dos shaders: vertices + fragmentos
char filenameV[] = "VertexShaderMeta3.txt";
char filenameF[] = "FragmentShaderMeta3.txt";

// SHADERS variaveis
char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram;



/* ***** PROTOTIPOS ***** */
int main(int argc, char** argv);
char* readShaderFile(char* FileName);
void BuiltShader(void);
void InitShader(void);
void DeInitShader(void);
void inicia(void);
void cenario(void);
void teclado(unsigned char key, int x, int y);
void printHelp(void);
void tecladoEspecial(int key, int x, int y);
void iniciaVarsGlobaisPadrao(void);
void desenha(void);
void desenhaEixos(void);
void Timer(int value);



/* ***** FUNCOES ***** */
int main(int argc, char** argv) {

	iniciaVarsGlobaisPadrao();


	printf("**************************************************************************************\n");
	printf("* CG - LEI/FCTUC 2020/21 | Dario Felix N.2018275530 | Projeto Meta 3 - SISTEMA SOLAR *\n");
	printf("**************************************************************************************\n");
	printHelp();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W_SCREEN, H_SCREEN);
	glutInitWindowPosition(300, 100);
	glutCreateWindow(" Dario Felix N. 2018275530 | FCTUC CG 2020/21 Meta 3 | Sistema Solar ");
	
	inicia();

	//  GLEW
	GLenum err = glewInit();
	InitShader();
	DeInitShader();


	glutSpecialFunc(tecladoEspecial);
	glutDisplayFunc(cenario);
	glutKeyboardFunc(teclado);
	glutIdleFunc(cenario);

	glutTimerFunc(MSEC, Timer, 1);														// glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds.

	glutMainLoop();
	return 1;
}


void Timer(int value) {
	// Ciclo

	tempo = tempo + MSEC/1000.0;
	glUniform1f(unitempo, tempo);

	glutPostRedisplay();																// marks the current window as needing to be redisplayed.
	glutTimerFunc(MSEC, Timer, 1);														// glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds.
}


void iniciaVarsGlobaisPadrao(void) {
	rVisao = RAIO_INIT;																	// Observador: raio / distancia
	aVisao = ANGULO_INIT;																// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz

	xAlvo = X_ALVO_INIT;																// xAlvo - Para Onde o Observador Esta a Olhar
	yAlvo = Y_ALVO_INIT;																// yAlvo
	zAlvo = Z_ALVO_INIT;																// zAlvo

	xObs = rVisao * cos(aVisao) + xAlvo;												// xObservador - Local Onde o Observador Esta  | Coordenadas Plano xOz
	yObs = yAlvo;																		// yObservador (Altura)
	zObs = rVisao * sin(aVisao) + zAlvo;												// zObservador | Coordenadas Plano xOz

	xLuz = X_LUZ_1_INIT;
	yLuz = Y_LUZ_1_INIT;
	zLuz = Z_LUZ_1_INIT;

	ignorar_eixos = EIXOS_INIT;															// boolean: ignorar eixos? sim Vs nao

	tempo = 0.0;
	velocidade = 1.0;
}


char* readShaderFile(char* FileName) {
	// 1. Ler um ficheiro com um shader

	char* DATA = NULL;
	int   flength = 0;
	FILE* filepoint;
	errno_t err;

	err = fopen_s(&filepoint, FileName, "r");
	if (!err) {
		fseek(filepoint, 0, SEEK_END);
		flength = ftell(filepoint);
		rewind(filepoint);

		DATA = (char*)malloc(sizeof(char) * (flength + 1));
		flength = fread(DATA, sizeof(char), flength, filepoint);

		DATA[flength] = '\0';
		fclose(filepoint);
		return DATA;
	}
	else {
		printf(" --------  Error while reading  %s ", FileName);
	}
}


void BuiltShader(void) {
	// 2. Criar, compilar, linkar, e usar

	GLEW_ARB_vertex_shader;
	GLEW_ARB_fragment_shader;

	// Criar
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(filenameV);
	FragmentShaderSource = readShaderFile(filenameF);

	const char* VS = VertexShaderSource;
	const char* FS = FragmentShaderSource;
	glShaderSource(VertexShader, 1, &VS, NULL);
	glShaderSource(FragmentShader, 1, &FS, NULL);
	free(VertexShaderSource);
	free(FragmentShaderSource);

	// Compilar
	glCompileShaderARB(VertexShader);
	glCompileShaderARB(FragmentShader);

	// Criar e Linkar
	ShaderProgram = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	// Usar
	glUseProgramObjectARB(ShaderProgram);
}


void InitShader(void) {

	// Criar+linkar
	BuiltShader();

	unitempo = glGetUniformLocation(ShaderProgram, "tempo");
	glUniform1f(unitempo, tempo);

	uniTipo = glGetUniformLocation(ShaderProgram, "tipo");
	glUniform1i(uniTipo, tipo);

	unixObs = glGetUniformLocation(ShaderProgram, "xObs");
	glUniform1f(unixObs, xObs);

	uniyObs = glGetUniformLocation(ShaderProgram, "yObs");
	glUniform1f(uniyObs, yObs);

	unizObs = glGetUniformLocation(ShaderProgram, "zObs");
	glUniform1f(unizObs, zObs);

	unixLuz = glGetUniformLocation(ShaderProgram, "xLuz");
	glUniform1f(unixLuz, xLuz);

	uniyLuz = glGetUniformLocation(ShaderProgram, "yLuz");
	glUniform1f(uniyLuz, yLuz);

	unizLuz = glGetUniformLocation(ShaderProgram, "zLuz");
	glUniform1f(unizLuz, zLuz);

	unid_mercurio = glGetUniformLocation(ShaderProgram, "d_mercurio");
	glUniform1f(unid_mercurio, d_mercurio);

	unid_venus = glGetUniformLocation(ShaderProgram, "d_venus");
	glUniform1f(unid_venus, d_venus);

	unid_terra = glGetUniformLocation(ShaderProgram, "d_terra");
	glUniform1f(unid_terra, d_terra);

	unid_marte = glGetUniformLocation(ShaderProgram, "d_marte");
	glUniform1f(unid_marte, d_marte);

	unid_jupiter = glGetUniformLocation(ShaderProgram, "d_jupiter");
	glUniform1f(unid_jupiter, d_jupiter);

	unid_saturno = glGetUniformLocation(ShaderProgram, "d_saturno");
	glUniform1f(unid_saturno, d_saturno);

	unid_urano = glGetUniformLocation(ShaderProgram, "d_urano");
	glUniform1f(unid_urano, d_urano);

	unid_neptuno = glGetUniformLocation(ShaderProgram, "d_neptuno");
	glUniform1f(unid_neptuno, d_neptuno);

	unin_planeta = glGetUniformLocation(ShaderProgram, "n_planeta");
	glUniform1f(unin_planeta, n_planeta);

	univelocidade = glGetUniformLocation(ShaderProgram, "velocidade");
	glUniform1f(univelocidade, velocidade);
}


void DeInitShader(void) {
	// 3.Libertar os Shaders

	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(ShaderProgram);
}



void inicia(void){
	glClearColor(PRETO, 1.0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);																// From this point on, all the faces that are not front-faces are discarded.
	glCullFace(GL_BACK);
}


void cenario(void){

	//glUniform1f(unitempo, tempo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, W_SCREEN, H_SCREEN);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(ANGULO_Z, (float)W_SCREEN / H_SCREEN, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xObs, yObs, zObs, xAlvo, yAlvo, zAlvo, 0, 1, 0);

	if (ignorar_eixos == 0) {
		desenhaEixos();
	}

	desenha();

	glutSwapBuffers();
}


void desenha(void) {

	GLfloat malha = 30;

	tipo = TIPO_PHONG;
	glUniform1i(uniTipo, tipo);

	// Planeta Neptuno 8
	n_planeta = 8;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(AZUL_ESCURO);
	//glPushMatrix();
	//glTranslatef(d_neptuno, 0, 0);
	glutSolidSphere(r_neptuno, malha, malha);
	//glPopMatrix();

	// Planeta Saturno 6
	n_planeta = 6;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(CASTANHO_CLARO);
	//glPushMatrix();
	//glTranslatef(d_saturno, 0, 0);
	glutSolidSphere(r_saturno, malha, malha);
	//glPopMatrix();

	// Planeta Marte 4
	n_planeta = 4;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(VERMELHO);
	//glPushMatrix();
	//glTranslatef(d_marte, 0, 0);
	glutSolidSphere(r_marte, malha, malha);
	//glPopMatrix();

	// Planeta Venus 2
	n_planeta = 2;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(LARANJA);
	//glPushMatrix();
	//glTranslatef(d_venus, 0, 0);
	glutSolidSphere(r_venus, malha, malha);
	//glPopMatrix();




	// --------------------
	tipo = TIPO_GOURAD;
	glUniform1i(uniTipo, tipo);

	// Planeta Urano 7
	n_planeta = 7;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(AZUL_CLARO);
	//glPushMatrix();
	//glTranslatef(d_urano, 0, 0);
	glutSolidSphere(r_urano, malha, malha);
	//glPopMatrix();

	// Planeta Jupiter 5
	n_planeta = 5;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(CASTANHO);
	//glPushMatrix();
	//glTranslatef(d_jupiter, 0, 0);
	glutSolidSphere(r_jupiter, malha, malha);
	//glPopMatrix();

	// Planeta Terra 3
	n_planeta = 3;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(VERDE_CLARO);
	//glPushMatrix();
	//glTranslatef(d_terra, 0, 0);
	glutSolidSphere(r_terra, malha, malha);
	//glPopMatrix();

	// Planeta Mercurio 1
	n_planeta = 1;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(CINZENTO_CLARO);
	//glPushMatrix();
	//glTranslatef(d_mercurio, 0, 0);
	glutSolidSphere(r_mercurio, malha, malha);
	//glPopMatrix();



	// ------------------
	tipo = TIPO_ESTATICO;
	glUniform1i(uniTipo, tipo);

	// SOL
	n_planeta = 0;
	glUniform1f(unin_planeta, n_planeta);
	glColor3f(AMARELO);
	glPushMatrix();
	glTranslatef(xLuz, yLuz, zLuz);
	glutSolidSphere(r_sol, malha, malha);
	glPopMatrix();

}


void teclado(unsigned char key, int x, int y) {

	switch (key) {

	case 'h':
	case 'H':																			// Print Ajuda na Consola (Key e Funcao)
		printf(">>> \'%s\' : %s\n", "H", "Print Ajuda");
		printHelp();
		break;

	case 'e':
	case 'E':																			// ignorar eixos?
		printf(">>> \'%s\' : %s\n", "E", "Ligar/Desligar os Eixos Auxiliares");
		ignorar_eixos = (ignorar_eixos + 1) % 2;
		glutPostRedisplay();
		break;

	case 'r':
	case 'R':																			// Reiniciar os valores do programa (PROJECAO) e  (ANIMACAO)
		printf(">>> \'%s\' : %s\n", "R", "Reiniciar Todo o Cenario");
		iniciaVarsGlobaisPadrao();
		glutPostRedisplay();
		break;

	case 'w':
	case 'W':																			// Mover paara cima Y
		printf(">>> \'%s\' : %s\n", "W", "Subir - o Obs em Torno do Alvo");
		yObs = yObs + MOVE_INC;
		if (yObs > Y_OBS_MAX)
			yObs = Y_OBS_MAX;
		glUniform1f(uniyObs, yObs);
		glutPostRedisplay();
		break;

	case 's':
	case 'S':																			// Mover para baixo Y
		printf(">>> \'%s\' : %s\n", "S", "Descer - o Obs em Torno do Alvo");
		yObs = yObs - MOVE_INC;
		if (yObs < -Y_OBS_MAX)
			yObs = -Y_OBS_MAX;
		glUniform1f(uniyObs, yObs);
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':																			// Rodar em torno do Alvo <-
		printf(">>> \'%s\' : %s\n", "A", "Rodar - o Obs para a Esquerda em Torno do Alvo");
		aVisao = aVisao + ANGULO_INC;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unixObs, xObs);
		glUniform1f(unizObs, zObs);
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':																			// Rodar em torno do Alvo ->
		printf(">>> \'%s\' : %s\n", "D", "Rodar - o Obs para a Direita em Torno do Alvo");
		aVisao = aVisao - ANGULO_INC;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unixObs, xObs);
		glUniform1f(unizObs, zObs);
		glutPostRedisplay();
		break;

	case 'f':
	case 'F':																			// + Zoom | O observador aproxima-se
		printf(">>> \'%s\' : %s\n", "F", "+Zoom - Aproximar o Obs ao Alvo");
		rVisao = rVisao - RAIO_INC;
		if (rVisao < RAIO_MIN)
			rVisao = RAIO_MIN;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unixObs, xObs);
		glUniform1f(unizObs, zObs);
		glutPostRedisplay();
		break;

	case 'g':
	case 'G':																			// - Zoom | O observador afasta-se
		printf(">>> \'%s\' : %s\n", "G", "-Zoom - Afastar o Obs do Alvo");
		rVisao = rVisao + RAIO_INC;
		if (rVisao > RAIO_MAX)
			rVisao = RAIO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unixObs, xObs);
		glUniform1f(unizObs, zObs);
		glutPostRedisplay();
		break;

	case 'y':
	case 'Y':																			// Mover Luz 1 para frente -Z
		printf(">>> \'%s\' : %s\n", "Y", "Mover Luz 1 para Frente");
		zLuz = zLuz - MOVE_INC;
		if (zLuz < -DIM_MUNDO_Z)
			zLuz = -DIM_MUNDO_Z;
		glUniform1f(unizLuz, zLuz);
		glutPostRedisplay();
		break;

	case 'u':
	case 'U':																			// Mover Luz 1 para tras Z
		printf(">>> \'%s\' : %s\n", "U", "Mover Luz 1 para Tras");
		zLuz = zLuz + MOVE_INC;
		if (zLuz > DIM_MUNDO_Z)
			zLuz = DIM_MUNDO_Z;
		glUniform1f(unizLuz, zLuz);
		glutPostRedisplay();
		break;

	case 'i':
	case 'I':																			// Mover Luz 1 para esquerda -X
		printf(">>> \'%s\' : %s\n", "I", "Mover Luz 1 para Esquerda");
		xLuz = xLuz - MOVE_INC;
		if (xLuz < -DIM_MUNDO_X)
			xLuz = -DIM_MUNDO_X;
		glUniform1f(unixLuz, xLuz);
		glutPostRedisplay();
		break;

	case 'o':
	case 'O':																			// Mover Luz 1 para direita X
		printf(">>> \'%s\' : %s\n", "O", "Mover Luz 1 para Direita");
		xLuz = xLuz + MOVE_INC;
		if (xLuz > DIM_MUNDO_X)
			xLuz = DIM_MUNDO_X;
		glUniform1f(unixLuz, xLuz);
		glutPostRedisplay();
		break;

	case 'k':
	case 'K':																			// Mover Luz 1 para baixo -Y
		printf(">>> \'%s\' : %s\n", "K", "Mover Luz 1 para Baixo");
		yLuz = yLuz - MOVE_INC;
		if (yLuz < -DIM_MUNDO_Y)
			yLuz = -DIM_MUNDO_Y;
		glUniform1f(uniyLuz, yLuz);
		glutPostRedisplay();
		break;

	case 'l':
	case 'L':																			// Mover Luz 1 para cima Y
		printf(">>> \'%s\' : %s\n", "L", "Mover Luz 1 para Cima");
		yLuz = yLuz + MOVE_INC;
		if (yLuz > DIM_MUNDO_Y)
			yLuz = DIM_MUNDO_Y;
		glUniform1f(uniyLuz, yLuz);
		glutPostRedisplay();
		break;

	case '1':
		printf(">>> \'%s\' : %s\n", "1", "Aumentar Velocidade da Animacao");
		velocidade = velocidade * 1.1;
		tempo = 0.0;
		glUniform1f(unitempo, tempo);
		glUniform1f(univelocidade, velocidade);
		break;

	case '2':
		printf(">>> \'%s\' : %s\n", "2", "Diminuir Velocidade da Animacao");
		velocidade = velocidade * 0.9;
		tempo = 0.0;
		glUniform1f(unitempo, tempo);
		glUniform1f(univelocidade, velocidade);
		break;

	case 27:																			// ESC/Escape >>> sair
		printf(">>> \'%s\' : %s\n", "<ESC>", "Sair/Parar Execucao");
		exit(0);
		break;

	default:
		printf("> ERRO: Tecla \'%c\' Nao Funcional | Press \'H\' para Ajuda.\n", key);
		break;
	}

}


void tecladoEspecial(int key, int x, int y) {
	// EVENTOS:  teclado teclas especiais

	
	if (key == GLUT_KEY_UP) {															// Deslocamento de xObs e xAlvo para a Frente em Z
		printf(">>> \'%s\' : %s\n", "<up>", "Mover - para a Frente (Obs + Alvo)");
		zAlvo = zAlvo - MOVE_INC;
		if (zAlvo < -Z_ALVO_MAX)
			zAlvo = -Z_ALVO_MAX;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unizObs, zObs);
	}


	if (key == GLUT_KEY_DOWN) {															// Deslocamento de xObs e xAlvo para a Tras em Z
		printf(">>> \'%s\' : %s\n", "<down>", "Mover - para Tras (Obs + Alvo)");
		zAlvo = zAlvo + MOVE_INC;
		if (zAlvo > Z_ALVO_MAX)
			zAlvo = Z_ALVO_MAX;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glUniform1f(unizObs, zObs);
	}

	if (key == GLUT_KEY_LEFT) {															// Deslocamento de xObs e xAlvo para a Esquerda <- em X
		printf(">>> \'%s\' : %s\n", "<left>", "Mover - para a Esquerda (Obs + Alvo)");
		xAlvo = xAlvo - MOVE_INC;
		if (xAlvo < -X_ALVO_MAX)
			xAlvo = -X_ALVO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;
		glUniform1f(unixObs, xObs);

	}

	if (key == GLUT_KEY_RIGHT) {														// Deslocamento de xObs e xAlvo para a Direita -> em X
		printf(">>> \'%s\' : %s\n", "<right>", "Mover - para a Direita (Obs + Alvo)");
		xAlvo = xAlvo + MOVE_INC;
		if (xAlvo > X_ALVO_MAX)
			xAlvo = X_ALVO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;
		glUniform1f(unixObs, xObs);
	}

	glutPostRedisplay();																// marks the current window as needing to be redisplayed.
}


void printHelp(void) {
	// Print na Consola: Help

	printf("\n\n########## AJUDA ##########\n");

	printf("#\n");
	printf("# (KEY : FUNCAO)\n");

	printf("#\n");
	printf("# SUPORTE:\n");
	printf("# KEY \'%s\'\t:\t%s\n", "<ESC>", "Sair/Parar Execucao");
	printf("# KEY \'%s\'\t:\t%s\n", "H", "Print Ajuda");
	printf("# KEY \'%s\'\t:\t%s\n", "R", "Reiniciar Todo o Cenario");
	printf("# KEY \'%s\'\t:\t%s\n", "E", "Ligar/Desligar os Eixos Auxiliares");

	printf("#\n");
	printf("# OBSERVADOR Pseudo-Primeira-Pessoa (Meta 3):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "<left>", "Mover - para a Esquerda (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<right>", "Mover - para a Direita (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<up>", "Mover - para a Frente (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<down>", "Mover - para Tras (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "W", "Subir - o Obs em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "S", "Descer - o Obs em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "A", "Rodar - o Obs para a Esquerda em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "D", "Rodar - o Obs para a Direita em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "F", "+Zoom - Aproximar o Obs ao Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "G", "-Zoom - Afastar o Obs do Alvo");

	printf("#\n");
	printf("# ILUMINACAO (Meta 3):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "Y", "Mover Luz 1 para Frente");
	printf("# KEY \'%s\'\t:\t%s\n", "U", "Mover Luz 1 para Tras");
	printf("# KEY \'%s\'\t:\t%s\n", "I", "Mover Luz 1 para Esquerda");
	printf("# KEY \'%s\'\t:\t%s\n", "O", "Mover Luz 1 para Direita");
	printf("# KEY \'%s\'\t:\t%s\n", "K", "Mover Luz 1 para Baixo");
	printf("# KEY \'%s\'\t:\t%s\n", "L", "Mover Luz 1 para Cima");

	printf("#\n");
	printf("# ANIMACAO (Meta 3):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "1", "Aumentar Velocidade da Animacao");
	printf("# KEY \'%s\'\t:\t%s\n", "2", "Diminuir Velocidade da Animacao");

	printf("#\n");
	printf("# NOTAS: \n# Modelo ESTATICO: Sol \n# Modelo GOURAUD (impares): Mercurio, Terra, Jupiter, Urano  \n# Modelo PHONG (pares): Venus, Marte, Saturno, Neptuno \n");
	printf("###########################\n\n");
}


void desenhaEixos(void) {
	// Temporario - Auxiliar do Projeto

	n_planeta = 0;
	glUniform1f(unin_planeta, n_planeta);
	
	tipo = TIPO_ESTATICO;
	glUniform1i(uniTipo, tipo);

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// -X
	glVertex3i(-DIM_MUNDO_X, 0, 0);
	glVertex3i(0, 0, 0);
	glEnd();

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// X
	glVertex3i(0, 0, 0);
	glVertex3i(DIM_MUNDO_X, 0, 0);
	glEnd();

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// -Y
	glVertex3i(0, -DIM_MUNDO_Y, 0);
	glVertex3i(0, 0, 0);
	glEnd();

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// Y
	glVertex3i(0, 0, 0);
	glVertex3i(0, DIM_MUNDO_Y, 0);
	glEnd();

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// -Z
	glVertex3i(0, 0, -DIM_MUNDO_Z);
	glVertex3i(0, 0, 0);
	glEnd();

	glColor3f(BRANCO);
	glBegin(GL_LINES);																	// Z
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, DIM_MUNDO_Z);
	glEnd();
}

