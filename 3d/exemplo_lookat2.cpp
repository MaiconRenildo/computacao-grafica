#include <GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST);  
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  
}

// Função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a câmera (posição, ponto a olhar, vetor "up")
    gluLookAt(0.0, 0.0, 5.1,  // z acima de 5 exibe o branco
              0.0, 0.0, 0.0,  // Para onde a câmera olha 
              0.0, 1.0, 0.0); // Vetor "up" 


    // branco -> z=-5
    glPushMatrix();
    // Marcador para Z+
      glTranslatef(0.0f, 0.0f, -5.0); // Move para Z+
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Roda o cone para apontar para +Z
      glColor3f(1.0f, 1.0f, 1.0f);
      glutSolidCone(0.3f, 1.0f, 20, 20);
    glPopMatrix();

    // azul -> z=5
    glPushMatrix();
    // Marcador para Z+
      glTranslatef(0.0f, 0.0f, 5.0); // Move para Z+
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Roda o cone para apontar para +Z
      glColor3f(0.0f, 0.0f, 0.8f); // azul escuro para Z+
      glutSolidCone(0.3f, 1.0f, 20, 20);
    glPopMatrix();


    glutSwapBuffers(); 
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(60.0, aspect, 1.0, 100.0); // Projeção em perspectiva
    glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, 1.0, 20.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exemplos com LookAt");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}