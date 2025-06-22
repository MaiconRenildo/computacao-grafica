// Mesa sem iluminação

#include <GL/glut.h>

void drawTableMat(){
    glPushMatrix();
        glScalef(1.2f, 0.01f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawGlass() {
    GLUquadric* quad = gluNewQuadric();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // azulada e translúcida
    glColor4f(0.8f, 0.9f, 1.0f, 0.3f); 

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

    // cinza fosco
    glColor3f(0.6f, 0.6f, 0.6f);

    // Base
    glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f); // Levemente abaixo
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluDisk(quad, 0.0f, 0.08f, 64, 1); // Centro do prato
    glPopMatrix();

    // Parte interna arredondada (como funil raso)
    for (float i = 0; i < 10; i++) {
        float r1 = 0.08f + i * 0.012f;
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
        glScalef(0.2f, 0.8f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawTableLeg() {
    glPushMatrix();
        glScalef(0.2f, 1.0f, 0.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawChairSeat(){
    glPushMatrix();
        glScalef(1.2f, 0.1f, 1.2f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void DrawTable(){
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
        glTranslatef(2.0f, -0.2f, -1.0f); 
        DrawChair();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.0f, -0.2f, 2.0f);
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
        glTranslatef(-2.4, 0.1f, -0.5f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(-2.4, 0.1f, 1.2f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(2.4, 0.1f, -0.5f);
        DrawPlate();
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(2.4, 0.1f, 1.2f);
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