#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#define M_PI 3.142f

// Global variables for animation / rotation
float _angleY = 0.0f;
float _angleX = 0.0f;

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glClearColor(0.9f, 0.9f, 0.95f, 1.0f);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawHead() {
    // ─── FOREHEAD “ELLIPSOID” LAYER ──────────────────────────────────────────
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.0f, -0.15f, 0.75f);
    glScalef(0.2f, 0.2f, 0.2f);
    glutSolidDodecahedron();
    glPopMatrix();

    //add main head
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.0f, -0.1f, 0.3f);
    glutSolidSphere(0.6f, 32, 32);
    glPopMatrix();

   //add head
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.0f, -0.1f, 0.3f);
    glScalef(0.2f, 0.2f, 0.2f);
    glutSolidSphere(0.6f, 32, 32);
    glPopMatrix();

   //add(nose)
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    // Position the base of the cone just in front of the sphere’s surface:
    
    glTranslatef(0.0f, -0.3f, 0.65f);
    glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
    // glutSolidCone(baseRadius, height, slices, stacks)
   
    glutSolidCone(0.5f, 0.50f, 10, 10);
    glPopMatrix();

    //draw cheek<tak siap lagi>

    //left cheek
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(-0.25f, 0.1f, 0.3f);
    glutSolidSphere(0.4f, 32, 32);
    glPopMatrix();



    //right cheek
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.25f, 0.1f, 0.3f);
    glutSolidSphere(0.4f, 32, 32);
    glPopMatrix();

}

//control ear nak rotate kiri kanan, depan belakang
float earRotX[4] = { -70.0f, -70.0f, -70.0f, -70.0f };  // sudut rotate depan–belakang
float earRotY[4] = { 25.0f,   0.0f,   0.0f,   -25.0f };  // sudut rotate kiri–kanan


//add kedudukan ear
void drawEarAppendage() {
    const float xOffsets[4] = { -0.5f,  -0.2f,  0.4f,  0.6f };//control kedudukan
    const float HEAD_Y = 0.0f;
    const float HEAD_Z = -0.10f;
    const float SCALE_X1 = 0.10f;
    const float SCALE_Y1 = 0.10f;
    const float SCALE_Z1 = 0.50f;

    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        // 1) Pindah ke posisi dasar ear
        glTranslatef(xOffsets[i], HEAD_Y, HEAD_Z);

        // 2) Rotate depan–belakang (paksi X) ikut earRotX[i]
        glRotatef(earRotX[i], 1.0f, 0.0f, 0.0f);

        // 3) Rotate kiri–kanan (paksi Y) ikut earRotY[i]
        glRotatef(earRotY[i], 0.0f, 1.0f, 0.0f);

        // 4) Scale jadi ellipsoid
        glScalef(SCALE_X1, SCALE_Y1, SCALE_Z1);

        // 5) Gambar sphere (ear)
        glColor3f(0.388235f, 0.3921569f, 0.4f);
        glutSolidSphere(1.0f, 20, 20);
        glPopMatrix();
    }
}

//add func body<tak siap spikes and body>
void drawBody() {
   //draw neck
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.0f, -0.8f, 0.2f);      // move neck down
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);   // align +Z→+Y
    gluCylinder(q, 0.20f, 0.20f, 0.40f, 20, 1);
    glPopMatrix();
    gluDeleteQuadric(q);

    // ─── 2) DRAW SPIKES AROUND THE TOP OF THE NECK ────────────────────────────
    const int   NUM_SPIKES = 6;
    const float NECK_TOP_Y = -0.8f;   // (−0.65 + 0.40)
    const float NECK_RADIUS = 0.20f;
    const float CONE_BASE = 0.05f;
    const float CONE_HEIGHT = 0.20f;

    for (int i = 0; i < NUM_SPIKES; ++i) {
        float angleDeg = (370.0f / NUM_SPIKES) * i;
        glPushMatrix();
        glTranslatef(0.0f, NECK_TOP_Y, 0.2f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(angleDeg, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, NECK_RADIUS);
        glColor3f(0.40303922f, 0.592157f, 0.555557f);
        // glutSolidCone(baseRadius, height, slices, stacks)
        glutSolidCone(CONE_BASE, CONE_HEIGHT, 20, 20);
        glPopMatrix();
    }

    // ─── 3) DRAW MAIN BODY (A SCALED CUBE) ────────────────────────────────────
    glPushMatrix();
    glTranslatef(0.0f, -1.2f, 0.0f);
    glScalef(0.5f, 0.8f, 0.3f);
    glColor3f(0.40303922f, 0.592157f, 0.555557f);
    glutSolidCube(0.8f);
    glPopMatrix();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    gluLookAt(0.0, 0.0, 10.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(_angleY, 0.0f, 1.0f, 0.0f);

    drawBody();//add
    drawHead();//add
    drawEarAppendage();//add

    glutSwapBuffers();
}

void handleSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  _angleY -= 2.0f; break;
    case GLUT_KEY_RIGHT: _angleY += 2.0f; break;
    case GLUT_KEY_UP:    _angleX -= 2.0f; break;
    case GLUT_KEY_DOWN:  _angleX += 2.0f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simplified Lucario with Spikes");

    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutSpecialFunc(handleSpecialKeys);
    glutMainLoop();
    return 0;
}
