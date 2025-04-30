#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>  // para rand() e srand()
#include <ctime>    // para time()
#include <vector>
#include <tuple>

const char* title = "Penguim Game";
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

void drawTriangle() {
    double side = 0.1;
    double halfBase = side / 2.0;
    double height = side;

    glBegin(GL_TRIANGLES);
        glVertex3d(-halfBase, -height / 2.0, 0.0);  // canto inferior esquerdo
        glVertex3d(halfBase, -height / 2.0, 0.0);   // canto inferior direito
        glVertex3d(0.0, height / 2.0, 0.0);         // vértice superior (topo)
    glEnd();
}

void drawPolygonCircle(double radius){
    int d;
    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++){
        double angle =  (2*PI/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}

void drawEllipse(double radiusX, double radiusY) {
    int d;
    glBegin(GL_LINE_LOOP);
    for(d = 0; d < 32; d++) {
        double angle = (2 * PI / 32) * d;
        glVertex3f(radiusX * cos(angle), radiusY * sin(angle), 0);
    }
    glEnd();
}

void drawPolygonEllipse(double radiusX, double radiusY) {
    int d;
    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++) {
        double angle = (2 * PI / 32) * d;
        glVertex3f(radiusX * cos(angle), radiusY * sin(angle), 0);
    }
    glEnd();
}

////////////////////////

///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// PAINTING
void drawBackground(){
    glPushMatrix();
        // glTranslated(0, 2.8, 0.0);
        glColor3f(1, 0.8, 0.95);
        glScaled(16, 16, 1.0); 
        drawSquare();
    glPopMatrix();
}

void drawBaseRetangle(){
    glPushMatrix();
        glScaled(0.5, 1.0, 1.0); 
        glPushMatrix();
            glTranslated(0, -3, 0.0);
            glScaled(10, 2, 1.0); 
            drawSquare();
        glPopMatrix();
    glPopMatrix();
}

void drawOneFish() {
    glColor3f(0.0f, 0.0f, 0.0f);
    // corpo
    glPushMatrix();
        glTranslated(0.3, 0.0, 0.0);
        glPushMatrix();
            glLineWidth(3.0f);
            drawEllipse(0.20, 0.10);
        glPopMatrix();
    glPopMatrix();

    // rabo
    glPushMatrix();
        glRotated(-90, 0.0, 0.0, 1.0);
        glScaled(2, 2, 1.0); 
        drawTriangle();
    glPopMatrix();
}

void drawPenguinChick(){
    glPushMatrix();
        glTranslated(-7.5, -3.9, 0.0);
        glScaled(0.7, 0.7, 1.0); 
        
        // corpo
        glPushMatrix();
        glColor3f(0.8f, 0.8f, 0.2f);
        glTranslated(0.2, 0.42, 0.0);
        drawPolygonEllipse(0.42, 0.41);
        glPopMatrix();

        // pata esquerda
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glRotated(-30, 0.0, 0.0, 1.0);
        glScaled(3, 3, 1.0); 
        drawTriangle();
        glPopMatrix();

        // pata direita
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);    
        glTranslated(0.3, 0.0, 0.0);
        glRotated(-30, 0.0, 0.0, 1.0);
        glScaled(3, 3, 1.0); 
        drawTriangle();
        glPopMatrix();

        // asa
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslated(0.4, 0.42, 0.0);
        drawPolygonEllipse(0.10, 0.25);
        glPopMatrix();

        // bico
        glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        // glTranslated(0.0, -0.6, 0.0);
        glTranslated(0.55, 1.05, 0.0);
        glRotated(-100, 0.0, 0.0, 1.0);
        glScaled(3, 3, 1.0); 
        drawTriangle();
        glPopMatrix();

        // cabeça
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslated(0.25, 1.1, 0.0);
        glScaled(1, 1.2, 1.0); 
        drawPolygonCircle(0.25);
        glPopMatrix();

        // olho
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslated(0.4, 1.15, 0.0);
        glScaled(1, 1.2, 1.0); 
        drawPolygonCircle(0.08);
        glPopMatrix();

    glPopMatrix();
}

