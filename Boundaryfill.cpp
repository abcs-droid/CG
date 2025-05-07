#include <GL/glut.h>
#include <iostream>
using namespace std;

int seedX = 350, seedY = 150;
bool fillFromMouse = false;
bool fillFromKeyboard = false;

void init() {
    glClearColor(1, 1, 1, 0);  // White background
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

bool isSameColor(float* c1, float* c2) {
    return (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]);
}

void boundaryFill(int x, int y, float* fillColor, float* boundaryColor) {
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if (!isSameColor(current, boundaryColor) && !isSameColor(current, fillColor)) {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

void drawShape() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);  // Blue boundary
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();
}

void display() {
    drawShape();

    float fillColor[] = {1, 0, 0};      // Red fill
    float boundaryColor[] = {0, 0, 1};  // Blue boundary

    if (fillFromKeyboard) {
        boundaryFill(seedX, seedY, fillColor, boundaryColor);
        fillFromKeyboard = false;
    }

    if (fillFromMouse) {
        boundaryFill(seedX, seedY, fillColor, boundaryColor);
        fillFromMouse = false;
    }
}

// Keyboard interface
void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 'b' || key == 'B') {
        fillFromKeyboard = true;
        glutPostRedisplay();
    }
}

// Mouse interface
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        seedX = x;
        seedY = 480 - y; // Adjust for OpenGL origin
        fillFromMouse = true;
        glutPostRedisplay();
    }
}

// Right-click menu
void handleMenu(int option) {
    switch (option) {
        case 1: // Fill from fixed point
            fillFromKeyboard = true;
            glutPostRedisplay();
            break;
        case 2: // Clear screen
            fillFromKeyboard = false;
            fillFromMouse = false;
            drawShape();
            break;
    }
}

void createMenu() {
    glutCreateMenu(handleMenu);
    glutAddMenuEntry("Boundary Fill (Fixed Point)", 1);
    glutAddMenuEntry("Clear Screen", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Boundary Fill - Mouse + Keyboard + Menu");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    createMenu();
    glutMainLoop();
    return 0;
}
