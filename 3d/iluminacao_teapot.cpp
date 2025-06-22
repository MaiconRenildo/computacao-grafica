// TeaPot3D.cpp - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualiza??o
// de objetos 3D.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLfloat r=1.0, g=1.0, b=1.0;
GLint especMaterial = 60;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void){
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; // original

	// 5 - Altere o valor de inicialização da variável luzAmbiente para {0.1,0.1,0.1,1.0}, compile e execute o
	// programa. Altere o valor desta mesma variável para {0.4,0.4,0.4,1.0}, compile e execute o
	// programa. Agora altere o valor desta mesma variável para {0.8,0.8,0.8,1.0}, compile e execute o
	// programa.
	// GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0}; // questão 5
	// R:Quando o valor da variável luzAmbiente é aumentado, a cena fica 
	// progressivamente mais iluminada de forma uniforme. Com valores baixos, a 
	// cena fica escura e com sombras mais evidentes. Com valores médios, a iluminação
	// geral melhora e as sombras ficam menos intensas. Com valores altos, a cena fica 
	// muito clara, com pouca distinção entre áreas iluminadas e áreas de sombra. Isso 
	// acontece porque a luz ambiente afeta todos os pontos da cena igualmente, independente
	// da posição da fonte de luz, resultando em uma iluminação geral mais forte à medida
	// que o valor aumenta.
	
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
	GLfloat luzEspecular[4]={r, g, b, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};

	// 4- Agora coloque as linhas de código que aparecem abaixo em comentário:
	// GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	// glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	// R: Ao comentar essas linhas, a imagem perde o brilho especular.
	// As superfícies dos objetos ficam foscas e opacas, sem os reflexos 
	// brilhantes da luz. Isso acontece porque tanto a componente especular 
	// da luz quanto a capacidade do material de refletir brilho foram desativadas.
	// A iluminação agora é composta apenas das componentes ambiente e difusa, tornando a
	// cena visualmente mais simples e com menos realismo.


	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

// Fun??o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela de visualiza??o com a cor
	// de fundo definida previamente
	// glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao(); // INCLUA ESTA LINHA

	// Troca cor corrente para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	glutSolidTeapot(50.0f);

	// Execu??o dos comandos de desenho
	glutSwapBuffers();
}

// Inicialização
void Inicializa(void){
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	// Habilita o modelo de colorização de Gouraud
	// glShadeModel(GL_SMOOTH);
	glShadeModel(GL_FLAT);
	
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=50;
	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsZ = 180;
}


// Fun??o usada para especificar a posi??o do observador virtual
void PosicionaObservador(void){
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao(); // INCLUA ESTA LINHA
	// Especifica posi??o do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Fun??o usada para especificar o volume de visualiza??o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje??o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje??o
	glLoadIdentity();

	// Especifica a proje??o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}


// Fun??o callback chamada quando o tamanho da janela ? alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens?es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre??o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


// Fun??o callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;

	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback para gerenciar eventos de teclas normais
void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1': r = (r > 0.1f) ? r - 0.1f : 0.0f; break;
        case '2': g = (g > 0.1f) ? g - 0.1f : 0.0f; break;
        case '3': b = (b > 0.1f) ? b - 0.1f : 0.0f; break;
        case '4': r = (r < 0.9f) ? r + 0.1f : 1.0f; break;
        case '5': g = (g < 0.9f) ? g + 0.1f : 1.0f; break;
        case '6': b = (b < 0.9f) ? b + 0.1f : 1.0f; break;

        case 'p' : case 'P' :
            if (especMaterial <= 155) especMaterial += 5;
			std::cout << "Specular Material: " << especMaterial << std::endl;
            break;
         case 'b' : case 'B' :
            if (especMaterial >= 5) especMaterial -= 5;
			std::cout << "Specular Material: " << especMaterial << std::endl;
            break;

    }
	std::cout << "R: " << r 
          << " G: " << g 
          << " B: " << b << std::endl;
    DefineIluminacao(); // Chame para atualizar a luz
    glutPostRedisplay(); // Solicita redesenho
}

// Programa Principal
int main()
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posi??o inicial da janela GLUT
    glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de um teapot com ilumina??o");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);
	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
	// Registra a funcao callback para tratamento do redimensionamento da janela
    glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);
	glutKeyboardFunc(Teclado); 
	Inicializa();
	glutMainLoop();
}
