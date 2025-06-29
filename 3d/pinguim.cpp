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

#define NUM_BURACOS 5
#define NUM_PEIXES 4
#define GAME_WIN_TIME_MS 300000 // 5 minutos
#define BABY_HUNGER_TIME_MS 60000 // 1 minuto

// Variáveis para os buracos
float holeX[NUM_BURACOS];
float holeZ[NUM_BURACOS];
float holeRadius = 1.0;
int lastToggleTime = 0;
int showHoles = 0;

// Variáveis de câmera e iluminação
GLfloat angle, fAspect;
GLfloat windowWidth = 400;
GLfloat windowHeight = 400;
GLfloat r, g, b;
GLint especMaterial;
int activeViewport = 3; // 0: X, 1: Y, 2: Z, 3: Perspectiva (padrão)
bool showAllViewports = true; // Alternar entre todas as viewports ou apenas a principal

// posições dos pinguins
float initialMotherPenguinX = 2.0;
float babyPenguinX = 0.0;
float babyPenguinZ = 0.0;
float motherPenguinZ = 0.0;
float motherPenguinX = initialMotherPenguinX;

float cameraAngle = 0.0;
float cameraHeight = 2.0;
float cameraDistance = 5.0;

int canCollectFish = 1;
int hasFishInMouth = 0;

// variaveis pras asas
int lastKeyPressedTime = 0;
float wingSwingAngle = 0.0f;
float wingSwingSpeed = 0.5f;
int wingSwingDirection = 1;
int isPenguinMoving = 0;
int movementIdleCounter = 0;
const int IDLE_THRESHOLD = 1;
const int IDLE_TIMEOUT_MS = 100;

// Variáveis para os peixes
float fishXPositions[NUM_PEIXES] = {-6.0f, -3.5f, 4.0f, 7.0};
float fishZPositions[NUM_PEIXES] = {-8.0f, -4.0f, 4.0f, 8.0};
float fishSpeedList[NUM_PEIXES] = {0.05f, 0.07f, 0.06f, 0.04};
int fishVisibleList[NUM_PEIXES] = {1, 1, 1, 1};
int fishDirectionsList[NUM_PEIXES] = {-1, 1, 1, -1}; // 1 para frente, -1 para trás

// Limites da folha de gelo
const float ICE_SHEET_HALF_SIZE = 10.0;
const float PENGUIN_RADIUS = 1.0; // Raio aproximado do pinguim
const float FISH_RADIUS = 0.8; // Raio aproximado do peixe

// Variáveis do jogo tempo e pontuação
int startTime = 0; 
int collected = 0;
int lastFedTime = 0;
// Define as direções para onde o pinguim pode estar "olhando"
typedef enum {
    FACING_FORWARD,
    FACING_BACKWARD,
    FACING_LEFT,
    FACING_RIGHT
} PenguinDirection;

// Variável global para armazenar a direção atual do pinguim
PenguinDirection direcaoAtualPinguim = FACING_FORWARD; // Começa olhando para frente
float penguimRotationAngle = 0.0; 

// --- DECLARAÇÕES DAS FUNÇÕES ---
void drawSceneContent(void); // Adicione esta linha
void endGame(int isVictory, const char* message);
void configureObserver(void);
void checkCollisions(void);
void checkHoleCollisions(void);
void checkPenguinCollision(void);
void updateFishPositions(void);
void doFrame(int v);
void defineLighting(void);
void drawAxes(void);
void drawSphere(void);
void drawPyramid(float size, float height);
void drawCone(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);
void drawPenguimBody(void);
void drawPenguimStomach(void);
void drawBeak(void);
void drawMotherEyes(void);
void drawPenguimHead(void);
void drawPenguimWings(void);
void drawPenguimFeet(void);
void drawPenguim(void);
void drawPenguimBaby(void);
void drawFishAtPosition(float x, float z, int direction);
void drawPenguimMother(void);
void drawFishes(void);
void drawHole(float x, float y, float z, float radius);
void drawSheetOfIce(void);
void draw(void);
void specifyViewParameters(void);
void resizeWindow(GLsizei w, GLsizei h);
void keyboard(int key, int x, int y);
void keyboardpoint(unsigned char key, int x, int y);
void initialize(void);
// --- FIM DAS DECLARAÇÕES ---



