#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>  // para rand() e srand()
#include <ctime>    // para time()
#include <vector>
#include <tuple>
#include <chrono>

// declare generic code
void reset_modelview_matrix();
void reset_projection_matrix();
void init();

// declare constants
const char* title = "Penguim Game";
const int windowWidth = 800;
const int windowHeight = 600;
const float orthoValue = 8.0;
const double PI = 3.14;
const float moveStep = 0.5;
const float windowLeftLimit = -7.5;
const float windowRightLimit = 6.5;

// declare global variables
float dadXPosition = -1.5;
float dadYStandingPosition = -3.4;
float dadYSwimmingPosition = -4;
float dadYPosition = dadYStandingPosition;
bool moveDadToLeft = false;
bool isDadGoingToLeft = false;
bool moveDadDown = false;
bool moveDadUp = false;
bool colisaoDetectada = false;
bool hasFish = false;
int direcao = 0;
int framesDesdeUltimaColisao = 0;
int score = 0;


// Variáveis para controle de tempo
std::chrono::steady_clock::time_point startTime;
bool gameFinished = false;
const int GAME_DURATION = 300; // 5 minutos em segundos

// Estrutura para representar uma bounding box
struct BoundingBox {
    float x, y;       
    float largura, altura;
};

// Estrutura para representar um peixe
struct Fish {
    float x;
    float y;
    float speed;
    bool movingRight;
    float scale;
    bool isVisible;
};

float getRandomFloat(float min, float max) {
    if (min > max) {
        std::swap(min, max);
    }
    float range = max - min;
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / range);
}

std::vector<Fish> initializeFishes() {
    std::vector<Fish> fishes = {
        {1.0f, -7.5f, 0.005f, true, 1.0f},
        {2.8f, -7.2f, 0.005f, true, 1.0f},
        {4.0f, -4.5f, 0.005f, false, 1.0f},
        {3.0f, -5.0f, 0.005f, false, 1.0f}
    };
    return fishes;
}

std::vector<Fish> allFishes = initializeFishes();

// Função para obter a bounding box do pinguim filho
BoundingBox getPenguinSonBoundingBox() {
    BoundingBox box;
    box.x = -7.5 + 0.2;  
    box.y = -3.9 + 0.42; 
    box.largura = 0.42 * 2 * 0.7; 
    box.altura = 0.41 * 2 * 0.7;  
    return box;
}

// Função para obter a bounding box do pinguim pai
BoundingBox getPenguinDadBoundingBox() {
    BoundingBox box;

    box.x = dadXPosition + 0.2f;  
    box.y = dadYPosition + 0.42f; 
    box.largura = 0.42f * 2 * 0.7f; 
    box.altura = 0.41f * 2 * 0.7f;  
    return box;
}

// Função para obter a bounding box do pássaro
BoundingBox getBirdBoundingBox(float birdX, float birdY) {
    BoundingBox box;
    // O pássaro é composto por duas asas, vamos considerar uma box que as contém
    box.x = birdX - 1.0; 
    box.y = birdY + 1.0;  
    box.largura = 2.5;    
    box.altura = 0.5;     
    return box;
}


// Função para verificar colisão entre duas bounding boxes
bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return fabs(a.x - b.x) < (a.largura/2 + b.largura/2) &&
           fabs(a.y - b.y) < (a.altura/2 + b.altura/2);
}

float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

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
void drawSquare(){ 
    float squareWidth = 1.0;
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


void drawWing(){
    float RAIO = 2.0 ; 

    glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_LINE_STRIP);  
        for (int i = 0; i <= 180; i++) {  // De 0 a 180 graus para a metade
            float angulo = i * PI / 180.0;  // Converte o ângulo para radianos
            float x = RAIO * cos(angulo);   // Coordenada x do ponto no arco
            float y = RAIO * sin(angulo);   // Coordenada y do ponto no arco
            glVertex3f(x, y, 1.0);               // Adiciona o ponto no arco
        }
    glEnd();

}


