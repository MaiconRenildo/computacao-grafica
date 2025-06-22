/*
* mesa.cpp
*
*  Created on: 9 de mai. de 2023
*      Author: Suporte
*/
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>

using namespace std;

float contFrame = 0;
bool plusFrame = true;

struct XYZ
{
    float x;
    float y;
    float z;
};

#define NI 15
#define NJ 6
XYZ inp[NI+1][NJ+1];
#define RESOLUTIONI 3*NI
#define RESOLUTIONJ 3*NJ
XYZ outp[RESOLUTIONI][RESOLUTIONJ];

GLfloat marrom[4] = {101.0/255,67.0/244,33.0/255,1};
GLfloat green[4] = {0.047, 0.569, 0.027,1};
GLfloat red[4] = {1, 0, 0,1};
GLfloat blue[4] = {0, 0, 1,1};
GLfloat cinza[4] = {0.2, 0.2, 0.2, 0.7};
GLfloat cinza1[4] = {0.2, 0.2, 0.2, 1};
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat direction[] = { 10.0, 10.0, 10.0, 1.0 };
GLfloat direction1[] = { 0.0, -10.0, 0.0, 1.0 };


double BezierBlend(int k,double mu, int n)
{
   int nn,kn,nkn;
   double blend=1;

   nn = n;
   kn = k;
   nkn = n - k;

   while (nn >= 1) {
      blend *= nn;
      nn--;
      if (kn > 1) {
         blend /= (double)kn;
         kn--;
      }
      if (nkn > 1) {
         blend /= (double)nkn;
         nkn--;
      }
   }
   if (k > 0)
      blend *= pow(mu,(double)k);
   if (n-k > 0)
      blend *= pow(1-mu,(double)(n-k));

   return(blend);
}



void generateControlPoint()
{
	   //int nMax = 2;
	   //int nMin = -2;
	   int i,j;
	   srandom(time(NULL));
	   for (i=0;i<=NI;i++) {
	      for (j=0;j<=NJ;j++) {
	         inp[i][j].x = i;
	         inp[i][j].y = j;
	         //inp[i][j].z = random()%((nMax+1)-nMin) + nMin;
	        inp[i][j].z = 4*sin(i);
	      }
	   }
}

void Surface()
{
   int i,j,ki,kj;
   double mui,muj,bi,bj;
   /* Create a random surface */
   for (i=0;i<RESOLUTIONI;i++) {
      mui = i / (double)(RESOLUTIONI-1);
      for (j=0;j<RESOLUTIONJ;j++) {
         muj = j / (double)(RESOLUTIONJ-1);
         outp[i][j].x = 0;
         outp[i][j].y = 0;
         outp[i][j].z = 0;
         for (ki=0;ki<=NI;ki++) {
            bi = BezierBlend(ki,mui,NI);
            for (kj=0;kj<=NJ;kj++) {
               bj = BezierBlend(kj,muj,NJ);
               outp[i][j].x += (inp[ki][kj].x * bi * bj);
               outp[i][j].y += (inp[ki][kj].y * bi * bj);
               outp[i][j].z += (inp[ki][kj].z * bi * bj);
            }
         }
      }
   }

}


void draw_surface(GLfloat c[4]){
    // front
	glMaterialfv(GL_FRONT, GL_SPECULAR,cinza1);
    glMaterialfv(GL_FRONT,GL_AMBIENT,c);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,c);
    glMaterialf(GL_FRONT,GL_SHININESS,120);

    // back
    glMaterialfv(GL_BACK,GL_AMBIENT,c);
    glMaterialfv(GL_BACK,GL_DIFFUSE,c);

    for(int i=0;i<RESOLUTIONI-1;i++) {
        for(int j=0;j<RESOLUTIONJ-1;j++) {
            XYZ uv, u, v;
            u.x = outp[i+1][j].x - outp[i][j].x;
            u.y = outp[i+1][j].y - outp[i][j].y;
            u.z  = outp[i+1][j].z - outp[i][j].z;

            v.x = outp[i][j+1].x - outp[i][j].x;
            v.y = outp[i][j+1].y - outp[i][j].y;
            v.z  = outp[i][j+1].z - outp[i][j].z;

            // produto vetorial - calculo da normal
            uv.x = u.y * v.z - u.z * v.y;
            uv.y = u.z * v.x - u.x * v.z;
            uv.z = u.x * v.y - u.y * v.x;

            // normalização

            uv.x = uv.x/(sqrt(uv.x*uv.x + uv.y*uv.y + uv.z*uv.z));
            uv.y = uv.y/(sqrt(uv.x*uv.x + uv.y*uv.y + uv.z*uv.z));
            uv.z = uv.z/(sqrt(uv.x*uv.x + uv.y*uv.y + uv.z*uv.z));
            // o efeito muda pq do jeito que foi feito acima a primeira linha alterar uv.x  
            // que impacta no uv.y e assim por diante
            // float norm = sqrt(uv.x*uv.x + uv.y*uv.y + uv.z*uv.z);
            // uv.x /= norm;
            // uv.y /= norm;
            // uv.z /= norm;


            glNormal3f(uv.x, uv.y, uv.z);

            glBegin(GL_QUADS);
            glVertex3f(outp[i][j].x, outp[i][j].y, outp[i][j].z);
            glVertex3f(outp[i][j+1].x,  outp[i][j+1].y,  outp[i][j+1].z);
            glVertex3f(outp[i+1][j+1].x,outp[i+1][j+1].y,outp[i+1][j+1].z);
            glVertex3f(outp[i+1][j].x,  outp[i+1][j].y,  outp[i+1][j].z);
            glEnd();
        }

    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(-2,5, 11, 0, 0, 0, 0, 1, 0);
    gluLookAt(0,20, 6, 0, 0, 0, 0, 0, 1);
    //gluLookAt(0,0, 20, 0, 0, 0, 0, 1, 0);

    //glTranslatef(-20,0,0);
    //glTranslatef(contFrame*2,0,0);

    Surface();

    glTranslatef(-8,0,0);
    draw_surface(green);

    glTranslatef(-3,0,6);
    draw_surface(red);

    glTranslatef(11,0,-12);
    draw_surface(blue);

    glFlush();
}


void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    GLfloat aspect = GLfloat(w) / GLfloat(h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,aspect, 0.1,40);
}

void init() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT1, GL_AMBIENT, cinza1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_POSITION, direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
}

void doFrame(int v) {

	contFrame = contFrame + 0.005;
	   for (int i=0;i<=NI;i++) {
	      for (int j=0;j<=NJ;j++) {
	         inp[i][j].z = 3*sin(contFrame + i);
	    	  //inp[i][j].z = -4*cos(cos(contFrame + i)) *sin(contFrame + i);

	      }
	   }

    glutPostRedisplay();
    glutTimerFunc(5,doFrame,0);
}

int main(int argc, char** argv) {
    generateControlPoint();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(5,doFrame,0);
    init();
    glutMainLoop();
}