void drawPenguinDad(){
    glPushMatrix();
        glTranslated(-1.5, -3.4, 0.0);
        glScaled(0.7, 0.7, 1.0); 

        // pata esquerda
        glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        glTranslated(0.0, -0.6, 0.0);
        glRotated(-10, 0.0, 0.0, 1.0);
        glScaled(3, 6, 1.0); 
        drawTriangle();
        glPopMatrix();

        // pata direita
        glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        glTranslated(0.3, -0.6, 0.0);
        glRotated(-10, 0.0, 0.0, 1.0);
        glScaled(3, 6, 1.0); 
        drawTriangle();
        glPopMatrix();

        // corpo
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.f);
        glTranslated(0.2, 0.42, 0.0);
        drawPolygonEllipse(0.40, 0.90);
        glPopMatrix();

        // asa
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslated(0.4, 0.42, 0.0);
        drawPolygonEllipse(0.1, 0.65);
        glPopMatrix();

        // bico
        glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        // glTranslated(0.0, -0.6, 0.0);
        glTranslated(0.6, 1.55, 0.0);
        glRotated(-100, 0.0, 0.0, 1.0);
        glScaled(3, 6, 1.0); 
        drawTriangle();
        glPopMatrix();

        // cabeça
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslated(0.25, 1.6, 0.0);
        glScaled(1, 1.2, 1.0); 
        drawPolygonCircle(0.35);
        glPopMatrix();

        // olho
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslated(0.4, 1.65, 0.0);
        glScaled(1, 1.2, 1.0); 
        drawPolygonCircle(0.12);
        glPopMatrix();
    glPopMatrix();
}

void drawWater(){
    glPushMatrix();
        glColor3f(0.4f, 0.6f, 1.0f);
        glTranslated(4, 0.0, 0.0);
        glScaled(1.589, 2, 1.0); 
        drawBaseRetangle();
    glPopMatrix();
}

void drawGrass(){
    glPushMatrix();
        glColor3f(0.0, 0.8, 0.0);
        glTranslated(-4, 0.0, 0.0);
        glScaled(1.589, 2, 1.0); 
        drawBaseRetangle();
    glPopMatrix();
}

float getRandomFloat(float min, float max) {
    if (min > max) {
        std::swap(min, max);
    }
    float range = max - min;
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / range);
}


// fish variables
float moveSpeed = 0.005f;
using Coordinate = std::tuple<float, float>;
std::vector<Coordinate> FishCoordinate = { // y max é -4.2 e y min é -7.8
    {1.0f, -7.5f},
    { 2.8f, -7.2f},
    { 4.0f,  -4.5f},
    { 3.0f,  -5.0f}
};
std::tuple<float, float> PositionOne = FishCoordinate[0];
std::tuple<float, float> PositionTwo = FishCoordinate[1];
std::tuple<float, float> PositionThree = FishCoordinate[2];
std::tuple<float, float> PositionFour = FishCoordinate[3];
float xOne = std::get<0>(PositionOne);
float yOne = std::get<1>(PositionOne);
float xTwo = std::get<0>(PositionTwo);
float yTwo = std::get<1>(PositionTwo);
float xThree = std::get<0>(PositionThree);
float yThree = std::get<1>(PositionThree);
float xFour = std::get<0>(PositionFour);
float yFour = std::get<1>(PositionFour);

void drawFish(){
    float leftLimit = 0.0;
    float rightLimit = 8.5;
    float adjusted = 0.2;
    float upLimit = -4.2;
    float downLimit = -7.8;
    
    // to right
    glPushMatrix();
        glPushMatrix();
            xOne = xOne + moveSpeed;            
            if(xOne>(rightLimit)){
                xOne = 0;
                yOne = getRandomFloat(downLimit, upLimit);
            }
            glTranslated(xOne, yOne, 0.0);
            drawOneFish();
        glPopMatrix();

        glPushMatrix();
            xTwo = xTwo + moveSpeed;            
            if(xTwo>(rightLimit)){
                xTwo = 0;
                yTwo = getRandomFloat(downLimit, upLimit);
            }
            glTranslated(xTwo, yTwo, 0.0);
            drawOneFish();
        glPopMatrix();
    glPopMatrix();

    // to left
    glPushMatrix();
        glPushMatrix();
            xThree = xThree - moveSpeed;            
            if(xThree<(leftLimit)){
                xThree = rightLimit-0.1;
                yThree = getRandomFloat(downLimit, upLimit);
            }
            glTranslated(xThree, yThree, 0.0);
            glRotated(-180, 0.0, 0.0, 1.0);
            drawOneFish();
        glPopMatrix();

        glPushMatrix();
            xFour = xFour - moveSpeed;            
            if(xFour<(leftLimit)){
                xFour = rightLimit-0.1;
                yFour = getRandomFloat(downLimit, upLimit);
            }
            glTranslated(xFour, yFour, 0.0);
            glRotated(-180, 0.0, 0.0, 1.0);
            glScaled(0.8, 0.8, 1.0); 
            drawOneFish();
        glPopMatrix();
    glPopMatrix();
}


void drawPicture(){
    drawBackground();
    drawGrass();
    drawWater();
    drawPenguinChick();
    drawPenguinDad();
    drawFish();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    reset_modelview_matrix();
    drawPicture();
    cartesian_plane();
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
void doFrame(int v){
    glutPostRedisplay();
    glutTimerFunc(20, doFrame,0); // 50fps
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(20, doFrame,0); // 50fps
    glutMainLoop();
    return 0;
}