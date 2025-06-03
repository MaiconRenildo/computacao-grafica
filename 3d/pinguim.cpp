#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

GLfloat angle, fAspect, rotX, rotY;
GLfloat windowWidth = 400;
GLfloat windowHeight = 400;
GLdouble obsX, obsY, obsZ;
GLfloat r, g, b;
GLint especMaterial; 

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    // GLfloat luzAmbiente[4]= {0.1,0.1,0.1,1.0};
    // GLfloat luzAmbiente[4]=  {0.4,0.4,0.4,1.0};
    
    // GLfloat luzAmbiente[4]=  {0.8,0.8,0.8,1.0};
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
    // Capacidade de brilho do material
    // GLfloat especularidade[4]={r,g,b,1.0};
    // GLint especMaterial = 60;
    // Define a refletância do material
    // glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    // glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void drawAxes() {
    glLineWidth(2.0); // Espessura da linha
    glBegin(GL_LINES);

    // Eixo X (Vermelho)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    // Eixo Y (Verde)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    // Eixo Z (Azul)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -10.0);
    glVertex3f(0.0, 0.0, 10.0);

    glEnd();
    glLineWidth(1.0); // Volta à espessura padrão
}

void drawSphere(){
    glPushMatrix();
        glPushMatrix(); 
            glutSolidSphere(0.5, 20,20);
        glPopMatrix();
    glPopMatrix();
}

void drawPyramid(float size, float height){
    glBegin(GL_TRIANGLES);
        // Vértices da base (no plano XY)
        float s2 = size / 2.0;
        // Triângulo 1 da base
        glNormal3f(0.0, -1.0, 0.0); // Normal para baixo
        glVertex3f(-s2, 0.0, -s2);
        glVertex3f(s2, 0.0, -s2);
        glVertex3f(s2, 0.0, s2);

        // Triângulo 2 da base
        glNormal3f(0.0, -1.0, 0.0); // Normal para baixo
        glVertex3f(-s2, 0.0, -s2);
        glVertex3f(s2, 0.0, s2);
        glVertex3f(-s2, 0.0, s2);
    glEnd();

    glBegin(GL_TRIANGLES);
        // Ápice da pirâmide (no eixo Y, acima da base)
        float topY = height; // Altura da pirâmide
        float baseX = s2;
        float baseZ = s2;

        // Face frontal (negativo Z)
        glNormal3f(0.0, height, -size); // Normal para fora da face (aproximado)
        glVertex3f(0.0, topY, 0.0); // Ápice
        glVertex3f(-baseX, 0.0, -baseZ);
        glVertex3f(baseX, 0.0, -baseZ);

        // Face direita (positivo X)
        glNormal3f(size, height, 0.0); // Normal para fora da face (aproximado)
        glVertex3f(0.0, topY, 0.0); // Ápice
        glVertex3f(baseX, 0.0, -baseZ);
        glVertex3f(baseX, 0.0, baseZ);

        // Face traseira (positivo Z)
        glNormal3f(0.0, height, size); // Normal para fora da face (aproximado)
        glVertex3f(0.0, topY, 0.0); // Ápice
        glVertex3f(baseX, 0.0, baseZ);
        glVertex3f(-baseX, 0.0, baseZ);

        // Face esquerda (negativo X)
        glNormal3f(-size, height, 0.0); // Normal para fora da face (aproximado)
        glVertex3f(0.0, topY, 0.0); // Ápice
        glVertex3f(-baseX, 0.0, baseZ);
        glVertex3f(-baseX, 0.0, -baseZ);
    glEnd();
}

////////////////////////////////// PENGUIM
void drawPenguimBody(){
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
        glScalef(1.0, 1.3, 1.0); // Corpo um pouco alongado
        drawSphere();
    glPopMatrix();
}

void drawPenguimStomach(){
    glColor3f(1.0, 1.0, 1.0); // Branco
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.14); // Ajuste a posição para "dentro" do corpo
        glScalef(0.8, 1.2, 0.8); // Escala para a barriga
        drawSphere();
    glPopMatrix();
}

void drawCone(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    gluDisk(quadric, 0, baseRadius, slices, 1);
    gluDeleteQuadric(quadric);
}

// void drawBeak(){
    // glColor3f(1.0, 0.6, 0.0); // laranja
    // glPushMatrix();
    //     glTranslatef(0.0, 1.5, 0.35);
    //     glRotatef(-30.0, 1.0, 0.0, 0.0);
    //     glScalef(0.1, 0.25, 0.25); // (largura, profundidade, comprimento)
    //     glTranslatef(0.0, 0.0, 0.0);
    //     drawPyramid(1.0, 1.0); // Tamanho base 1
    // glPopMatrix();
