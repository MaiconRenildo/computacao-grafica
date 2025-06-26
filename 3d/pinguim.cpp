#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_BURACOS 5
#define NUM_PEIXES 4

float buracoX[NUM_BURACOS];
float buracoZ[NUM_BURACOS];
float buracoRadius = 1.0f;
int lastToggleTime = 0;
int showBuracos = 1;

GLfloat angle, fAspect;
GLfloat windowWidth = 400;
GLfloat windowHeight = 400;
GLfloat r, g, b;
GLint especMaterial;
float initialPenfuimPaiX = 2.0;
float penguimPaiX = initialPenfuimPaiX;
float penguimPaiZ = 0.0;

float cameraDistance = 5.0f;
float cameraHeight = 2.0f;
float cameraAngle = 0.0f;

// Variáveis para os peixes
float fishPositions[NUM_PEIXES] = { -8.0f, -4.0f, 4.0f, 8.0f };
float fishSpeeds[NUM_PEIXES] = { 0.05f, 0.07f, 0.06f, 0.04f };
int fishDirections[NUM_PEIXES] = { 1, 1, -1, -1 }; // 1 para frente, -1 para trás

// Limites da folha de gelo
const float ICE_SHEET_HALF_SIZE = 10.0f;
const float PENGUIN_RADIUS = 1.0f; // Raio aproximado do pinguim

void PosicionaObservador(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    float radAngle = cameraAngle * M_PI / 180.0f;
    float camX = penguimPaiX - initialPenfuimPaiX - cameraDistance * sin(radAngle);
    float camZ = penguimPaiZ - cameraDistance * cos(radAngle);
    float camY = cameraHeight;
    
    gluLookAt(camX, camY, camZ, 0, 0.0, penguimPaiZ, 0.0, 1.0, 0.0);
}

void updateFishPositions() {
    for (int i = 0; i < NUM_PEIXES; i++) {
        fishPositions[i] += fishSpeeds[i] * fishDirections[i];
        
        // Verifica os limites e inverte a direção se necessário
        if (fishPositions[i] > ICE_SHEET_HALF_SIZE) {
            fishDirections[i] = -1;
        } else if (fishPositions[i] < -ICE_SHEET_HALF_SIZE) {
            fishDirections[i] = 1;
        }
    }
}

void doFrame(int v){
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    if (currentTime - lastToggleTime > 10000) {
        showBuracos = !showBuracos;
        if (showBuracos) {
            float minX = -9.0f, maxX = 9.0f;
            float minZ = -9.0f, maxZ = 9.0f;
            
            for (int i = 0; i < NUM_BURACOS; i++) {
                buracoX[i] = minX + (float)rand() / RAND_MAX * (maxX - minX);
                buracoZ[i] = minZ + (float)rand() / RAND_MAX * (maxZ - minZ);
            }
        }
        lastToggleTime = currentTime;
    }
    
    updateFishPositions();
    glutPostRedisplay();
    glutTimerFunc(12, doFrame, 0);
}

void DefineIluminacao(void){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void drawAxes() {
    glLineWidth(2.0);
    glBegin(GL_LINES);

    // Eixo X
    glColor3f(0.8, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glColor3f(1.0, 0.6, 0.6);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);

    // Eixo Y
    glColor3f(0.0, 0.8, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.6, 1.0, 0.6);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);

    // Eixo Z
    glColor3f(0.0, 0.0, 0.8);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);

    glEnd();

    glPushMatrix();
        glTranslatef(10.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glColor3f(0.8f, 0.0f, 0.0f);
        glutSolidCone(0.3f, 1.0f, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 10.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.8f, 0.0f);
        glutSolidCone(0.3f, 1.0f, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 10.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 0.8f);
        glutSolidCone(0.3f, 1.0f, 20, 20);
    glPopMatrix();

    glLineWidth(1.0);
}

