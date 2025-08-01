#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();



  glEnable(GL_LIGHT0);

  // direita e mais ao fundo(z)
  glPushMatrix();
  glTranslatef(1, 0.0, -3.0);
  glutSolidSphere(0.5, 30, 30);
  glPopMatrix();

  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  // esquerda e ponto zero
  glPushMatrix();
  glTranslatef(-1, 0.0, 0.0);
  glutSolidSphere(0.5, 30, 30);
  glPopMatrix();

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  // meio, mais acima(y) e mais ao fundo ainda(z)
  glPushMatrix();
  glTranslatef(0.0, 1.0, -5.5);
  glutSolidSphere(0.5, 30, 30);
  glPopMatrix();

  glDisable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  // meio, mais abaixo, e mais a frente(z)
  glPushMatrix();
  glTranslatef(0.0, -1.0, 6);
  glutSolidSphere(0.5, 30, 30);
  glPopMatrix();

  glDisable(GL_LIGHT3);



  glFlush();
}





void init() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-2.5, 2.5, -2.5, 2.5, 0, 2.5);

  // 2 - Altere os parâmetros da função glOrtho para aumentar volume visualizado
  // (em pelo menos 4 unidades em cada direção). Descreva a cena é gerada após essa alteração.
  // glOrtho(-10.0, 10.0, -10.0, 10.0, 0, 10.0);

  // 3 - Utilize o comando "gluPerspective (60,1, 0.1, 15);" para alterar o modo de projeção.
  // gluPerspective(60,1, 0.1, 15);


  // 4 - Faça a alteração necessária no código para visualizar todos os objetos que estão sendo
  //  desenhados, utilizando a projeção perspectiva.
  // gluPerspective (60,1, 0.1, 15);
  // gluLookAt(0, 0, 9,    0, 0, 0,     0, 1, 0);


  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat pink[] = { 1.0, 0.5, 1.0, 1.0 };
  GLfloat pink2[] = { 0.5, 1.0, 0.5, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 0.0, 0.0, 10.0, 1.0 };
  GLfloat direction1[] = { 0.0,0.0, 10.0, 1.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);

  glLightfv(GL_LIGHT1, GL_AMBIENT, black);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightfv(GL_LIGHT1, GL_POSITION, direction1);

  glLightfv(GL_LIGHT2, GL_AMBIENT, black);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, pink);
  glLightfv(GL_LIGHT2, GL_SPECULAR, white);
  glLightfv(GL_LIGHT2, GL_POSITION, direction1);

  glLightfv(GL_LIGHT3, GL_AMBIENT, black);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, pink2);
  glLightfv(GL_LIGHT3, GL_SPECULAR, white);
  glLightfv(GL_LIGHT3, GL_POSITION, direction1);

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

}


int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 600);
  glutCreateWindow("");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}