void drawBird() {
    static float birdX = 0.0f;
    static float birdY = 0.0f;
    static float birdSpeed = 0.05f;
    static float direction = 1.0f;

    static int parabolicMode = 0;
    static float parabolaH = 0.0f;
    static float parabolaK = -4.3f;         // ponto mais baixo da parábola
    static float parabolaA = 0.0f;
    static float parabolaStartX = 0.0f;
    static float initialY = 0.0f;

    static int initialized = 0;
    static int cooldown = 10;  // evita novas parábolas muito rapidamente

    // Obter bounding boxes
    BoundingBox penguinBox = getPenguinDadBoundingBox();
    BoundingBox birdBox = getBirdBoundingBox(birdX, birdY);

    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }

    // Movimento horizontal
    birdX += birdSpeed * direction;

    // Sorteia movimento parabólico com 10% de chance (com cooldown)
    if (!parabolicMode && cooldown <= 0) {
        int randNum = rand() % 100 + 1;
        if (randNum <= 10) {
            parabolicMode = 1;
            parabolaStartX = birdX;
            parabolaH = birdX + 2.0f * direction;  // vértice no meio do mergulho
            initialY = birdY;

            // Calcula A para que y volte a zero no fim da parábola
            float dx = parabolaStartX - parabolaH;
            parabolaA = (initialY - parabolaK) / (dx * dx);

            cooldown = 200;  // espera N frames antes de poder mergulhar de novo
        }
    }

    // Atualiza Y se estiver em modo parábola
    if (parabolicMode) {
        float x = birdX;
        birdY = parabolaA * (x - parabolaH) * (x - parabolaH) + parabolaK;

        // Finaliza parábola depois de 4 unidades (ida + volta)
        if ((direction > 0 && birdX >= parabolaH + 2.0f) ||
            (direction < 0 && birdX <= parabolaH - 2.0f)) {
            parabolicMode = 0;
            birdY = initialY;
        }
    }

    // Inverte direção ao sair da tela
    if (birdX > 7.0f || birdX < -5.0f) {
        direction *= -1;
    }

    // Diminui cooldown
    if (cooldown > 0) {
        cooldown--;
    }

    // Verificar colisão
    if (checkCollision(penguinBox, birdBox)) {
        if (!colisaoDetectada) {
            colisaoDetectada = true;
            framesDesdeUltimaColisao = 0;
            exit(0);
        }
    } else {
        framesDesdeUltimaColisao++;
        if (framesDesdeUltimaColisao > 10) { // Pequeno delay para evitar múltiplas detecções
            colisaoDetectada = false;
        }
    }

    // Desenha o pássaro
    glPushMatrix();
        glTranslated(birdX, birdY, 1.0);

        // Asa esquerda
        glPushMatrix();
            glTranslated(-2.0, 1.0, 1.0);
            glScaled(0.5, 0.2, 1.0);
            drawWing();
        glPopMatrix();

        // Asa direita
        glPushMatrix();
            glTranslated(0.0, 1.0, 1.0);
            glScaled(0.5, 0.2, 1.0);
            drawWing();
        glPopMatrix();
    glPopMatrix();
}


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

void adjustXDirections(){
    dadYPosition = dadYStandingPosition;
    glTranslated(dadXPosition, dadYStandingPosition, 0.0); // movimenta o pinguim
    float adjustXPosition = 0.15; //as costas do pinguim passam a casar com o ponto 0 do eixo y
    if(isDadGoingToLeft){
        glTranslated(-adjustXPosition, 0.0, 0.0);
        glScaled(-1.0, 1.0, 1.0); 
    }else{
        glTranslated(adjustXPosition, 0.0, 0.0);
    }
}

void adjustYDirections(bool isFalling){
    if(isFalling){
        dadYPosition = dadYSwimmingPosition;
    }
    glTranslated(dadXPosition, dadYPosition, 0.0); // movimenta o pinguim
    float adjustXPosition = 0.15; //as costas do pinguim passam a casar com o ponto 0 do eixo x
    glTranslated(0.0, -adjustXPosition, 0.0);
    glRotated(-90, 0.0, 0.0, 1.0);
    if(isDadGoingToLeft){
        glScaled(1.0, -1.0, 1.0); 
    }
}