void drawSphere(){
    glPushMatrix();
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

void drawPyramid(float size, float height){
    glBegin(GL_TRIANGLES);
        float s2 = size / 2.0;
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-s2, 0.0, -s2);
        glVertex3f(s2, 0.0, -s2);
        glVertex3f(s2, 0.0, s2);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-s2, 0.0, -s2);
        glVertex3f(s2, 0.0, s2);
        glVertex3f(-s2, 0.0, s2);
    glEnd();

    glBegin(GL_TRIANGLES);
        float topY = height;
        float baseX = size/2;
        float baseZ = size/2;

        glNormal3f(0.0, height, -size);
        glVertex3f(0.0, topY, 0.0);
        glVertex3f(-baseX, 0.0, -baseZ);
        glVertex3f(baseX, 0.0, -baseZ);

        glNormal3f(size, height, 0.0);
        glVertex3f(0.0, topY, 0.0);
        glVertex3f(baseX, 0.0, -baseZ);
        glVertex3f(baseX, 0.0, baseZ);

        glNormal3f(0.0, height, size);
        glVertex3f(0.0, topY, 0.0);
        glVertex3f(baseX, 0.0, baseZ);
        glVertex3f(-baseX, 0.0, baseZ);

        glNormal3f(-size, height, 0.0);
        glVertex3f(0.0, topY, 0.0);
        glVertex3f(-baseX, 0.0, baseZ);
        glVertex3f(-baseX, 0.0, -baseZ);
    glEnd();
}

void drawCone(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    gluDisk(quadric, 0, baseRadius, slices, 1);
    gluDeleteQuadric(quadric);
}

void drawPenguimBody(){
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
        glScalef(1.0, 1.3, 1.0);
        drawSphere();
    glPopMatrix();
}

void drawPenguimStomach(){
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.14);
        glScalef(0.8, 1.2, 0.8);
        drawSphere();
    glPopMatrix();
}

void drawBeak(){
    glColor3f(1.0, 0.6, 0.0);
    glPushMatrix();
        glTranslatef(0.0, 1.5, 0.30);
        glScalef(0.1, 0.15, 0.15);
        drawCone(1.0, 0.0, 1.0, 20, 20);
    glPopMatrix();
}

void drawDadEyes(){
    glPushMatrix();
        glTranslatef(0, 0, -0.45);
        glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
            glTranslatef(-0.25, 1.6, 0.65);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();
        
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
            glTranslatef(-0.23, 1.62, 0.7);
            glScalef(0.045, 0.045, 0.045);
            drawSphere();
        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
            glTranslatef(0.25, 1.6, 0.65);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
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
    glColor3f(0.05, 0.05, 0.05);
    glTranslatef(0, -0.3, 0.0);
    glPushMatrix();
        glPushMatrix();
            glTranslatef(-0.5, 0.5, 0.0);
            glRotatef(-30.0, 0.0, 0.0, 1.0);
            glScalef(0.2, 0.8, 0.5);
            drawSphere();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            glRotatef(30.0, 0.0, 0.0, 1.0);
            glScalef(0.2, 0.8, 0.5);
            drawSphere();
        glPopMatrix();
    glPopMatrix();
}

void drawPenguimFeet(){
    glColor3f(1.0, 0.6, 0.0);
    glPushMatrix();
        glTranslatef(-0.2, -0.3, 0.3);
        glScalef(0.35, 0.1, 0.6);
        drawSphere();
    glPopMatrix();
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
        glTranslatef(penguimPaiX, 0.65, penguimPaiZ);
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

void drawFishAtPosition(float x, float z, int direction) {
    glPushMatrix();
        glTranslatef(x, 0.40, z);
        
        // Rotaciona o peixe para a direção correta
        if (direction < 0) {
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        }

        glColor3f(1.0, 0.4, 0.0);
        glPushMatrix();
            glScalef(1.5, 0.8, 0.8);
            drawSphere();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(-0.5, 0.0, 0.0);
            glScalef(1.0, 0.6, 0.6);
            drawSphere();
        glPopMatrix();

        glColor3f(1.0, 0.3, 0.0);
        glPushMatrix();
            glTranslatef(-1.0, 0.0, 0.0);
            glScalef(0.5, 0.5, 0.1);
            glPushMatrix();
                glTranslatef(0.0, 0.25, 0.0);
                glRotatef(-45.0, 0.0, 0.0, 1.0);
                drawSphere();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -0.25, 0.0);
                glRotatef(45.0, 0.0, 0.0, 1.0);
                drawSphere();
            glPopMatrix();
        glPopMatrix();

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

        glColor3f(1.0, 0.3, 0.0);
        glPushMatrix();
            glTranslatef(0.3, 0.0, 0.45);
            glRotatef(-45.0, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.1, 0.2);
            drawSphere();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.3, 0.0, -0.45);
            glRotatef(45.0, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.1, 0.2);
            drawSphere();
        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
            glTranslatef(0.5, 0.1, 0.3);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5, 0.1, -0.3);
            glScalef(0.1, 0.1, 0.1);
            drawSphere();
        glPopMatrix();

        glColor3f(0.8, 0.2, 0.0);
        glPushMatrix();
            glTranslatef(0.75, 0.0, 0.0);
            glScalef(0.1, 0.1, 0.2);
            drawSphere();
        glPopMatrix();
    glPopMatrix();
}

