



#include <GL/glut.h>
#include <cmath>

const char* title = "Quadro do carrinho";
int windowWidth = 800;
int windowHeight = 600;
bool whitBackground = true;
const double PI = 3.14;
const float orthoValue = 8.0;
const float squareWidth = 1.0;

// declare generic code
void reset_modelview_matrix();
void reset_projection_matrix();
void init();

///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// BASE CODE
//////////////////////// CARTESIAN PLANE
void axis_markers() {
    float interval = (6.25*orthoValue)/100;
    float length = (6.25*orthoValue)/100;
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
////////////////////////

//////////////////////// POLYGONS
void drawSquare() { 
    glBegin(GL_POLYGON);
        glVertex3f(squareWidth/2, squareWidth/2, 0.0);   
        glVertex3f(-squareWidth/2, squareWidth/2, 0.0);  
        glVertex3f(-squareWidth/2, -squareWidth/2, 0.0);
        glVertex3f(squareWidth/2, -squareWidth/2, 0.0);
    glEnd();
}

void drawBlade(){
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -1.0, 0.0);
    glEnd();
}

void drawCircle(double radius){
    int d;
    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++){
        double angle =  (2*PI/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}
////////////////////////

///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// PAINTING
void drawWheel(){
    float extern_radius = 0.28;
    float intern_radius = 0.10; // Raio interno onde os raios começam

    glPushMatrix();
        glColor3f(0, 0, 0);
        drawCircle(0.35);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        drawCircle(extern_radius);
    glPopMatrix();

   // Desenhar os raios
   glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        int num_radios = 8;
        glBegin(GL_LINES);
            for (int i = 0; i < num_radios; ++i) {
                float angle = 2.0 * M_PI * i / num_radios;
                glVertex3f(cos(angle) * intern_radius, sin(angle) * intern_radius, 0);
                glVertex3f(cos(angle) * extern_radius, sin(angle) * extern_radius, 0);
            }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 0, 0);
        drawCircle(intern_radius);
    glPopMatrix();
}

void drawBody(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslated(0.0, 0.8, 0.0);
        glScaled(2.5, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslated(-0.4, 1.3, 0.0);
        glScaled(1.1, 0.5, 1.0); 
        drawSquare();
    glPopMatrix();
}

void drawCar(){
    glPushMatrix();
        glTranslated(0.8, 0.38, 0.0);
        drawWheel();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.8, 0.38, 0.0);
        drawWheel();
    glPopMatrix();

    drawBody();
}

void drawTrack(){
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glScaled(10, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslated(0.0, 0.35, 0.0);
        glScaled(10, 0.1, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslated(0.0, 0.65, 0.0);
        glScaled(10, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();
}


void drawMountains(){
    glPushMatrix();
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
            glVertex3f(5.0f, -1.2f, 0.0f); // direita baixo
            glVertex3f(-5.0f, -1.2f, 0.0f); // esquerda baixo
            glVertex3f(-5.0f, 1.5f, 0.0f); // esquerda cima
            glVertex3f(-3.5f, 2.9f, 0.0f); // primeiro topo(esquerda)
            glVertex3f(-3.25f, 2.3f, 0.0f); // primeiro vale(esquerda)
            glVertex3f(-1.5f, 4.0f, 0.0f); // segundo topo(meio)
            glVertex3f(1.2f, 1.4f, 0.0f); // segundo vale
            glVertex3f(3.0f, 3.0f, 0.0f); // terceiro topo(direita)
            glVertex3f(5.0, 1.0, 0.0); // direita cima
        glEnd();
    glPopMatrix();
}

void drawBackground(){
    glPushMatrix();
        glTranslated(0, 2.8, 0.0);
        glColor3f(1, 0.8, 0.95);
        glScaled(10, 8, 1.0); 
        drawSquare();
    glPopMatrix();
}

void drawBlades(){
    glColor3f(0.8, 0.0, 0.0);
    glPushMatrix();
        glRotated(85.0, 0.0, 0.0, 1.0);
        glTranslated(0.75, 0.0, 0.0);  
        glScaled(0.75, 0.2, 1.0);
        drawBlade();
    glPopMatrix();

    glPushMatrix();
        glRotated(205.0, 0.0, 0.0, 1.0);
        glTranslated(0.75, 0.0, 0.0);  
        glScaled(0.75, 0.2, 1.0);
        drawBlade();
    glPopMatrix();

    glPushMatrix();
        glRotated(325.0, 0.0, 0.0, 1.0);
        glTranslated(0.75, 0.0, 0.0);  
        glScaled(0.75, 0.2, 1.0);
        drawBlade();
    glPopMatrix();
}

void drawWindTower(float rotate=10.0){
    // pás
    glPushMatrix();
        // glRotated(rotate, 0.0, 0.0, 1.0);
        drawBlades();
    glPopMatrix();

    // poste
    glPushMatrix();
        glTranslated(0.0, -2, 0.0);
        glScaled(0.15, 4, 1.0); 
        drawSquare();
    glPopMatrix();

    // circulo central
    glPushMatrix();
        drawCircle(0.15);
    glPopMatrix();
}

void drawWindTowers(){
    glPushMatrix();
        glTranslated(-4.0, 4, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower(10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.0, 5, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower(-10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0, 4, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower();
    glPopMatrix();
}

void drawSun(){
    float extern_radius = 0.28;
    float intern_radius = 0.0; // Raio interno onde os raios começam

    glPushMatrix();
        glTranslated(4, 5, 0.0);
        glScaled(2, 2, 1.0); 
        // Desenhar os raios
        glPushMatrix();
            glColor3f(1.0f, 1.0f, 0.0f);
            int num_radios = 12;
            glBegin(GL_LINES);
                for (int i = 0; i < num_radios; ++i) {
                    float angle = 2.0 * M_PI * i / num_radios;
                    glVertex3f(cos(angle) * intern_radius, sin(angle) * intern_radius, 0);
                    glVertex3f(cos(angle) * (extern_radius+0.1), sin(angle) * (extern_radius+0.1), 0);
                }
            glEnd();
        glPopMatrix();
        glPushMatrix();
            glColor3f(1.0f, 1.0f, 0.0f);
            drawCircle(extern_radius);
        glPopMatrix();
    glPopMatrix();
}

void drawPicture(){
    drawBackground();
    drawWindTowers();
    drawMountains();
    drawTrack();
    drawCar();
    drawSun();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    reset_modelview_matrix();
    drawPicture();
    // cartesian_plane();
    glFlush();
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////// GENERIC CODE
void reset_modelview_matrix(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reset_projection_matrix(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    reset_projection_matrix();
    glOrtho(-orthoValue, orthoValue, -orthoValue, orthoValue, -orthoValue, orthoValue);
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
///////////////////////////////////////////////////////////////////