void configureObserver(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    float radAngle = cameraAngle * M_PI / 180.0;
    float camX = motherPenguinX - initialMotherPenguinX - cameraDistance * sin(radAngle);
    float camZ = motherPenguinZ - cameraDistance * cos(radAngle);
    float camY = cameraHeight;
    
    gluLookAt(camX, camY, camZ, 
        babyPenguinX, 0.0, motherPenguinZ,
         0.0, 1.0, 0.0);
}

// Colisão entre mãe e peixes
void checkCollisions(){
    if (canCollectFish) {
        for (int i = 0; i < NUM_PEIXES; i++) {
            if (fishVisibleList[i]) {
                float dx = motherPenguinX - fishXPositions[i];
                float dz = motherPenguinZ - fishZPositions[i];
                float distance = sqrt(dx * dx + dz * dz);
                
                if (distance < (PENGUIN_RADIUS + FISH_RADIUS)) {
                    fishVisibleList[i] = 0;
                    canCollectFish = 0;
                    collected += 1;
                    hasFishInMouth = 1;
                    lastFedTime = glutGet(GLUT_ELAPSED_TIME);
                    break; // Sai do loop após coletar um peixe
                }
            }
        }
    }
}

void endGame(int isVictory, const char* message) {
    printf("=====================\n");
    if(isVictory){
        printf("Você GANHOU!!!\n");
    } else {
        printf("GAME OVER!\n");
        if(message != NULL){
            printf("%s\n", message);
        }
    }
    printf("PEIXES COLETADOS: %d \n", collected);
    printf("=====================\n");
    exit(0);
}

// Colisão mãe e buraco
void checkHoleCollisions() {
    const float COLLISION_SENSITIVITY = 0.8; 
    const float EFFECTIVE_PENGUIN_RADIUS = PENGUIN_RADIUS * COLLISION_SENSITIVITY;
    const float EFFECTIVE_HOLE_RADIUS = holeRadius * COLLISION_SENSITIVITY;
    
    for (int i = 0; i < NUM_BURACOS; i++) {
        if (showHoles) {
            float dx = motherPenguinX - holeX[i];
            float dz = motherPenguinZ - holeZ[i];
            float distance = sqrt(dx * dx + dz * dz);
            distance = distance + (distance/2); // melhora percepção de sobreposição
            
            if (distance < (EFFECTIVE_PENGUIN_RADIUS + EFFECTIVE_HOLE_RADIUS)) {
                endGame(false, "Mãe caiu no buraco");
            }
        }
    }
}

// Colisão mãe e filho
void checkPenguinCollision(){
    const float SENSIBILITY_X = 0.4;  
    const float SENSIBILITY_Z = 0.3;  
    
    float dx = (motherPenguinX - babyPenguinX) / SENSIBILITY_X;
    float dz = (motherPenguinZ - babyPenguinZ) / SENSIBILITY_Z;
    
    const float MOTHER_EFFECTIVE_RADIUS = 0.4;
    const float BABY_EFFECTIVE_RADIUS = 0.3;
    const float COLLISION_TOLERANCE = 0.5;
    
    float distance = sqrt(dx * dx + dz * dz);
    
    float sumOfRadii = MOTHER_EFFECTIVE_RADIUS + BABY_EFFECTIVE_RADIUS;
    float adjustedSumOfRadii = sumOfRadii + COLLISION_TOLERANCE;
    
    if (distance < adjustedSumOfRadii) {
        canCollectFish = 1;
        hasFishInMouth = 0;
        
        // Reaparece apenas um peixe por colisão
        for (int i = 0; i < NUM_PEIXES; i++) {
            if (!fishVisibleList[i]) {
                fishVisibleList[i] = 1;
                // Posiciona o peixe 
                do {
                    fishXPositions[i] = -ICE_SHEET_HALF_SIZE + (float)rand() / RAND_MAX * (2 * ICE_SHEET_HALF_SIZE);
                    fishZPositions[i] = -ICE_SHEET_HALF_SIZE + (float)rand() / RAND_MAX * (2 * ICE_SHEET_HALF_SIZE);
                } while (sqrt(pow(fishXPositions[i]-motherPenguinX,2) + pow(fishZPositions[i]-motherPenguinZ,2)) < 3.0f ||
                         sqrt(pow(fishXPositions[i]-babyPenguinX,2) + pow(fishZPositions[i]-babyPenguinZ,2)) < 3.0f);
                
                fishDirectionsList[i] = (rand() % 2) ? 1 : -1;
                break;
            }
        }
    }
}