void drawFishes() {
    for (int i = 0; i < NUM_PEIXES; i++) {
        drawFishAtPosition(2.0f + i * 1.5f, fishPositions[i], fishDirections[i]);
    }
}

void drawBuraco(float x, float y, float z, float radius) {
    int numSegments = 50;
    glColor3f(0.0f, 0.0f, 0.0f);

    glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        GLUquadricObj *quadric = gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);
        gluDisk(quadric, 0, radius, numSegments, 1);
        
        gluCylinder(quadric, radius, radius, 0.1, numSegments, 1);
        gluDeleteQuadric(quadric);
    glPopMatrix();
}

void drawSheetOfIce() {
    // Gelo
    glColor3f(0.7f, 0.9f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0, -0.5, 0.0);
        glScalef(20.0, 1, 20.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // Buracos 
    if (showBuracos) {
        for (int i = 0; i < NUM_BURACOS; i++) {
            drawBuraco(buracoX[i], 0.1f, buracoZ[i], buracoRadius);
        }
    }
}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DefineIluminacao();
    drawAxes();
    drawSheetOfIce();
    drawPenguimDad();
    drawPenguimBaby();
    drawFishes();
    glutSwapBuffers();
}

void EspecificaParametrosVisualizacao(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.5, 190);
    PosicionaObservador();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h){
    windowHeight = h;
    windowWidth = w;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    EspecificaParametrosVisualizacao();
}

void Teclado(unsigned char key, int x, int y) {
    float step = 0.1f;
    float angleStep = 5.0f;

    // Calcula a nova posição temporária
    float newX = penguimPaiX;
    float newZ = penguimPaiZ;

    switch(key) {
        case 'w':
        case 'W':
            newZ += step;
            break;
        case 's':
        case 'S':
            newZ -= step;
            break;
        case 'a':
        case 'A':
            newX += step;
            break;
        case 'd':
        case 'D':
            newX -= step;
            break;
    }

    // Verifica se a nova posição está dentro dos limites da folha de gelo
    if (newX > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) && 
        newX < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS) &&
        newZ > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) && 
        newZ < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS)) {
        
        penguimPaiX = newX;
        penguimPaiZ = newZ;
    }

    glutPostRedisplay();
}

void Inicializa(void) {
    r = 1.0f;
    g = 1.0f;
    b = 1.0f;
    especMaterial = 60;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    
    angle = 50;
    
    cameraDistance = 20.0f;
    cameraHeight = 10.0f;
    cameraAngle = 0.0f;
    
    float minX = -9.0f, maxX = 9.0f;
    float minZ = -9.0f, maxZ = 9.0f;
    
    for (int i = 0; i < NUM_BURACOS; i++) {
        buracoX[i] = minX + (float)rand() / RAND_MAX * (maxX - minX);
        buracoZ[i] = minZ + (float)rand() / RAND_MAX * (maxZ - minZ);
    }
    
    lastToggleTime = glutGet(GLUT_ELAPSED_TIME);
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Pinguim com gluLookAt");

    srand((unsigned int)time(NULL));
    Inicializa();
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);

    doFrame(0);
    glutMainLoop();
    return 0;
}
