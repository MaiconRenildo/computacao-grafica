#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#ifndef edu_jmu_cs_Materials_h
#define edu_jmu_cs_Materials_h

float timer= 0.0;


struct XYZ
{
    float x;
    float y;
    float z;
};

#define NI 18
#define NJ 6
XYZ inp[NI+1][NJ+1];
#define RESOLUTIONI 3*NI
#define RESOLUTIONJ 3*NJ
XYZ outp[RESOLUTIONI][RESOLUTIONJ];




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
	   int nMax = 2;
	   int nMin = -2;
	   int i,j;
	   srandom(time(NULL));
	   for (i=0;i<=NI;i++) {
	      for (j=0;j<=NJ;j++) {
	         inp[i][j].x = i;
	         inp[i][j].y = j;
	        //  inp[i][j].z = random()%((nMax+1)-nMin) + nMin;
	        inp[i][j].z = 4*sin(timer-i);
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


int BRASS = 0;
int BRONZE = 1;
int CHROME = 2;
int COPPER = 3;
int GOLD = 4;
int PEWTER = 5;
int SILVER = 6;
int JADE = 7;
int OBSIDIAN = 8;
int PEARL = 9;
int RUBY = 10;
int TURQUOISE = 11;
int BLACK_PLASTIC = 12;
int BLACK_RUBBER = 13;
int LAST_MATERIAL = 14;
int WOOD = 15;
int VELVET = 16;
int RED_SURFACE = 17;
int GREEN_SURFACE = 18;
int BLUE_SURFACE = 19;
int material = -1;




float SPECULAR_EXPONENTS[] =
{
27.897400, // BRASS
25.600000, // BRONZE
76.800003, // CHROME
12.800000, // COPPER
51.200001, // GOLD
09.846150, // PEWTER
51.200001, // SILVER
76.800003, // EMERALD
12.800000, // JADE
38.400002, // OBSIDIAN
11.264000, // PEARL
76.800003, // RUBY
12.800000, // TURQUOISE
32.000000, // BLACK_PLASTIC
10.000000, // BLACK_RUBBER
40,         // WOOD
20,         // VELVET
80.0f,      // RED_SURFACE (novo)
80.0f,      // GREEN_SURFACE (novo)
80.0f       // BLUE_SURFACE (novo)
};


float MATERIAL_COLORS[][3][4] =
{
// BRASS 0
{
{0.329412, 0.223529, 0.027451, 1.000000}, // Ambient RGBA
{0.780392, 0.568627, 0.113725, 1.000000}, // Diffuse RGBA
{0.992157, 0.941176, 0.807843, 1.000000} // Specular RGBA
},

// BRONZE 1
{
{0.212500, 0.127500, 0.054000, 1.000000},
{0.714000, 0.428400, 0.181440, 1.000000},
{0.393548, 0.271906, 0.166721, 1.000000}
},

// CHROME 2
{
{0.250000, 0.250000, 0.250000, 1.000000},
{0.400000, 0.400000, 0.400000, 1.000000},
{0.774597, 0.774597, 0.774597, 1.000000}
},

// COPPER 3
{
{0.191250, 0.073500, 0.022500, 1.000000},
{0.703800, 0.270480, 0.082800, 1.000000},
{0.256777, 0.137622, 0.086014, 1.000000}
},

// GOLD 4
{
{0.247250, 0.199500, 0.074500, 1.000000},
{0.751640, 0.606480, 0.226480, 1.000000},
{0.628281, 0.555802, 0.366065, 1.000000}
},

// PEWTER 5
{
{0.105882, 0.058824, 0.113725, 1.000000},
{0.427451, 0.470588, 0.541176, 1.000000},
{0.333333, 0.333333, 0.521569, 1.000000}
},

// SILVER 6
{
{0.192250, 0.192250, 0.192250, 1.000000},
{0.507540, 0.507540, 0.507540, 1.000000},
{0.508273, 0.508273, 0.508273, 1.000000}
},

// EMERALD 7
{
{0.021500, 0.174500, 0.021500, 0.550000},
{0.075680, 0.614240, 0.075680, 0.550000},
{0.633000, 0.727811, 0.633000, 0.550000}
},

// JADE 8
{
{0.135000, 0.222500, 0.157500, 0.950000},
{0.540000, 0.890000, 0.630000, 0.950000},
{0.316228, 0.316228, 0.316228, 0.950000}
},

// OBSIDIAN 9
{
{0.053750, 0.050000, 0.066250, 0.820000},
{0.182750, 0.170000, 0.225250, 0.820000},
{0.332741, 0.328634, 0.346435, 0.820000}
},

// PEARL 10
{
{0.250000, 0.207250, 0.207250, 0.922000},
{1.000000, 0.829000, 0.829000, 0.922000},
{0.296648, 0.296648, 0.296648, 0.922000}
},

// RUBY 11
{
{0.174500, 0.011750, 0.011750, 1.0},
{0.614240, 0.041360, 0.041360, 1.0},
{0.727811, 0.626959, 0.626959, 1.0}
},

// TURQUOISE 12
{
{0.100000, 0.187250, 0.174500, 0.800000},
{0.396000, 0.741510, 0.691020, 0.800000},
{0.297254, 0.308290, 0.306678, 0.800000}
},

// BLACK_PLASTIC 13
{
{0.000000, 0.000000, 0.000000, 1.000000},
{0.010000, 0.010000, 0.010000, 1.000000},
{0.500000, 0.500000, 0.500000, 1.000000}
},

// BLACK_RUBBER 14
{
{0.020000, 0.020000, 0.020000, 1.000000},
{0.010000, 0.010000, 0.010000, 1.000000},
{0.400000, 0.400000, 0.400000, 1.000000}
},

// WOOD 15
{
{101.0/255,67.0/255,33.0/255,1},
{101.0/255,67.0/255,33.0/255,1},
{101.0/255,67.0/255,33.0/255,1}
},

// VELVET 16
{
{1.0/255, 50.0/255, 32.0/255,1},
{1.0/255, 50.0/255, 32.0/255,1},
{1.0/255, 50.0/255, 32.0/255,1}
},

// RED_SURFACE 17 - Definindo cores para a superfície vermelha
{
{0.5f, 0.0f, 0.0f, 0.8f}, // Ambient
{0.8f, 0.0f, 0.0f, 0.8f}, // Diffuse
{1.0f, 0.2f, 0.2f, 0.8f}  // Specular
},

// GREEN_SURFACE 18 - Definindo cores para a superfície verde
{
{0.0f, 0.5f, 0.0f, 0.8}, // Ambient
{0.0f, 0.8f, 0.0f, 0.8}, // Diffuse
{0.2f, 1.0f, 0.2f, 0.8}  // Specular
},

// BLUE_SURFACE 19 - Definindo cores para a superfície azul
{
{0.0f, 0.0f, 0.5f, 0.8f}, // Ambient
{0.0f, 0.0f, 0.8f, 0.8f}, // Diffuse
{0.2f, 0.2f, 1.0f, 0.8f}  // Specular
}
};

#endif

static GLfloat colorWhite[] = { 0.5, 0.5, 0.5, 1.0 };

static GLfloat cinza[4] = {0.2, 0.2, 0.2, 0.7};
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 0.5, 0.5, 0.5, 1.0 };

static GLfloat light1Pos[] = { 10.0, 10.0, 0.0, 1 };

void aplicaMaterial(int matIndex) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, MATERIAL_COLORS[matIndex][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MATERIAL_COLORS[matIndex][1]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_COLORS[matIndex][2]);
    glMaterialf(GL_FRONT, GL_SHININESS, SPECULAR_EXPONENTS[matIndex]);
}