// Animação dos peixes
void updateFishPositions() {
    for (int i = 0; i < NUM_PEIXES; i++) {
        if (fishVisibleList[i]) {
            fishZPositions[i] += fishSpeedList[i] * fishDirectionsList[i];
            
            if (fishZPositions[i] > ICE_SHEET_HALF_SIZE) {
                fishDirectionsList[i] = -1;
            } else if (fishZPositions[i] < -ICE_SHEET_HALF_SIZE) {
                fishDirectionsList[i] = 1;
            }
        }
    }
    
    checkCollisions();
    checkPenguinCollision();
}

void doFrame(int v){
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - startTime;
    int timeSinceLastFed = currentTime - lastFedTime;
    
    if (elapsedTime >= GAME_WIN_TIME_MS) {
        endGame(true, "");
    }

    if (timeSinceLastFed >= BABY_HUNGER_TIME_MS) {
        endGame(false, "O pinguim filhote ficou com fome por muito tempo.");
    }
    
    if (currentTime - lastToggleTime > 10000) {
        showHoles = !showHoles;
        if (showHoles) {
            float minX = -9.0f, maxX = 9.0;
            float minZ = -9.0f, maxZ = 9.0;
            
            for (int i = 0; i < NUM_BURACOS; i++) {
                holeX[i] = minX + (float)rand() / RAND_MAX * (maxX - minX);
                holeZ[i] = minZ + (float)rand() / RAND_MAX * (maxZ - minZ);
            }
        }
        lastToggleTime = currentTime;
    }

    // animação das asas
    if ((currentTime - lastKeyPressedTime) < IDLE_TIMEOUT_MS) {
        wingSwingAngle += wingSwingDirection * wingSwingSpeed;
        if (wingSwingAngle > 15.0f){
            wingSwingAngle = 15.0f;
            wingSwingDirection = -1;
        } else if (wingSwingAngle < -15.0f){
            wingSwingAngle = -15.0f;
            wingSwingDirection = 1;
        }
        movementIdleCounter = IDLE_THRESHOLD;
    } else {
        if (movementIdleCounter > 0) {
            movementIdleCounter--;
        } else {
            if (fabs(wingSwingAngle) > 0.5f) {
                wingSwingAngle *= 0.85;
            } else {
                wingSwingAngle = 0.0f;
            }
        }
    }

    updateFishPositions();
    checkHoleCollisions();  
    glutPostRedisplay();
    glutTimerFunc(12, doFrame, 0);
}

