#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float w = 800;
float h = 600;
// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  // câmera da direita para a esquerda
  // Canto inferior direito
  glPushMatrix();
    gluLookAt(5,0,0, 0,0,0, 0,1,0);
    glViewport(w/2, 0, w/2, h/2); // Posição (400, 0), tamanho (400, 300) 
    glEnable(GL_LIGHT2); // fica verde
    glutSolidTeapot(1);
    glDisable(GL_LIGHT2);
  glPopMatrix();

  // de frente
  // canto superior direito
  glPushMatrix();
    glViewport(w/2, h/2, w/2, h/2);
    glEnable(GL_LIGHT1); // fica azul
    glutSolidTeapot(1);
    glDisable(GL_LIGHT1);
  glPopMatrix();

  // de cima para baixo
  // Canto superior esquerdo
  glPushMatrix();
    gluLookAt(0,5,0, 0,0,0, 0,0,-1); // a câmera está no y=5 e o "cima" é o Z negativo
    glViewport(0,h/2, w/2, h/2); // Posição (0, 300), tamanho (400, 300)
    glEnable(GL_LIGHT2); // fica verde
    glutSolidTeapot(1);
    glDisable(GL_LIGHT2);
  glPopMatrix();

  // de baixo para cima
  // Canto inferior esquerdo
  glPushMatrix();
    gluLookAt(0,-5,0, 0,0,0, 0,0,1); // a câmera está no y=5 e o "cima" é o Z positivo
    glViewport(0, 0, w/2, h/2); // Posição (0, 0), tamanho (400, 300)
    glEnable(GL_LIGHT1); // fica azul
    glutSolidTeapot(1);
    glDisable(GL_LIGHT1);
  glPopMatrix();

  glFlush();
}


void reshape(GLint w, GLint h) {
  glMatrixMode(GL_PROJECTION);
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();

 if (w <= h) {
    // width is smaller, so stretch out the height
    glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
  } else {
    // height is smaller, so stretch out the width
    glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
  }

  // gluPerspective (60, aspect, 0.1, 15);
}


void init() {
  // glClearColor(0.5, 0.7, 1.0, 1.0); // define a cor de fundo. Caso não haja, utiliza o preto
  // cores no formato RGBA, onde A é a transparência
  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
  GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
  // definição da direção das luzes. O último parâmetro define se é posicional(1 - ponto de luz) ou direcional(0 - como o sol)
  GLfloat direction[] = { 0.0, -20.0, 0.0, 1.0 };
  GLfloat direction1[] = { 0.0, 00.0, 10.0, 1.0 };

  // define as propriedades do material do objeto
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan); //cor ambiente e difusa(verde + azul)
  glMaterialfv(GL_FRONT, GL_SPECULAR, white); // cor do brilho especular, aquele ponto brilhante
  // que aparece quando a luz reflete diretamente na direção do observador, como no reflexo de uma superfície polida.
  glMaterialf(GL_FRONT, GL_SHININESS, 60); // Controla o tamanho e a intensidade do brilho especular.
  // 1-20 _ mais fraco e espalhado | 60 - 128 _ pequeno e intenso | fora desse intervalo fica tudo branco


  glLightfv(GL_LIGHT1, GL_AMBIENT, black);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white); // (1,1,1)×(0,1,1)=(0,1,1) → Ciano puro (verde + azul)
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightfv(GL_LIGHT1, GL_POSITION, direction1);

  glLightfv(GL_LIGHT2, GL_AMBIENT, black);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, yellow); // (1,1,0)×(0,1,1)=(0,1,0) → Verde puro
  glLightfv(GL_LIGHT2, GL_SPECULAR, white);
  glLightfv(GL_LIGHT2, GL_POSITION, direction1);

  // Ativa o sistema de iluminação do OpenGL. Se não estiver habilitado o 
  // OpenGL não considera as luzes nem os materiais, então as cores dos objetos ficariam controladas apenas por glcolor
  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
}

// The usual application statup code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(w, h);
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
