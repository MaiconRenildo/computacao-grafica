#include <GL/glut.h>

float w = 800;
float h = 600;

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

void DrawChair(){
    // pés da cadeira
    // frente - esquerda
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5); // Cor: cinza
        glTranslatef(-0.5f, -0.5f,  0.5f);
        DrawTableLeg();
    glPopMatrix();

    // trás - esquerda
    glPushMatrix();
        glColor3f(0.0, 0.8, 1.0); // Cor: azul
        glTranslatef(-0.5f, -0.5f, -0.5f);
        DrawTableLeg();
    glPopMatrix();  

    // frente - direita
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0); // Cor: verde
        glTranslatef(0.5f, -0.5f,  0.5f);
        DrawTableLeg();
    glPopMatrix();

    // frente - esquerda
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef( 0.5f, -0.5f, -0.5f);
        DrawTableLeg();
    glPopMatrix();

    // diagonais
    glPushMatrix(); 
        glColor3f(1.0, 0.8, 0.4);
        glTranslatef(0.0f, -0.5f, -0.5f);
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(50, 0.0f, 0.0f, 1.0f);
        DrawTableLeg();
    glPopMatrix();

    glPushMatrix(); 
        glColor3f(0.5, 0.8, 0.4);
        glTranslatef(0.0f, -0.5f, -0.5f); 
        glScalef(1.2f, 1.0f, 0.5f); 
        glRotatef(-50, 0.0f, 0.0f, 1.0f);
        DrawTableLeg();
    glPopMatrix();

    glColor3f(0.9, 0.8, 0.4);
    // Assento
    DrawChairSeat();

    // Encosto
    glPushMatrix();
        // glColor3f(0.5, 0.5, 0.5); // Cor: cinza
        glColor3f(0.0, 1.0, 0.0); // Cor: verde
        glTranslatef(0.0f, 0.5f, -0.55f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        DrawChairSeat();
    glPopMatrix();
}


void DrawChairs(){
    glPushMatrix();
        // glTranslatef(2.0f, -0.2f, -1.0f);
        DrawChair();
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glPushMatrix();
        // gluLookAt(5,0,0, 0,0,0, 0,1,0);

        gluLookAt(
            // -1.0, 2.0, 4.0,
            // 0,0.4,1, // cadeira de frente
            0,0.4,-1, // cadeira de frente
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(w/2, 0, w/2, h/2); // Posição (400, 0), tamanho (400, 300) 
        glEnable(GL_LIGHT2);
        // glutSolidTeapot(1);
        DrawChairs();
        glDisable(GL_LIGHT2);
    glPopMatrix();

    // de frente
    // canto superior direito
    glPushMatrix();
        gluLookAt(
            // -1.0, 2.0, 4.0,
            // 0,0.4,1, // cadeira de frente
            0,0.4,1, // cadeira de frente
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );

        glViewport(w/2, h/2, w/2, h/2);
        glEnable(GL_LIGHT1);
        // glutSolidTeapot(1);
        DrawChairs();
        glDisable(GL_LIGHT1);
    glPopMatrix();


    // de cima para baixo
    // Canto superior esquerdo
    glPushMatrix();

        gluLookAt(
            // -1.0, 2.0, 4.0,
            // 0,0.4,1, // cadeira de frente
            1,0.4,1, // cadeira de frente
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );
        glViewport(0,h/2, w/2, h/2); // Posição (0, 300), tamanho (400, 300)
        glEnable(GL_LIGHT2);
        DrawChairs();
        glDisable(GL_LIGHT2);
    glPopMatrix();


    glPushMatrix();
        gluLookAt(
            // -1.0, 2.0, 4.0,
            // 0,0.4,1, // cadeira de frente
            -1,0.4,1, // cadeira de frente
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0
        );
        glViewport(0, 0, w/2, h/2); // Posição (0, 0), tamanho (400, 300)
        glEnable(GL_LIGHT1);
        DrawChairs();
        glDisable(GL_LIGHT1);
    glPopMatrix();


    // // Câmera
    // gluLookAt(
    //     // -1.0, 2.0, 4.0,
    //     // 0,0.4,1, // cadeira de frente
    //     0,0.4,-1, // cadeira de frente
    //     0.0, 0.0, 0.0,
    //     0.0, 1.0, 0.0
    // );
    // DrawChairs();
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

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    // glEnable(GL_COLOR_MATERIAL); // habilita cores dos objetos

    glEnable(GL_DEPTH_TEST); // necessário para que os elementos sejam desenhados na profundidade correta
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