void DrawTableLeg() {
    aplicaMaterial(WOOD);
    glPushMatrix();
        glScalef(0.2f, 1.0f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawBezierSurface() {
    int i, j;
    for (i = 0; i < RESOLUTIONI - 1; i++) {
        for (j = 0; j < RESOLUTIONJ - 1; j++) {
            glBegin(GL_QUADS);
                glVertex3f(outp[i][j].x,     outp[i][j].y,     outp[i][j].z);
                glVertex3f(outp[i+1][j].x,   outp[i+1][j].y,   outp[i+1][j].z);
                glVertex3f(outp[i+1][j+1].x, outp[i+1][j+1].y, outp[i+1][j+1].z);
                glVertex3f(outp[i][j+1].x,   outp[i][j+1].y,   outp[i][j+1].z);
            glEnd();
        }
    }
}


void DrawTable(){
    aplicaMaterial(WOOD);
    glPushMatrix();
        glScalef(7.0f, 0.1f, 3.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Pés da mesa
    glPushMatrix(); 
        glTranslatef( -3.0f, -1.0f, -1.0f); 
        glScalef(1.0f, 1.9f, 1.0f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef( -3.0f, -1.0f, 1.2f); 
        glScalef(1.0f, 1.9f, 1.0f);
        DrawTableLeg(); 
    glPopMatrix();

    glPushMatrix();
        glTranslatef( 3.0f, -1.0f, -1.0f); 
        glScalef(1.0f, 1.9f, 1.0f);
        DrawTableLeg(); 
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef( 3.0f, -1.0f, 1.2f); 
        glScalef(1.0f, 1.9f, 1.0f);
        DrawTableLeg(); 
    glPopMatrix(); 
}


void idle() {
    timer += 0.01f;
    generateControlPoint();
    Surface();
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 20.0, 6.0,   // posição da câmera
        0.0, 0.0, 0.0, // olhar para o centro da superfície
        0.0, 0.0, 1.0       // "up" é eixo z
    );

    glPushMatrix();
        glTranslatef(-0.0f, 0.0f, 6.0);
        aplicaMaterial(RED_SURFACE);
        DrawBezierSurface();
    glPopMatrix(); // 

    
    glPushMatrix();
        glTranslatef(-12.0f, 0.0f, 0.0);
        aplicaMaterial(GREEN_SURFACE);
        
        DrawBezierSurface();
    glPopMatrix(); // 

    glPushMatrix();
        glTranslatef(-24.0f, 0.0f, -8.0);
        aplicaMaterial(BLUE_SURFACE);
        DrawBezierSurface();
    glPopMatrix(); // 


    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w/(float)h, 1.0, 100.0);
}

void init() {
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 0.0, -10.0, 0.0, 1.0 };
    GLfloat direction1[] = { 0.0, 10.0, 0.0, 1.0 };

    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    glutIdleFunc(idle);  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mesa 3D");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}