/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * Install Make, GCC, OpenGL and freeglut.                              *
 * To compile your program, run "make" in the          *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp, link   *
 * to your OpenGL libs, build and run the executable   *
 * as you normally would.                              *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    for (int i = 0; i < 8; i++) {
        glPushMatrix();

        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f);

        if (i % 2 == 0)
            glTranslatef(1.0f, 0.0f, 0.0f);
        else
            glTranslatef(0.75f, 0.0f, 0.0f);

        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

        glutSolidTeapot(0.10);

        glPopMatrix();
    }
}

void problem2() {
    for (int i = 0; i < 11; i++) {
        glPushMatrix();

        float size = 2.5f - i * 0.23f;

        glTranslatef(0.0f, i * 0.15f, 0.0f);
        glScalef(size, 0.15f, size);

        glutSolidCube(1.0);

        glPopMatrix();
    }
}

void problem3() {
    for (int i = 0; i < 6; i++) {
        int count = 6 - i;

        for (int j = 0; j < count; j++) {
            glPushMatrix();

            float x = (j - (count - 1) / 2.0f) * 0.37f;
            float y = 0.85f - i * 0.3f;

            glTranslatef(x, y, 0.0f);

            glutSolidTeapot(0.12);

            glPopMatrix();
        }
    }
}

void problem4() {
    glPushMatrix();

    // Move the entire scene slightly upward
    glTranslatef(0.0f, 0.2f, 0.0f);

    // Heart
    glPushMatrix();

    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(0.7f, 0.7f, 0.7f);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f, 0.0f, 1.0f);

    glVertex3f(0.0f, 0.2f, 0.0f);

    glVertex3f(0.0f, 0.7f, 0.0f);
    glVertex3f(-0.3f, 0.9f, 0.0f);
    glVertex3f(-0.7f, 0.8f, 0.0f);
    glVertex3f(-0.9f, 0.4f, 0.0f);
    glVertex3f(-0.8f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.9f, 0.0f);
    glVertex3f(0.8f, 0.0f, 0.0f);
    glVertex3f(0.9f, 0.4f, 0.0f);
    glVertex3f(0.7f, 0.8f, 0.0f);
    glVertex3f(0.3f, 0.9f, 0.0f);
    glVertex3f(0.0f, 0.7f, 0.0f);

    glEnd();

    glPopMatrix();

    // Support connecting heart to pedestal
    glPushMatrix();

    glTranslatef(0.0f, -0.35f, 0.0f);
    glScalef(0.08f, 0.5f, 0.08f);

    glutSolidCube(1.0);

    glPopMatrix();

    // Pedestal
    glPushMatrix();

    glTranslatef(0.0f, -0.7f, 0.0f);
    glScalef(1.2f, 0.2f, 0.5f);

    glutSolidCube(1.0);

    glPopMatrix();

    glPopMatrix();
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown) {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}