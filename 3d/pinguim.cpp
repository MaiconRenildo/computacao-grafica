#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstdio>

// Algumas constantes
#define NUM_BURACOS 5
#define NUM_PEIXES 4

// Variáveis para os buracos
float buracoX[NUM_BURACOS];
float buracoZ[NUM_BURACOS];
float buracoRadius = 1.0f;
int lastToggleTime = 0;
int showBuracos = 1;

// Variáveis câmera e iluminação
GLfloat angle, fAspect;
GLfloat windowWidth = 400;
GLfloat windowHeight = 400;
GLfloat r, g, b;
GLint especMaterial;
float initialPenguimMaeX = 2.0;
float penguimMaeX = initialPenguimMaeX;
float penguimMaeZ = 0.0;

float cameraDistance = 5.0f;
float cameraHeight = 2.0f;
float cameraAngle = 0.0f;

// Variáveis para os peixes
float fishPositionsX[NUM_PEIXES] = { -6.0f, -3.5f, 4.0f, 7.0f };
float fishPositionsZ[NUM_PEIXES] = { -8.0f, -4.0f, 4.0f, 8.0f };
float fishSpeeds[NUM_PEIXES] = { 0.05f, 0.07f, 0.06f, 0.04f };
int fishDirections[NUM_PEIXES] = { -1, 1, 1, -1 }; // 1 para frente, -1 para trás
int fishVisible[NUM_PEIXES] = { 1, 1, 1, 1 }; // 1 para visível, 0 para invisível

// Variável global para controlar se pode coletar peixes
int podeColetarPeixe = 1; // 1 = pode coletar, 0 = não pode

// Posição do pinguim filho
float penguimFilhoX = 0.0f;
float penguimFilhoZ = 0.0f;

// Limites da folha de gelo
const float ICE_SHEET_HALF_SIZE = 10.0f;
const float PENGUIN_RADIUS = 1.0f; // Raio aproximado do pinguim
const float FISH_RADIUS = 0.8f; // Raio aproximado do peixe

// Variáveis do jogo tempo e pontuação
int startTime = 0; 
int coletados = 0;
// Define as direções para onde o pinguim pode estar "olhando"
typedef enum {
    OLHANDO_FRENTE,
    OLHANDO_TRAS,
    OLHANDO_ESQUERDA,
    OLHANDO_DIREITA
} DirecaoPinguim;

// Variável global para armazenar a direção atual do pinguim
DirecaoPinguim direcaoAtualPinguim = OLHANDO_FRENTE; // Começa olhando para frente
float penguimRotationAngle = 0.0f; 

void PosicionaObservador(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    float radAngle = cameraAngle * M_PI / 180.0f;
    float camX = penguimMaeX - initialPenguimMaeX - cameraDistance * sin(radAngle);
    float camZ = penguimMaeZ - cameraDistance * cos(radAngle);
    float camY = cameraHeight;
    
    gluLookAt(camX, camY, camZ, 
        penguimFilhoX, 0.0, penguimMaeZ,
         0.0, 1.0, 0.0);
}

// Colisão entre mãe e peixes
void checkCollisions() {
    // Se estiver apto a coletar
    if (podeColetarPeixe) {
        for (int i = 0; i < NUM_PEIXES; i++) {
            if (fishVisible[i]) {
                float dx = penguimMaeX - fishPositionsX[i];
                float dz = penguimMaeZ - fishPositionsZ[i];
                float distance = sqrt(dx * dx + dz * dz);
                
                if (distance < (PENGUIN_RADIUS + FISH_RADIUS)) {
                    fishVisible[i] = 0; // Faz o peixe desaparecer
                    podeColetarPeixe = 0; // Impede de coletar outros peixes
                    coletados += 1;
                    break; // Sai do loop após coletar um peixe
                }
            }
        }
    }
}