void defineLighting(void){
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
void drawMotherEyes(){
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
        drawMotherEyes();
    glPopMatrix();
}

// Desenha asas dos pinguins
void drawPenguimWings(bool isMother=false){
    if(isMother){
        glColor3f(0.7f, 0.7f, 0.7f);
    }else{
        glColor3f(0.05, 0.05, 0.05);
    }
    glTranslatef(0, -0.3, 0.0);
    glPushMatrix();
        // esquerda
        glPushMatrix();
            glTranslatef(-0.5, 0.5, 0.0);
            if(isMother){
                glRotatef(-30.0 + wingSwingAngle, 0.0, 0.0, 1.0);
            }else{
                glRotatef(-30.0, 0.0, 0.0, 1.0);
            }
            glScalef(0.2, 0.8, 0.5);
            drawSphere();
        glPopMatrix();
        // direita
        glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            if(isMother){
                glRotatef(30.0 - wingSwingAngle, 0.0, 0.0, 1.0);
            }else{
                glRotatef(30.0, 0.0, 0.0, 1.0);
            }
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
void drawPenguim(bool isMother=false){
    glPushMatrix();
        drawPenguimHead();
        drawPenguimBody();
        drawPenguimStomach();
        drawPenguimWings(isMother);
        drawPenguimFeet();
    glPopMatrix();
}


// Posiciona pinguim filho
void drawPenguimBaby(){
    glPushMatrix();
        glTranslatef(babyPenguinX, 0.41, babyPenguinZ);
        glRotatef(180, 0.0f, 1.0f, 0.0f); 
        glScalef(0.8, 0.6, 0.8);
        drawPenguim(false);
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


// Posiciona pinguim mãe
void drawPenguimMother(){
    glPushMatrix();
        glTranslatef(motherPenguinX, 0.65, motherPenguinZ);
        glRotatef(penguimRotationAngle, 0.0f, 1.0f, 0.0f); // Rotação no eixo Y
        drawPenguim(true);
        if (hasFishInMouth) {
            glPushMatrix();
                glTranslatef(0.0f, 0.5f, 0.7f);
                glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
                glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

                glScalef(0.40f, 0.40f, 0.40f);
                drawFishAtPosition(0.0f, 0.0f, 1);
            glPopMatrix();
        }
    glPopMatrix();
}

void drawFishes() {
    for (int i = 0; i < NUM_PEIXES; i++) {
        if (fishVisibleList[i]) {
            drawFishAtPosition(fishXPositions[i], fishZPositions[i], fishDirectionsList[i]);
        }
    }
}

void drawHole(float x, float y, float z, float radius) {
    int numSegments = 50;
    glColor3f(0.5f, 0.7f, 0.9f);

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
    if (showHoles) {
        for (int i = 0; i < NUM_BURACOS; i++) {
            drawHole(holeX[i], 0.1f, holeZ[i],    holeRadius);
        }
    }
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (showAllViewports) {
        // --- Viewport 1: Câmera no Eixo X (visão lateral) ---
        glViewport(0, windowHeight/2, windowWidth/2, windowHeight/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(15.0, 2.0, 0.0,  // Posição da câmera (X fixo)
                 motherPenguinX, 0.0, motherPenguinZ,  // Olha para o pinguim
                 0.0, 1.0, 0.0); // Vetor "up"
        defineLighting();
        drawSceneContent(); // Função que desenha tudo (gelo, pinguins, etc.)

        // --- Viewport 2: Câmera no Eixo Y (visão de cima) ---
        glViewport(windowWidth/2, windowHeight/2, windowWidth/2, windowHeight/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 15.0, 0.0,  // Posição da câmera (Y fixo)
                 motherPenguinX, 0.0, motherPenguinZ,  // Olha para o pinguim
                 0.0, 0.0, -1.0); // Vetor "up" ajustado
        defineLighting();
        drawSceneContent();

        // --- Viewport 3: Câmera no Eixo Z (visão frontal) ---
        glViewport(0, 0, windowWidth/2, windowHeight/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 2.0, 15.0,  // Posição da câmera (Z fixo)
                 motherPenguinX, 0.0, motherPenguinZ,  // Olha para o pinguim
                 0.0, 1.0, 0.0); // Vetor "up"
        defineLighting();
        drawSceneContent();

        // --- Viewport 4: Câmera Perspectiva (original) ---
        glViewport(windowWidth/2, 0, windowWidth/2, windowHeight/2);
        specifyViewParameters(); // Usa a câmera original
        defineLighting();
        drawSceneContent();
    } else {
        // Modo: apenas uma viewport ativa (controlada por 'activeViewport')
        glViewport(0, 0, windowWidth, windowHeight);
        switch (activeViewport) {
            case 0: // Eixo X
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(15.0, 2.0, 0.0, motherPenguinX, 0.0, motherPenguinZ, 0.0, 1.0, 0.0);
                break;
            case 1: // Eixo Y
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(0.0, 15.0, 0.0, motherPenguinX, 0.0, motherPenguinZ, 0.0, 0.0, -1.0);
                break;
            case 2: // Eixo Z
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(50, (GLfloat)windowWidth/windowHeight, 0.5, 190);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(0.0, 2.0, 15.0, motherPenguinX, 0.0, motherPenguinZ, 0.0, 1.0, 0.0);
                break;
            case 3: // Perspectiva original
                specifyViewParameters();
                break;
        }
        defineLighting();
        drawSceneContent();
    }

    glutSwapBuffers();
}

// Função auxiliar para desenhar o conteúdo da cena (evita repetição de código)
void drawSceneContent() {
    glClear(GL_DEPTH_BUFFER_BIT); // Limpa apenas o depth buffer para cada viewport
    drawAxes();
    drawSheetOfIce();
    drawPenguimMother();
    drawPenguimBaby();
    drawFishes();
}

void specifyViewParameters(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.5, 190);
    configureObserver();
}

void resizeWindow(GLsizei w, GLsizei h){
    windowHeight = h;
    windowWidth = w;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    specifyViewParameters();
}

void keyboard(int key, int x, int y) {
    float step = 0.3;

    float newX = motherPenguinX;
    float newZ = motherPenguinZ;

    // Flag para saber se houve um movimento válido ou mudança de direção
    bool movedOrChangedDirection = false;

    switch(key) {
        case GLUT_KEY_UP: // Seta para Cima
            if (direcaoAtualPinguim == FACING_FORWARD) {
                newZ += step;
                movedOrChangedDirection = true;
            } else {
                direcaoAtualPinguim = FACING_FORWARD;
                penguimRotationAngle = 0.0;
            }
            break;
        case GLUT_KEY_DOWN: // Seta para Baixo
            if (direcaoAtualPinguim == FACING_BACKWARD) {
                newZ -= step;
                movedOrChangedDirection = true;
            } else {
                direcaoAtualPinguim = FACING_BACKWARD;
                penguimRotationAngle = 180.0;
            }
            break;
        case GLUT_KEY_LEFT: // Seta para Esquerda
            if (direcaoAtualPinguim == FACING_LEFT) {
                newX += step;
                movedOrChangedDirection = true;
            } else {
                direcaoAtualPinguim = FACING_LEFT;
                penguimRotationAngle = 90.0;
            }
            break;
        case GLUT_KEY_RIGHT: // Seta para Direita
            if (direcaoAtualPinguim == FACING_RIGHT) {
                newX -= step;
                movedOrChangedDirection = true;
            } else {
                direcaoAtualPinguim = FACING_RIGHT;
                penguimRotationAngle = -90.0;
            }
            break;
    }

    // Não deixa mãe andar fora do gelo
    if (newX > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newX < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS) &&
        newZ > (-ICE_SHEET_HALF_SIZE + PENGUIN_RADIUS) &&
        newZ < (ICE_SHEET_HALF_SIZE - PENGUIN_RADIUS)) {

        if (newX != motherPenguinX || newZ != motherPenguinZ) {
            motherPenguinX = newX;
            motherPenguinZ = newZ;
            movedOrChangedDirection = true;
        }
        // Verifica colisão com buracos após o movimento
        checkHoleCollisions();
    }

    if (movedOrChangedDirection) {
        lastKeyPressedTime = glutGet(GLUT_ELAPSED_TIME);
    }
    
    glutPostRedisplay();
}
void keyboardpoint(unsigned char key, int x, int y) {
    switch (key) {
        case 'v': // Alterna entre todas as viewports e a única ativa
            showAllViewports = !showAllViewports;
            break;
        case '1': // Muda para viewport do eixo X
            activeViewport = 0;
            showAllViewports = false;
            break;
        case '2': // Muda para viewport do eixo Y
            activeViewport = 1;
            showAllViewports = false;
            break;
        case '3': // Muda para viewport do eixo Z
            activeViewport = 2;
            showAllViewports = false;
            break;
        case '4': // Muda para viewport perspectiva
            activeViewport = 3;
            showAllViewports = false;
            break;
    }
    glutPostRedisplay();
}

void initialize(void) {
    r = 1.0;
    g = 1.0;
    b = 1.0;
    especMaterial = 60;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    
    angle = 50;
    
    cameraDistance = 20.0;
    cameraHeight = 10.0;
    cameraAngle = 0.0;
    
    float minX = -9.0f, maxX = 9.0;
    float minZ = -9.0f, maxZ = 9.0;
    
    for (int i = 0; i < NUM_BURACOS; i++) {
        holeX[i] = minX + (float)rand() / RAND_MAX * (maxX - minX);
        holeZ[i] = minZ + (float)rand() / RAND_MAX * (maxZ - minZ);
    }
    
    lastToggleTime = glutGet(GLUT_ELAPSED_TIME);
    startTime = glutGet(GLUT_ELAPSED_TIME); // Define o tempo de início do jogo
    lastFedTime = glutGet(GLUT_ELAPSED_TIME);
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Pinguim 3D");

    srand((unsigned int)time(NULL));
    initialize();
    glutDisplayFunc(draw);
    glutReshapeFunc(resizeWindow);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyboardpoint);

    doFrame(0);
    glutMainLoop();
    return 0;
}