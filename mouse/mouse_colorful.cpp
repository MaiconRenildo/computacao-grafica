#include <GL/glut.h>
#include <iostream>
#include <tuple>

void init(void);
void display(void);

// variaveis globais
bool isStarted = false;
float width = 0.05, height = 0.05;
float mousePositionX, mousePositionY;
const int windowWidth = 800, windowHeight = 800;

void init(void){
    // define a cor de background da janela
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // define o sistema de visualização - tipo de projeção
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-1, 1, -1, 1, -1, 1);
}

void draw(int x, int y){
    isStarted = true;
    mousePositionX = x;
    mousePositionY = y;
}


std::tuple<float, float> coordinate_converter() {
    float x =((mousePositionX / (windowWidth/2)) - 1.0);
    float y = (1.0 - (mousePositionY / (windowHeight/2)));
    return std::make_tuple(x, y);
}

void display() {
    if(isStarted==false){
        glClear(GL_COLOR_BUFFER_BIT);
    }else{
        float x, y;
        std::tie(x, y) = coordinate_converter();
        // quadrado centralizado no local do clique
        float basex = x-(width/2);
        float basey = y-(height/2);
        glColor3f(0.5, 0.0, 1.0); // roxo 
        glBegin(GL_QUADS);
            glVertex2f(basex,basey);
            glVertex2f(basex + width, basey);
            glVertex2f(basex + width, basey + height);
            glVertex2f(basex, basey + height);
        glEnd();
        // ponto no local do clique
        glColor3f(0.0, 0.0, 0.0); // preto
        glPointSize(5.0); // Define o tamanho do ponto
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
    glFlush(); // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
}



void mouse(int button, int action, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:{
            draw(x, y);
            break;
        }
        case GLUT_MIDDLE_BUTTON:{
            break;
        }
        case GLUT_RIGHT_BUTTON:{
            isStarted=false;
            break;
        }
        default: break;
    }
    display();
}


int main(int argc, char** argv){
    //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
    //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
    glutInit(&argc, argv);

    //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
    // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
    // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
    glutInitWindowSize (windowWidth, windowHeight);
    glutInitWindowPosition (200, 200);

    // Cria uma janela e define seu título
    glutCreateWindow ("Primeiro OpenGL");

    //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
    init();

    // Define display() como a função de desenho (display callback) para a janela corrente.
    // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
    glutDisplayFunc(display);

    // Indica que sempre que uma tecla for pressionada no teclado, GLUT deverá chama a função keyboard() para tratar eventos de teclado (keyboard callback).
    // A função de teclado deve possuir o seguinte protótipo:
    //    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    //Inicia o loop de processamento de desenhos com GLUT.
    // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
    glutMainLoop();

    return 0;
}