// Colisão mãe e buraco
void checkHoleCollisions() {
    const float COLLISION_SENSITIVITY = 0.8f; 
    const float EFFECTIVE_PENGUIN_RADIUS = PENGUIN_RADIUS * COLLISION_SENSITIVITY;
    const float EFFECTIVE_HOLE_RADIUS = buracoRadius * COLLISION_SENSITIVITY;
    
    for (int i = 0; i < NUM_BURACOS; i++) {
        if (showBuracos) {
            float dx = penguimMaeX - buracoX[i];
            float dz = penguimMaeZ - buracoZ[i];
            float distance = sqrt(dx * dx + dz * dz);
            
            if (distance < (EFFECTIVE_PENGUIN_RADIUS + EFFECTIVE_HOLE_RADIUS)) {
                printf("Você perdeu! Mãe caiu no buraco\n");
                exit(0);
            }
        }
    }
}

// Colisão mãe e filho
void checkPenguinCollision() {
    
    const float SENSIBILIDADE_X = 0.4f;  
    const float SENSIBILIDADE_Z = 0.3f;  
    
    float dx = (penguimMaeX - penguimFilhoX) / SENSIBILIDADE_X;
    float dz = (penguimMaeZ - penguimFilhoZ) / SENSIBILIDADE_Z;
    
    const float RAIO_EFETIVO_MAE = 0.4f;
    const float RAIO_EFETIVO_FILHO = 0.3f;
    
    float distancia = sqrt(dx * dx + dz * dz);
    float somaRaios = RAIO_EFETIVO_MAE + RAIO_EFETIVO_FILHO;
    
    if (distancia < somaRaios) {
        podeColetarPeixe = 1;
        
        // Reaparece apenas um peixe por colisão
        for (int i = 0; i < NUM_PEIXES; i++) {
            if (!fishVisible[i]) {
                fishVisible[i] = 1;
                // Posiciona o peixe 
                do {
                    fishPositionsX[i] = -ICE_SHEET_HALF_SIZE + (float)rand() / RAND_MAX * (2 * ICE_SHEET_HALF_SIZE);
                    fishPositionsZ[i] = -ICE_SHEET_HALF_SIZE + (float)rand() / RAND_MAX * (2 * ICE_SHEET_HALF_SIZE);
                } while (sqrt(pow(fishPositionsX[i]-penguimMaeX,2) + pow(fishPositionsZ[i]-penguimMaeZ,2)) < 3.0f ||
                         sqrt(pow(fishPositionsX[i]-penguimFilhoX,2) + pow(fishPositionsZ[i]-penguimFilhoZ,2)) < 3.0f);
                
                fishDirections[i] = (rand() % 2) ? 1 : -1;
                break;
            }
        }
    }
}

// Animação dos peixes
void updateFishPositions() {
    for (int i = 0; i < NUM_PEIXES; i++) {
        if (fishVisible[i]) {
            fishPositionsZ[i] += fishSpeeds[i] * fishDirections[i];
            
            if (fishPositionsZ[i] > ICE_SHEET_HALF_SIZE) {
                fishDirections[i] = -1;
            } else if (fishPositionsZ[i] < -ICE_SHEET_HALF_SIZE) {
                fishDirections[i] = 1;
            }
        }
    }
    
    checkCollisions();
    checkPenguinCollision();
}

void doFrame(int v){
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - startTime;
    
    // Verifica se passaram 3 minutos (180.000 ms)
    if (elapsedTime >= 180000) {
        printf("=====================");
        printf("Você ganhou!!!\n");
        printf("%d PEIXES COLETADOS  \n",coletados);
        printf("=====================");
        exit(0);
    }
    
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
    checkHoleCollisions();  
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

// Desenha esfera
void drawSphere(){
    glPushMatrix();
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}


// Desenha pirâmide
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

// Desenha cone
void drawCone(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    gluDisk(quadric, 0, baseRadius, slices, 1);
    gluDeleteQuadric(quadric);
}

// Desenha corpo dos pinguins
void drawPenguimBody(){
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
        glScalef(1.0, 1.3, 1.0);
        drawSphere();
    glPopMatrix();
}

// Desenha estômago (branco)
void drawPenguimStomach(){
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.14);
        glScalef(0.8, 1.2, 0.8);
        drawSphere();
    glPopMatrix();
}

