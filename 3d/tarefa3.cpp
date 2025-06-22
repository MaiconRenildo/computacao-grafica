// Mesa com bola em cima

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.

void drawTableLegs(){
    // pes
    // inferior esquerdo
    glPushMatrix(); 
        glTranslatef(-1.4, 0, -0.9);
        glScaled(0.1, 2, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // inferior direito
    glPushMatrix(); 
        glTranslatef(1.4, 0, -0.9);
        glScaled(0.1, 2, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // superior esquerdo
    glPushMatrix(); 
        glTranslatef(-1.4, 0, 0.9);
        glScaled(0.1, 2, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    // superior direito
    glPushMatrix(); 
        glTranslatef(1.4, 0, 0.9);
        glScaled(0.1, 2, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawTableCover(){
    // tampa
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glPushMatrix(); 
            glScaled(4, 0.1, 3);
            glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();
}

void drawTable(){
    drawTableLegs();
    drawTableCover();
}

void drawSphere(){
    glPushMatrix();
        glTranslatef(0, 1.5, 0);
        glPushMatrix(); 
            glutSolidSphere(0.5, 20,20);
        glPopMatrix();
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 1, 4,0,0,0, 0, 1, 0);
    // Make a torus floating 0.5 above the x-z plane.  The standard torus in
    // the GLUT library is, perhaps surprisingly, a stack of circles which
    // encircle the z-axis, so we need to rotate it 90 degrees about x to
    // get it the way we want.
    drawTable();
    drawSphere();
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
    //     glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
    //   } else {
    //     // height is smaller, so stretch out the width
    //     glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
    //   }
  gluPerspective(45,aspect, 0.1, 40);
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

  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);              // so the renderer considers depth

}

// The usual application statup code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}