// }


void drawBeak(){
    glColor3f(1.0, 0.6, 0.0); // laranja
    glPushMatrix();
        glTranslatef(0.0, 1.5, 0.30);
        glScalef(0.1, 0.15, 0.15);
        drawCone(1.0, 0.0, 1.0, 20, 20);
    glPopMatrix();
}

void drawDadEyes(){
    glPushMatrix();
        glTranslatef(0, 0, -0.45);
        // olho esquerdo
        glColor3f(0.0, 0.0, 0.0); // Preto
        glPushMatrix(); // Olho Esquerdo
            glTranslatef(-0.25, 1.6, 0.65); // Posição
            glScalef(0.1, 0.1, 0.1); // Tamanho pequeno
            drawSphere();

        glPopMatrix();
        glColor3f(1.0, 1.0, 1.0); // Branco
        glPushMatrix();
            glTranslatef(-0.23, 1.62, 0.7);
            glScalef(0.045, 0.045, 0.045);
            drawSphere();
        glPopMatrix();

        // olho direito
        glColor3f(0.0, 0.0, 0.0); // Preto
        glPushMatrix(); // Olho Direito
            glTranslatef(0.25, 1.6, 0.65); // Posição
            glScalef(0.1, 0.1, 0.1); // Tamanho pequeno
            drawSphere();
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0); // Branco
        glPushMatrix();
            glTranslatef(0.27, 1.62, 0.7);
            glScalef(0.045, 0.045, 0.045);
            drawSphere();
        glPopMatrix();
    
    glPopMatrix();
}

void drawPenguimHead(){
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(0.0, -0.6, 0.0);
        // cabeça
        glPushMatrix();
            glTranslatef(0.0, 1.5, 0.0);
            glScalef(0.7, 0.7, 0.7);
            drawSphere();
        glPopMatrix();
    
        drawBeak();
        drawDadEyes();
    glPopMatrix();
}

void drawPenguimWings(){
    glColor3f(0.05, 0.05, 0.05); // Preto
    glTranslatef(0, -0.3, 0.0);
    glPushMatrix();
        // esquerda
        glPushMatrix();
            glTranslatef(-0.5, 0.5, 0.0);
            glRotatef(-30.0, 0.0, 0.0, 1.0);
            glScalef(0.2, 0.8, 0.5);
            drawSphere();
        glPopMatrix();
        // direita
        glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            glRotatef(30.0, 0.0, 0.0, 1.0);
            glScalef(0.2, 0.8, 0.5);
            drawSphere();
        glPopMatrix();
    glPopMatrix();
}

void drawPenguimFeet(){
    glColor3f(1.0, 0.6, 0.0); // laranja
    // esquerdo
    glPushMatrix();
        glTranslatef(-0.2, -0.3, 0.3);
        glScalef(0.35, 0.1, 0.6);
        drawSphere();
    glPopMatrix();
    // direito
    glPushMatrix();
        glTranslatef(0.2, -0.3, 0.3);
        glScalef(0.35, 0.1, 0.6);
        drawSphere();
    glPopMatrix();
}

void drawPenguim(){
    glPushMatrix();
        drawPenguimHead();
        drawPenguimBody();
        drawPenguimStomach();
        drawPenguimWings();
        drawPenguimFeet();
    glPopMatrix();
}

void drawPenguimDad(){
    glPushMatrix();
        glTranslatef(2.0, 0.65, 0.0);
        drawPenguim();
    glPopMatrix();
}

void drawPenguimBaby(){
    glPushMatrix();
        glTranslatef(0.0, 0.41, 0.0);
        glScalef(0.8, 0.6, 0.8);
        drawPenguim();
    glPopMatrix();
}
//////////////////////////////////

