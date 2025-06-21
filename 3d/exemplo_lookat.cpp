#include <GL/glut.h>

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

// Função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    // Define a câmera (posição, ponto a olhar, vetor "up")
    gluLookAt(0.0, 0.0, 6.0,  // Posição da câmera (0, 0, 6)
              0.0, 0.0, 0.0,  // Para onde a câmera olha 
              0.0, 1.0, 0.0); // Vetor "up" 

    // Cubo na origem (0,0,0)
    cuboBranco(); 

    // Cubo nas coordendas (0, 1, 5) 
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 5.0f);
        cuboAmarelo();  
    glPopMatrix();

    glutSwapBuffers(); 
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 1.0, 100.0); // Projeção em perspectiva

    glMatrixMode(GL_MODELVIEW);
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