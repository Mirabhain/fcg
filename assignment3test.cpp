//FCG Assignment 3
//Background

#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#define M_PI 3.142f

float _angleY = 0.0f;
float _angleX = 0.0f;


void ground() {
    glColor3f(0.0f, 0.8f, 0.0f); //Bright green
    glBegin(GL_QUADS);
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glEnd();
}

void grass() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);

    for (float x = -15.0f; x <= 15.0f; x += 0.5f) {
        for (float z = -15.0f; z <= 15.0f; z += 1.0f) {
            glBegin(GL_LINES);
            glVertex3f(x, 0.0f, z);
            glVertex3f(x, 0.4f + (rand() % 100) / 250.0f, z);
            glEnd();
        }
    }
}

void fence() {
    glColor3f(0.6f, 0.3f, 0.1f); //Brown
    glLineWidth(3.5f);

    for (float x = -20.0f; x <= 20.0f; x += 0.5f) {
        glPushMatrix();
        glTranslatef(x, 1.0f, -18.0f);
        glScalef(0.1f, 2.0f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
}

void sky() {
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.6f, 1.0f); //Dark blue (top)
    glVertex2f(0.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);

    glColor3f(0.6f, 0.8f, 1.0f); //Light blue (bottom)
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
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


    glPushMatrix();
    glColor3f(0.4039216f, 0.592159f, 0.666667f);
    glTranslatef(0.25f, 0.1f, 0.3f);
    glutSolidSphere(0.4f, 32, 32);
    glPopMatrix();

}


float earRotX[4] = { -70.0f, -70.0f, -70.0f, -70.0f };  // sudut rotate depan–belakang
float earRotY[4] = { 25.0f,   0.0f,   0.0f,   -25.0f };  // sudut rotate kiri–kanan

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




void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    sky();

    gluLookAt(0.0f, 5.0f, 15.0f,    //Camera
        0.0f, 1.0f, 0.0f,     //Target
        0.0f, 1.0f, 0.0f);    //Up

    ground();
    grass();
    fence();

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

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.35, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(850, 650);
    glutCreateWindow("3D Nature Background");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