void drawPenguinDad(){

    bool isChangingDirection = false; // ajusta o movimento no momento da troca de direção
    Fish carriedFish; // Peixe capturado

    if (isDadGoingToLeft != moveDadToLeft) {
        isChangingDirection =true;
        isDadGoingToLeft = moveDadToLeft;
        dadXPosition += (moveDadToLeft ? moveStep : -moveStep);
    }

    // Verifica colisão entre pinguim pai e peixe
    for (size_t i = 0; i < allFishes.size(); ++i) {
        float dist = distance(allFishes[i].x, allFishes[i].y, dadXPosition, dadYPosition);
        if (!hasFish && dist < 1.0f) { 
            hasFish = true;
            allFishes.erase(allFishes.begin() + i);  // Remove peixe
            continue;
        }
    }

    // Verifica colisão com filho
    BoundingBox pai = getPenguinDadBoundingBox();
    BoundingBox filho = getPenguinSonBoundingBox();

    if(hasFish && checkCollision(pai,filho)){
        
        // Configura novo peixe
        carriedFish.x = getRandomFloat(0.2f, 7.0f);  // Dentro da água
        carriedFish.y = getRandomFloat(-7.0f, -4.5f);     // Profundidade da água
        carriedFish.speed = 0.005f; // Velocidade padrão
        carriedFish.scale = 1.0f; 
        
        if(direcao % 2 == 0){
            carriedFish.movingRight = true;
        }else{
            carriedFish.movingRight = false;
        }
        direcao++;
      
        allFishes.push_back(carriedFish); // Adiciona à lista

        hasFish = false;
        score += 1;
    }

    bool isSwimming = false;
    // bool isRising = false;
    bool isFalling = false;
    if(isDadGoingToLeft){
        if(dadXPosition>1.4 || (dadXPosition<=1.4 && dadYPosition<-4)){
            isSwimming=true;
        }else if(dadXPosition>0 ){
            dadXPosition = 0;
            // isRising = true;
        }
    }else{
        if(dadXPosition>=0){
            isSwimming=true;
            if(dadXPosition<1){
                dadXPosition = 1;
                isFalling = true;
            }
        }
    }

    glPushMatrix();

        if(isSwimming){
            adjustYDirections(isFalling);
        }else{
            adjustXDirections();
        }        

        glPushMatrix();
        
            // limita o deslocamento no eixo x entre as extremidades da tela
            if(isSwimming==false){
                if(dadXPosition < (windowLeftLimit)){
                    dadXPosition = windowLeftLimit;
                }
            }else{
                if(dadXPosition>windowRightLimit){
                    dadXPosition = windowRightLimit;
                }else if(dadXPosition<=1.5){
                    dadXPosition = 1.5;
                }
                if(dadYPosition<=-7.5){
                    dadYPosition = -7.5;
                }else if(dadYPosition>=-4){
                    dadYPosition = -4;
                }
            }

            // desenha o peixe na boca
            if(hasFish){
                glPushMatrix();
                    glTranslated(0.5, 0.9, 0.0);
                    glRotated(-90, 0.0, 0.0, 1.0);
                    drawOneFish();
                glPopMatrix();
            }

            glPushMatrix();
                
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

void drawFish() {
    float leftLimit = 0.2f;
    float rightLimit = 8.5f;
    float upLimit = -4.2f;
    float downLimit = -7.8f;
    float adjustedLeft = leftLimit - 0.2f;
    float respawnRight = rightLimit - 0.1f;
    float respawnLeft = 0.0f;

    for (auto& fish : allFishes) {
        glPushMatrix();
            if (fish.movingRight) {
                fish.x += fish.speed;
                if (fish.x > rightLimit) {
                    fish.x = respawnLeft;
                    fish.y = getRandomFloat(downLimit, upLimit);
                }
                glTranslatef(fish.x, fish.y, 0.0f);
                drawOneFish();
            } else {
                fish.x -= fish.speed;
                if (fish.x < adjustedLeft) {
                    fish.x = respawnRight;
                    fish.y = getRandomFloat(downLimit, upLimit);
                }
                glTranslatef(fish.x, fish.y, 0.0f);
                glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
                glScalef(fish.scale, fish.scale, 1.0f);
                drawOneFish();
            }
        glPopMatrix();
    }
}

void drawPicture(){
    drawBackground();
    drawWater();
    drawFish();
    drawGrass();
    drawPenguinChick();
    drawPenguinDad();
    drawBird();
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

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            dadXPosition += moveStep;
            moveDadToLeft = false;
            break;
        case GLUT_KEY_LEFT:
            dadXPosition -= moveStep;
            moveDadToLeft = true;
            break;
        case GLUT_KEY_DOWN:
            dadYPosition -= moveStep;
            moveDadDown = true;
            break;
        case GLUT_KEY_UP:
            dadYPosition += moveStep;
            moveDadUp = true;
            break;
    }
    display();
}

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


void checkGameTime() {
    if (gameFinished) return;
    
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    
    if (elapsed >= GAME_DURATION) {
        gameFinished = true;
        system("clear"); // Para Linux/Mac
        std::cout << "============================\n";
        std::cout << "      VOCÊ GANHOU!\n";
        std::cout << "   Pontuação final: " << score << "\n";
        std::cout << "============================\n";
        exit(0); // Encerra o jogo
    }
}

void doFrame(int v){
    checkGameTime();  // Verifica se o tempo acabou
    glutPostRedisplay();
    glutTimerFunc(20, doFrame,0); // 50fps
}

int main(int argc, char** argv){
    startTime = std::chrono::steady_clock::now();  // Inicia o timer
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutTimerFunc(20, doFrame,0); // 50fps
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}