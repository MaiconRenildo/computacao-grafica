#include <GL/glut.h>
#include <cmath>

const char* title = "Casa em OpenGL";
const int windowWidth = 800;
const int windowHeight = 600;
bool whitBackground = true;


void axis_markers(float interval = 0.05f, float length = 0.05f) {
    glColor3f(0.0, 0.0, 0.0); // Cor preta para os marcadores
    glLineWidth(1.0);

    glBegin(GL_LINES);

    // Marcadores ao longo do eixo X
    for (float x = -1.0f; x <= 1.0f; x += interval) {
        if (fabs(x) < 0.0001f) continue; // Pular o centro (0)
        glVertex2f(x, -length);
        glVertex2f(x, length);
    }

    // Marcadores ao longo do eixo Y
    for (float y = -1.0f; y <= 1.0f; y += interval) {
        if (fabs(y) < 0.0001f) continue; // Pular o centro (0)
        glVertex2f(-length, y);
        glVertex2f(length, y);
    }

    glEnd();
}

void cartesian_plane(){
    glLineWidth(2.0); // mais espesso para melhor visualização

    // Eixo X - vermelho
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
    glEnd();

    // Eixo Y - verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
    glEnd();

    axis_markers();   
}

void drawSquare() {
    double side = 0.1;
    double x = -side / 2.0;
    double y = -side / 2.0;
    glBegin(GL_LINE_LOOP); // alterado em relação ao colorful
        glVertex3f(x, y, 0);
        glVertex3f(x + side, y, 0);
        glVertex3f(x + side, y + side, 0);
        glVertex3f(x, y + side, 0);
    glEnd();
}

void drawTriangle() {
    double side = 0.1;
    double halfBase = side / 2.0;
    double height = side;

    glBegin(GL_LINE_LOOP); // alterado em relação ao colorful
        glVertex3f(-halfBase, -height / 2.0, 0);  // canto inferior esquerdo
        glVertex3f(halfBase, -height / 2.0, 0);   // canto inferior direito
        glVertex3f(0.0, height / 2.0, 0);         // vértice superior (topo)
    glEnd();
}


void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    //////////////////////////// corpo da torre - quadrado maior
    glPushMatrix();
        glColor3d(0.5, 0.0, 1.0); // roxo
        glTranslated(0, 0.1, 0.0);
        glScaled(3, 2, 1.0);
        drawSquare(); 
    glPopMatrix();
    ////////////////////////////

    //////////////////////////// porta
    glPushMatrix();
        glColor3d(0.9, 0.0, 1.0);
        glTranslated(0, 0.05, 0.0);
        glScaled(0.7, 1, 1.0);
        drawSquare();
    glPopMatrix();
    ////////////////////////////

    //////////////////////////// torre do meio
    glPushMatrix();
        glColor3d(0.9, 0.8, 1.0);
        glTranslated(0, 0.275, 0.0);
        glScaled(0.8, 1.5, 1.0);
        drawSquare();
    glPopMatrix();

    // janela da torre do meio
    glPushMatrix();
        glColor3d(0.9, 0.8, 0.45);
        glTranslated(0, 0.3, 0.0);
        glScaled(0.2, 0.4, 1.0);
        drawSquare();
    glPopMatrix();

    // telhado da torre do meio
    glPushMatrix();
        glColor3d(0.0, 0.4, 0.0);
        glTranslated(0, 0.4, 0.0);
        drawTriangle();
    glPopMatrix();
    ////////////////////////////

    //////////////////////////// torre à direita
    glPushMatrix();
        glColor3d(0.0, 0.4, 0.0);
        // glTranslated(0, 3, 0.0);
        glTranslated(0.18, 0.15, 0.0);
        glScaled(0.8, 3, 1.0);
        drawSquare();
    glPopMatrix();

    // telhado da torre à direita
    glPushMatrix();
        glColor3d(0.0, 0.8, 0.0);
        glTranslated(0.18, 0.35, 0.0);
        drawTriangle();
    glPopMatrix();

    // janela da torre à direita
    glPushMatrix();
        glColor3d(0.9, 0.8, 0.45);
        glTranslated(0.18, 0.25, 0.0);
        glScaled(0.2, 0.4, 1.0);
        drawSquare();
    glPopMatrix();
    ////////////////////////////

    //////////////////////////// torre à esquerda
    glPushMatrix();
        glColor3d(0.0, 0.4, 0.0);
        glTranslated(-0.18, 0.15, 0.0);
        glScaled(0.8, 3, 1.0);
        drawSquare();
    glPopMatrix();

    // telhado da torre à direita
    glPushMatrix();
        glColor3d(0.0, 0.8, 0.0);
        glTranslated(-0.18, 0.35, 0.0);
        drawTriangle();
    glPopMatrix();

    // janela da torre à esquerda
    glPushMatrix();
        glColor3d(0.9, 0.8, 0.45);
        glTranslated(-0.18, 0.25, 0.0);
        glScaled(0.2, 0.4, 1.0);
        drawSquare();
    glPopMatrix();
    ////////////////////////////

    //////////////////////////// SOL
    glPushMatrix();
        glColor3d(0.0, 0.4, 0.0);
        glTranslated(0.30, 0.40, 0.0);
        glScaled(0.8, 0.8, 1.0);
        drawSquare();
    glPopMatrix();    

    glPushMatrix();
        glColor3d(0.0, 0.7, 0.0);
        glTranslated(0.30, 0.40, 0.0);
        glScaled(0.8, 0.8, 1.0);
        glRotated(45.0, 0.0, 0.0, 1.0);      
        drawSquare();
    glPopMatrix();
    ////////////////////////////

    cartesian_plane();

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
    glOrtho(-1, 1, -1, 1, -1, 1); // alterado em relação ao colorful
    
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}