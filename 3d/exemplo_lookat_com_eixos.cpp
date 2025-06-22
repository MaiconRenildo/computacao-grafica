#include <GL/glut.h>
#include <iostream>

GLfloat angle=60, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ = 6;

void cuboBranco(){
    glColor3f(1.0f, 1.0f, 1.0f); // Cubo branco
    glutSolidCube(1.0); 
}

void cuboAmarelo(){
    glColor3f(1.0f, 1.0f, 0.0f); // Cubo amarelo
    glutSolidCube(1.0); 
}

void init() {
    glEnable(GL_DEPTH_TEST);  
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  
}

void drawAxes(){
    glLineWidth(2.0); // Espessura da linha
    glBegin(GL_LINES);
    
    float limit = 10.0;
    // Eixo X
    glColor3f(0.8, 0.0, 0.0); // vermelho escuro para X+ (positivo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(limit, 0.0, 0.0);
    glColor3f(1.0, 0.6, 0.6); // vermelho claro para X- (negativo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(-limit, 0.0, 0.0);
  
    // Eixo Y
    glColor3f(0.0, 0.8, 0.0); // verde escuro para Y+ (positivo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, limit, 0.0);
    glColor3f(0.6, 1.0, 0.6); // verde claro para Y- (negativo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, -limit, 0.0);
  
    // Eixo Z
    glColor3f(0.0, 0.0, 0.8); // azul escuro para Z+ (positivo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, limit);
    glColor3f(0.6, 0.6, 1.0); // azul claro para Z- (negativo)
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, -limit);
  
    glEnd();
  
    glLineWidth(1.0); // Volta à espessura padrão
}
  
// Função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a câmera (posição, ponto a olhar, vetor "up")
    // gluLookAt(0.0, 0.0, 6.0,  // Posição da câmera (0, 0, 6)
    //           0.0, 0.0, 0.0,  // Para onde a câmera olha 
    //           0.0, 1.0, 0.0); // Vetor "up" 
    glTranslatef(0,0,-obsZ); // z=6
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);

    // Cubo na origem (0,0,0)
    cuboBranco(); 

    // Cubo nas coordendas (0, 1, 5) 
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 5.0f);
        cuboAmarelo();  
    glPopMatrix();

    drawAxes();

    glutSwapBuffers(); 
}

void adjustProjection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 1.0, 100.0); // Projeção em perspectiva
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    if (h == 0) h = 1;
    fAspect = (float)w / (float)h;
    adjustProjection();
}

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

    adjustProjection();
	glutPostRedisplay();
}

void TeclasEspeciais (int tecla, int x, int y){
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
	glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exemplos com LookAt");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutSpecialFunc(TeclasEspeciais);
	glutMouseFunc(GerenciaMouse);
    glutMainLoop();
    return 0;
}