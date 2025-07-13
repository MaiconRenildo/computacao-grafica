#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>


void drawAxes() {
  glLineWidth(2.0); // Espessura da linha
  glBegin(GL_LINES);

  // Eixo X
  glColor3f(0.8, 0.0, 0.0); // vermelho escuro para X+ (positivo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
  glColor3f(1.0, 0.6, 0.6); // vermelho claro para X- (negativo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);

  // Eixo Y
  glColor3f(0.0, 0.8, 0.0); // verde escuro para Y+ (positivo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
  glColor3f(0.6, 1.0, 0.6); // verde claro para Y- (negativo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);

  // Eixo Z
  glColor3f(0.0, 0.0, 0.8); // azul escuro para Z+ (positivo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
  glColor3f(0.6, 0.6, 1.0); // azul claro para Z- (negativo)
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);

  glEnd();

  // Marcadores nos sentidos positivos e negativos dos eixos:
  glPushMatrix();
      // Marcador para X+
      glTranslatef(10.0f, 0.0f, 0.0f); // Move para X+
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Roda o cone para apontar para +X
      glColor3f(0.8f, 0.0f, 0.0f); // vermelho escuro para X+
      glutSolidCone(0.3f, 1.0f, 20, 20);
  glPopMatrix();

  glPushMatrix();
      // Marcador para Y+
      glTranslatef(0.0f, 10.0f, 0.0f); // Move para Y+
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Roda o cone para apontar para +Y
      glColor3f(0.0f, 0.8f, 0.0f); // verde escuro para Y+
      glutSolidCone(0.3f, 1.0f, 20, 20);
  glPopMatrix();

  glPushMatrix();
      // Marcador para Z-
      glTranslatef(0.0f, 0.0f, -15.0f); // Move para Z-
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Roda o cone para apontar para -Z
      glColor3f(0.6f, 0.6f, 1.0f); // azul claro para Z-
      glutSolidCone(0.3f, 1.0f, 20, 20);
  glPopMatrix();

  // se o lookat está definido com z=2.5, near = 1 e far=20,
  // então eu só deveria enxergar do ponto z=1.5 em diante(sentido negativo)
  glPushMatrix();
  // Marcador para Z+
    glTranslatef(0.0f, 0.0f, 4.2f); // Move para Z+
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Roda o cone para apontar para +Z
    glColor3f(0.0f, 0.0f, 0.8f); // azul escuro para Z+
    glutSolidCone(0.3f, 1.0f, 20, 20);
  glPopMatrix();

  glLineWidth(1.0); // Volta à espessura padrão
}


// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  // vejo as figuras de frente: a bola está um pouco a frente do cone
  // gluLookAt(
  //   0, 0, 1.0,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 

  // movo o olho para o lado direito. Então ele fica de frente para a bola
  // gluLookAt(
  //   1, 0, 1.0,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 


  // movo o olho para o lado esquerdo. Então ele fica de frente para o cone
  // gluLookAt(
  //   -1, 0, 1.0,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 

  // olha a imagem de cima, ou seja, o olho fica no topo
  // gluLookAt(
  //   0, 1, 1.0,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 

  // olha a imagem de baixo, ou seja, o olho fica "abaixo do chão"
  // gluLookAt(
  //   0, -1, 1.0,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 

  // não entendi o z
  // quando ele é +- 0.1, a imagem aparece. Quando é zero não aparece
  // gluLookAt(
  //   0, 0, -1,
  //   0,0,0, // olha para o centro
  //   0, 1, 0 // significa que o eixo Y positivo do mundo aponta para cima
  // ); 

  gluLookAt(0, 0, 2.5,0,0,0, 0, 1, 0);

  // Make a torus floating 0.5 above the x-z plane.  The standard torus in
  // the GLUT library is, perhaps surprisingly, a stack of circles which
  // encircle the z-axis, so we need to rotate it 90 degrees about x to
  // get it the way we want.

  // glPushMatrix();
  //   glTranslatef(-0.75, 0.5, 0.0);
  //   glRotatef(90.0, 1.0, 0.0, 0.0);
  //   glutSolidTorus(0.275, 0.85, 16, 40);
  // glPopMatrix();
  drawAxes();

  // Make a cone.  The standard cone "points" along z; we want it pointing
  // along y, hence the 270 degree rotation about x.
  // glPushMatrix();
  //   glTranslatef(-0.75, -0.5, 0.0);
  //   glRotatef(270.0, 1.0, 0.0, 0.0);
  //   glutSolidCone(1.0, 2.0, 70, 12);
  // glPopMatrix();

  // // Add a sphere to the scene.
  // glPushMatrix();
  //   glTranslatef(0.75, 0.5, 2.0);
  //   glutSolidSphere(1.0, 30, 30);
  // glPopMatrix();


  glFlush();
}

// We don't want the scene to get distorted when the window size changes, so
// we need a reshape callback.  We'll always maintain a range of -2.5..2.5 in
// the smaller of the width and height for our viewbox, and a range of -10..10
// for the viewbox depth.

//PARAMETROS glOrtho
//left, right :Specify the coordinates for the left and right vertical clipping planes.
//bottom, top :Specify the coordinates for the bottom and top horizontal clipping planes.
//nearVal, farVal:Specify the distances to the nearer and farther depth clipping planes. These values are negative if the plane is to be behind the viewer.


void reshape(GLint w, GLint h) {
  glMatrixMode(GL_PROJECTION);
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();

//  if (w <= h) {
//     // width is smaller, so stretch out the height
//     // glOrtho(-10, 10, -10/aspect, 10/aspect, -10.0, 20.0);
//     glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
//   } else {
//     // height is smaller, so stretch out the width
//     // glOrtho(-10*aspect, 10*aspect, -10, 10, -10.0, 20.0);
//     glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
//   }

  glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, 1.0, 20.0);
  std:: cout << "left = " << -2.5
    << ", right = " << 2.5
    << ", bottom = " << -2.5/aspect
    << ", top = " << 2.5/aspect
    << ", near = " << 1.0
    << ", far = " << 20.0 << std:: endl;
  // gluPerspective (60,aspect, 0.1, 15);

}

// Performs application specific initialization.  It defines lighting
// parameters for light source GL_LIGHT0: black for ambient, yellow for
// diffuse, white for specular, and makes it a directional source
// shining along <-1, -1, -1>.  It also sets a couple material properties
// to make cyan colored objects with a fairly low shininess value.  Lighting
// and depth buffer hidden surface removal are enabled here.
void init() {

  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 0.0, -10.0, 0.0, 1.0 };
  GLfloat direction1[] = { 0.0, 10.0, 0.0, 1.0 };

  // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  // glMaterialf(GL_FRONT, GL_SHININESS, 30);

  // glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  // glLightfv(GL_LIGHT0, GL_POSITION, direction);

  // glLightfv(GL_LIGHT1, GL_AMBIENT, black);
  // glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  // glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  // glLightfv(GL_LIGHT1, GL_POSITION, direction1);

  // glEnable(GL_LIGHTING);                // so the renderer considers light
  // glEnable(GL_LIGHT0);                  // turn LIGHT0 on
  // glEnable(GL_LIGHT1);
  // glEnable(GL_DEPTH_TEST);              // so the renderer considers depth

}

// The usual application statup code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(1200, 1200);
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}