// Desenha bico
void drawBeak(){
    glColor3f(1.0, 0.6, 0.0);
    glPushMatrix();
        glTranslatef(0.0, 1.5, 0.30);
        glScalef(0.1, 0.15, 0.15);
        drawCone(1.0, 0.0, 1.0, 20, 20);
    glPopMatrix();
}

// Desenha olhos
void drawMaeEyes(){
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

// Desenha cabeça dos pinguins
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
        drawMaeEyes();
    glPopMatrix();
}

// Desenha asas dos pinguins
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

// Desenha pés dos pinguins
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

// Desenha pinguim 
void drawPenguim(){
    glPushMatrix();
        drawPenguimHead();
        drawPenguimBody();
        drawPenguimStomach();
        drawPenguimWings();
        drawPenguimFeet();
    glPopMatrix();
}

// Posiciona pinguim mãe
void drawPenguimMae(){
    glPushMatrix();
        glTranslatef(penguimMaeX, 0.65, penguimMaeZ);
        glRotatef(penguimRotationAngle, 0.0f, 1.0f, 0.0f); // Rotação no eixo Y
        drawPenguim();
    glPopMatrix();
}

// Posiciona pinguim filho
void drawPenguimBaby(){
    glPushMatrix();
        glTranslatef(penguimFilhoX, 0.41, penguimFilhoZ);
        glRotatef(180, 0.0f, 1.0f, 0.0f); 
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
        if (fishVisible[i]) {
            drawFishAtPosition(fishPositionsX[i], fishPositionsZ[i], fishDirections[i]);
        }
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
    drawPenguimMae();   
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
    float step = 0.3f;
    float angleStep = 5.0f;

    // Calcula a nova posição temporária
    float newX = penguimMaeX;
    float newZ = penguimMaeZ;

    switch(key) {
        case 'w':
        case 'W':
            if (direcaoAtualPinguim == OLHANDO_FRENTE) {
                newZ += step; // Anda para frente
            } else {
                direcaoAtualPinguim = OLHANDO_FRENTE; // Muda a direção para frente
                penguimRotationAngle = 0.0f; // Reseta a rotação
            }
            break;
        case 's':
        case 'S':
            if (direcaoAtualPinguim == OLHANDO_TRAS) {
                newZ -= step; // Anda para trás
            } else {
                direcaoAtualPinguim = OLHANDO_TRAS; // Muda a direção para trás
                penguimRotationAngle = 180.0f; // Rotaciona 180 graus
            }
            break;
        case 'a':
        case 'A':
            if (direcaoAtualPinguim == OLHANDO_ESQUERDA) {
                newX += step; // Anda para a "esquerda" (no seu sistema de coordenadas X positivo é esquerdo)
            } else {
                direcaoAtualPinguim = OLHANDO_ESQUERDA; // Muda a direção para esquerda
                penguimRotationAngle = 90.0f; // Rotaciona 90 graus
            }
            break;
        case 'd':
        case 'D':
            if (direcaoAtualPinguim == OLHANDO_DIREITA) {
                newX -= step; // Anda para a "direita" (no seu sistema de coordenadas X negativo é direito)
            } else {
                direcaoAtualPinguim = OLHANDO_DIREITA; // Muda a direção para direita
                penguimRotationAngle = -90.0f; // Rotaciona -90 graus
            }
            break;
    }

    // Não deixa mãe andar fora do gelo
    if (newX > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newX < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS) &&
        newZ > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newZ < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS)) {
        
        penguimMaeX = newX;
        penguimMaeZ = newZ;

        // Verifica colisão com buracos após o movimento
        checkHoleCollisions();
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
    startTime = glutGet(GLUT_ELAPSED_TIME); // Define o tempo de início do jogo
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Pinguim 3D");

    srand((unsigned int)time(NULL));
    Inicializa();
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);

    doFrame(0);
    glutMainLoop();
    return 0;
}
