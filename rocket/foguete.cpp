#include <GL/glut.h>
#include <cmath>

const char* title = "Foguete";
const int windowWidth = 800;
const int windowHeight = 600;
bool whitBackground = true;
const double PI = 3.14;
const float orthoValue = 8.0;

void axis_markers() {
    float interval = (5*orthoValue)/100;
    float length = (5*orthoValue)/100;
    glColor3f(1.0, 0.5, 0.0); // Cor preta para os marcadores
    glLineWidth(1.0);

    glBegin(GL_LINES);

    // Marcadores ao longo do eixo X
    for (float x = -orthoValue; x <= orthoValue; x += interval) {
        if (fabs(x) < 0.0001f) continue; // Pular o centro (0)
        glVertex2f(x, -length);
        glVertex2f(x, length);
    }

    // Marcadores ao longo do eixo Y
    for (float y = -orthoValue; y <= orthoValue; y += interval) {
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
        glVertex2f(-orthoValue, 0.0f);
        glVertex2f(orthoValue, 0.0f);
    glEnd();

    // Eixo Y - verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.0f, -orthoValue);
        glVertex2f(0.0f, orthoValue);
    glEnd();

    axis_markers();   
}


void drawSquare() { 
    glBegin(GL_LINE_LOOP);
        glVertex3f(1.0, 1.0, 0.0);   
        glVertex3f(-1.0, 1.0, 0.0);  
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void drawEquilateralTriangle() {
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void drawRightTriangle() {
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void drawCircle(double radius){
    int d;
    glBegin(GL_LINE_LOOP);
    for(d = 0; d < 32; d++){
        double angle =  (2*PI/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-orthoValue, orthoValue, -orthoValue, orthoValue, -orthoValue, orthoValue);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    // cartesian_plane(); // utilizado como auxílio para fazer o desenho
    glColor3f(0, 0, 0);

    ////////////////////////
    //////////// corpo
    glPushMatrix();
        glTranslated(0.0, 2.0, 0.0);
        glScaled(1.0, 2.0, 1.0); 
        drawSquare();
    glPopMatrix();
    ////////////////////////

    ////////////////////////
    /////////// topo
    glPushMatrix();
        glTranslated(0.0, 4.0, 0.0);
        drawEquilateralTriangle();
    glPopMatrix();
    ////////////////////////

    ////////////////////////
    //////////// janela superior
    glPushMatrix();
        glTranslated(0.0, 2.0, 0.0);
        drawCircle(0.35);
    glPopMatrix();

    //////////// janela inferior
    glPushMatrix();
        glTranslated(0.0, 3.0, 0.0);
        drawCircle(0.35);
    glPopMatrix();
    ////////////////////////

    ////////////////////////
    ///////////// asa direita
    glPushMatrix();
        glTranslated(1.5, 0.5, 0.0);  
        glScaled(0.5, 0.5, 1.0);       
        drawRightTriangle();
    glPopMatrix();

    //////////// asa esquerda
    glPushMatrix();
        glTranslated(-1.5, 0.5, 0.0);  
        glScaled(0.5, 0.5, 1.0);       
        glRotated(90.0, 0.0, 0.0, 1.0);
        drawRightTriangle();
    glPopMatrix();
    ////////////////////////

    //////////////////////// fogo
    //////////// fogo esquerda
    glPushMatrix();
        glTranslated(-0.6, -0.55, 1.0);
        glScaled(0.20, 0.55, 1.0);
        drawSquare();
    glPopMatrix();

    //////////// fogo meio
    glPushMatrix();
        glTranslated(0, -0.55, 1.0);
        glScaled(0.20, 0.55, 1.0);
        drawSquare();
    glPopMatrix();

    //////////// fogo direita
    glPushMatrix();
        glTranslated(0.6, -0.55, 1.0);
        glScaled(0.20, 0.55, 1.0);
        drawSquare();
    glPopMatrix();
    ////////////////////////


    glPushMatrix();
        glTranslated(0.45, +0.45, 1.0);
        glScaled(0.30, 0.30, 1.0);
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.45, +0.45, 1.0);
        glScaled(0.30, 0.30, 1.0);
        drawSquare();
    glPopMatrix();


    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}