void drawFish() {
    glPushMatrix();
        glTranslatef(-2.0, 0.40, 0.0);

        // corpo
        //frente
        glColor3f(1.0, 0.4, 0.0);
        glPushMatrix();
            glScalef(1.5, 0.8, 0.8);
            drawSphere();
        glPopMatrix();
        //trás
        glPushMatrix();
            glTranslatef(-0.5, 0.0, 0.0);
            glScalef(1.0, 0.6, 0.6);
            drawSphere();
        glPopMatrix();

        // rabo
        glColor3f(1.0, 0.3, 0.0);
        glPushMatrix();
            glTranslatef(-1.0, 0.0, 0.0);
            glScalef(0.5, 0.5, 0.1);
            // primeira metade
            glPushMatrix();
                glTranslatef(0.0, 0.25, 0.0);
                glRotatef(-45.0, 0.0, 0.0, 1.0);
                drawSphere();
            glPopMatrix();
            // resto
            glPushMatrix();
                glTranslatef(0.0, -0.25, 0.0);
                glRotatef(45.0, 0.0, 0.0, 1.0);
                drawSphere();
            glPopMatrix();
        glPopMatrix();

        // nadadeiras dorsais
        glColor3f(1.0, 0.3, 0.0);
        glPushMatrix();
            glTranslatef(0.0, 0.35, 0.0);
            glScalef(0.2, 0.2, 0.2);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            drawPyramid(1.0, 1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.1, 0.35, 0.0);
            glScalef(0.2, 0.2, 0.2);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            drawPyramid(1.0, 1.0);
        glPopMatrix();

        // nadadeiras laterais
        glColor3f(1.0, 0.3, 0.0);
        // esquerda
        glPushMatrix();
            glTranslatef(0.3, 0.0, 0.45);
            glRotatef(-45.0, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.1, 0.2);
            drawSphere();
        glPopMatrix();
        // direita
        glPushMatrix();
            glTranslatef(0.3, 0.0, -0.45);
            glRotatef(45.0, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.1, 0.2);
            drawSphere();
        glPopMatrix();

        // olhos
        glColor3f(0.0, 0.0, 0.0);
        // esquerdo
        glPushMatrix();
            glTranslatef(0.5, 0.1, 0.3);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();
        // direito
        glPushMatrix();
            glTranslatef(0.5, 0.1, -0.3);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();

        // boca
        glColor3f(0.8, 0.2, 0.0);
        glPushMatrix();
            glTranslatef(0.75, 0.0, 0.0);
            glScalef(0.1, 0.1, 0.2);
            drawSphere();
        glPopMatrix();
    glPopMatrix();
}

// Fun??o callback chamada para fazer o desenho
void Desenha(void){
	// Limpa a janela de visualiza??o com a cor
	// de fundo definida previamente
	// glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DefineIluminacao();
    drawAxes();
	// Troca cor corrente para azul
	glColor3f(0.0f, 0.0f, 1.0f);
    drawPenguimDad();
    drawPenguimBaby();
    drawFish();
	// Desenha o teapot com a cor corrente (wire-frame)
	// glutWireTeapot(50.0f);
    
    // glutSolidTeapot(50.0f),
    // Desenha um cubo

	// Execu??o dos comandos de desenho
	glutSwapBuffers();
}

void Inicializa(void){
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    especMaterial = 60;

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
    obsZ = 5;
}

// Fun??o usada para especificar a posi??o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
    DefineIluminacao();
	// Especifica posi??o do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Fun??o usada para especificar o volume de visualiza??o
void EspecificaParametrosVisualizacao(void){
	// Especifica sistema de coordenadas de proje??o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje??o
	glLoadIdentity();

    // if (windowWidth <= windowHeight) {
    //     // width is smaller, so stretch out the height
    //     glOrtho(-2.5, 2.5, -2.5/fAspect, 2.5/fAspect, -10.0, 10.0);
    // } else {
    //     // height is smaller, so stretch out the width
    //     glOrtho(-2.5*fAspect, 2.5*fAspect, -2.5, 2.5, -10.0, 10.0);
    // }
    
	// Especifica a proje??o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,190);

	PosicionaObservador();
}


// Fun??o callback chamada quando o tamanho da janela ? alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis?o por zero
    windowHeight = h;
    windowWidth = w;
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
            break;
         case 'b' : case 'B' :
            if (especMaterial >= 5) especMaterial -= 5;
            break;
        // case GLUT_KEY_F1: // Aumenta especMaterial
        //     if (especMaterial <= 155) especMaterial += 5;
        //     break;
        // case GLUT_KEY_F2: // Diminui especMaterial
        //     if (especMaterial >= 5) especMaterial -= 5;
        //     break;

        case 27: exit(0); // ESC para sair
    }
    DefineIluminacao(); // Chame para atualizar a luz
    glutPostRedisplay(); // Solicita redesenho
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
        // case GLUT_KEY_F1: // Aumenta especMaterial
        //     if (especMaterial <= 155) especMaterial += 5;
        //     break;
        // case GLUT_KEY_F2: // Diminui especMaterial
        //     if (especMaterial >= 5) especMaterial -= 5;
        //     break;
	}
	PosicionaObservador();
	glutPostRedisplay();
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
	glutInitWindowSize(windowWidth, windowHeight);

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
