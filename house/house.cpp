///////////////////////////// QUESTÃO 1

#include <GL/glut.h>
#include <cmath>

const char* title = "Casa em OpenGL";
const int windowWidth = 800;
const int windowHeight = 600;
bool whitBackground = true;

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // retangulo maior(base)
    glColor3f(0.5, 0.0, 1.0); // roxo
    float x = -0.3;
    float y = -0.3;
    float width = 0.4;
    float height = 0.6;
    glBegin(GL_QUADS);
        glVertex2f(x, y); // -0.3, -0.3
        glVertex2f(x + height, y); // 0.3, -0.3
        glVertex2f(x + height, y + width); // 0.3, 0.1
        glVertex2f(x, y + width); // -0.3, 0.1
    glEnd();

    // triangulo(telhado)
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    float x1 = -0.4;
    float y1 = 0.1;
    float x2 = 0.4;
    float y2 = 0.1;
    float x3 = 0.0;
    float y3 = 0.5;
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();

    // porta
    glColor3f(1.0, 1.0, 1.0); // Branco
    x = -0.15;
    y = -0.29;
    width = 0.15;
    height = 0.3;
    glBegin(GL_QUADS);
        glVertex2f(x, y); // -0.3, -0.3
        glVertex2f(x + width, y); // 0.3, -0.3
        glVertex2f(x + width, y + height); // 0.3, 0.1
        glVertex2f(x, y + height); // -0.3, 0.1
    glEnd();

    // // janela
    glColor3f(1.0, 1.0, 1.0); // Branco
    x = 0.1;
    y = -0.15;
    width = 0.15;
    height = 0.15;
    glBegin(GL_QUADS);
        glVertex2f(x, y); // -0.3, -0.3
        glVertex2f(x + width, y); // 0.3, -0.3
        glVertex2f(x + width, y + height); // 0.3, 0.1
        glVertex2f(x, y + height); // -0.3, 0.1
    glEnd();

    // linhas da janela
    glColor3f(0.0, 0.0, 0.0); // preto
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(x+(width/2), y ); // -0.3, 0.1
        glVertex2f(x+(width/2), y +height); // -0.3, 0.1
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(x, y +(height)/2); // -0.3, 0.1
        glVertex2f(x+width, y +(height)/2); // -0.3, 0.1
    glEnd();

    glFlush();
}

void keyboard(unsigned char tecla, int x, int y) {
    if (tecla == 32) { // espaço
        whitBackground = !whitBackground;
        glClearColor(whitBackground ? 1.0 : 0.0, whitBackground ? 1.0 : 0.0, whitBackground ? 1.0 : 0.0, 1.0);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);

    glClearColor(1.0, 1.0, 1.0, 1.0); // fundo branco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

/////////////////////////////
