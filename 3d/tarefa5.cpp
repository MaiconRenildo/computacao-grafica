// Mesa colorida

#include <GL/glut.h>
#ifndef edu_jmu_cs_Materials_h
#define edu_jmu_cs_Materials_h

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
40,
20
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
{0.174500, 0.011750, 0.011750, 1.0}, // trocamos para 0.550000
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

{
{101.0/255,67.0/255,33.0/255,1},
{101.0/255,67.0/255,33.0/255,1},
{101.0/255,67.0/255,33.0/255,1}
},

{
{1.0/255, 50.0/255, 32.0/255,1},
{1.0/255, 50.0/255, 32.0/255,1},
{1.0/255, 50.0/255, 32.0/255,1}
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

void drawTableMat(){
    glPushMatrix();
        aplicaMaterial(COPPER);
        glScalef(1.2f, 0.11f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawGlass() {
    GLUquadric* quad = gluNewQuadric();

    // GLfloat glassAmbient[]  = {0.3f, 0.3f, 0.3f, 0.3f};
    // GLfloat glassDiffuse[]  = {0.8f, 0.8f, 0.8f, 0.3f};
    // GLfloat glassSpecular[] = {0.9f, 0.9f, 0.9f, 0.3f};
    // GLfloat glassShininess  = 50.0f;

    // glMaterialfv(GL_FRONT, GL_AMBIENT, glassAmbient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, glassDiffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, glassSpecular);
    // glMaterialf(GL_FRONT, GL_SHININESS, glassShininess);
    aplicaMaterial(BLACK_PLASTIC);
    
    // Base
    glPushMatrix();
        glTranslatef(0.0f, -0.4f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, 0.25f, 64, 1);
        glTranslatef(0.0f, 0.0f, -0.02f);
        gluCylinder(quad, 0.25f, 0.25f, 0.02f, 64, 1);
    glPopMatrix();

    // Corpo
    glPushMatrix();
        glTranslatef(0.0f, -0.4f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 0.25f, 0.20f, 0.8f, 64, 64); // Corpo
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void DrawPlate(){
    GLUquadric* quad = gluNewQuadric();

    aplicaMaterial(BLACK_PLASTIC);
    // Base
    glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f); // Levemente abaixo
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, 0.16f, 64, 1); // Centro do prato
    glPopMatrix();

    // Parte interna arredondada (como funil raso)
    for (float i = 0; i < 10; i++) {
        float r1 = 0.16f + i * 0.012f;
        float r2 = r1 + 0.012f;
        float h = 0.005f;
        glPushMatrix();
            glTranslatef(0.0f, -0.05f + i * h, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, r1, r2, h, 64, 1);
        glPopMatrix();
    }

    // Borda
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 0.2f, 0.22f, 0.02f, 64, 1);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void DrawLighting(){
    glPushMatrix();
        // aplicaMaterial(RUBY);
        aplicaMaterial(PEWTER);
        glScalef(0.2f, 0.8f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawTableLeg() {
    aplicaMaterial(WOOD);
    glPushMatrix();
        glScalef(0.2f, 1.0f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawChairSeat(){
    aplicaMaterial(VELVET);
    glPushMatrix();
        glScalef(1.2f, 0.1f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();
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

void DrawChair() {
    glPushMatrix();
        glTranslatef( 0.5f, -0.5f,  0.5f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5f, -0.5f,  0.5f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef( 0.5f, -0.5f, -0.5f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5f, -0.5f, -0.5f);
        DrawTableLeg();
    glPopMatrix();

    // diagonais 
    glPushMatrix(); 
        glTranslatef(0.0f, -0.5f, -0.5f);
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(50, 0.0f, 0.0f, 1.0f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(0.0f, -0.5f, -0.5f); 
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(-50, 0.0f, 0.0f, 1.0f);
        DrawTableLeg();
    glPopMatrix();

    // Assento
    DrawChairSeat();

    // Encosto
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, -0.55f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        DrawChairSeat();
    glPopMatrix();

}

void DrawChairs(){
    glPushMatrix();
        glTranslatef(1.5f, -0.2f, -1.0f); 
        DrawChair();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5f, -0.2f, 2.0f);
        glRotatef(180, 0.0f, 1.0f, 0.0f); 
        DrawChair();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0f, -0.2f, -1.0f); 
        DrawChair();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5f, -0.2f, 2.0f); 
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        DrawChair();
    glPopMatrix();
}

void DrawGlasses(){
    glPushMatrix(); 
        glTranslatef(-2.9, 0.2f, 0.0f);
        glScalef(0.6f, 0.6f, 0.6f);
        glRotatef(180,1.0f, 0.0f, 0.0f);
        DrawGlass();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(-1.8, 0.2f, 0.4f);
        glScalef(0.6f, 0.6f, 0.6f);
        glRotatef(180,1.0f, 0.0f, 0.0f);
        DrawGlass();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(1.8, 0.2f, 0.0f);
        glScalef(0.6f, 0.6f, 0.6f);
        glRotatef(180,1.0f, 0.0f, 0.0f);
        DrawGlass();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(2.9, 0.2f, 0.4f);
        glScalef(0.6f, 0.6f, 0.6f);
        glRotatef(180,1.0f, 0.0f, 0.0f);
        DrawGlass();
    glPopMatrix();
}

void drawPlates(){
    glPushMatrix(); 
        glTranslatef(-2.4, 0.2f, -0.5f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(-2.4, 0.2f, 1.2f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(2.4, 0.2f, -0.5f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(2.4, 0.2f, 1.2f);
        DrawPlate();
    glPopMatrix();
}

void DrawPlacematSet(){
    glPushMatrix(); 
        glTranslatef(-1.8f, 0.0f, -0.8f); 
        glScalef(1.5f, 1.0f, 0.8f);
        drawTableMat();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(1.8f, 0.0f, -0.8f); 
        glScalef(1.5f, 1.0f, 0.8f);
        drawTableMat();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(-1.8f, 0.0f, 0.8f); 
        glScalef(1.5f, 1.0f, 0.8f);
        drawTableMat();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(1.8f, 0.0f, 0.8f); 
        glScalef(1.5f, 1.0f, 0.8f);
        drawTableMat();
    glPopMatrix();
}

void DrawPositionedLamp(){
    glPushMatrix();
        glTranslatef(0.0f, 0.4f, 0.0f);
        glScaled(0.5,0.8,0.5);
        DrawLighting();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Câmera
    gluLookAt(
        -1.0, 2.0, 4.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
    
    DrawTable();
    DrawPlacematSet();
    drawPlates();
    DrawGlasses();
    DrawPositionedLamp();
    DrawChairs();
    drawTableMat();

    glFlush();
}

void reshape(GLint w, GLint h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = GLfloat(w) / GLfloat(h);

    if (w <= h) {
        // width is smaller, stretch out height
        glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
    } else {
        // height is smaller, stretch out width
        glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
    }
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
