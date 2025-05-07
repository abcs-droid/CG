#include <GL/glut.h>
#include <iostream>
using namespace std;

int seedX = 350, seedY = 150;
bool fillFromMouse = false;
bool fillFromKeyboard = false;

void init() {
    glClearColor(1, 1, 1, 0);     // White background
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);   // Set origin bottom-left
}

bool isSameColor(float* c1, float* c2) {
    return (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]);
}

// 4-connected flood fill
void floodFill(int x, int y, float* oldColor, float* newColor) {
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if (isSameColor(current, oldColor) && !isSameColor(current, newColor)) {
        glColor3fv(newColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void drawShape() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);  // Blue outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();
}

void display() {
    drawShape();

    float newColor[] = {1, 0, 0};  // Red

    if (fillFromKeyboard) {
        float oldColor[3];
        glReadPixels(seedX, seedY, 1, 1, GL_RGB, GL_FLOAT, oldColor);
        floodFill(seedX, seedY, oldColor, newColor);
        fillFromKeyboard = false;
    }

    if (fillFromMouse) {
        float oldColor[3];
        glReadPixels(seedX, seedY, 1, 1, GL_RGB, GL_FLOAT, oldColor);
        floodFill(seedX, seedY, oldColor, newColor);
        fillFromMouse = false;
    }
}

// Keyboard: press 'f' to flood fill from fixed point
void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 'f' || key == 'F') {
        fillFromKeyboard = true;
        glutPostRedisplay();
    }
}

// Mouse: left click to flood fill from that point
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        seedX = x;
        seedY = 480 - y; // Invert Y (OpenGL origin at bottom-left)
        fillFromMouse = true;
        glutPostRedisplay();
    }
}

// Menu: Flood Fill or Clear Screen
void handleMenu(int option) {
    switch (option) {
        case 1: // Trigger fill from fixed point
            fillFromKeyboard = true;
            glutPostRedisplay();
            break;
        case 2: // Clear
            fillFromKeyboard = false;
            fillFromMouse = false;
            drawShape();
            break;
    }
}

void createMenu() {
    glutCreateMenu(handleMenu);
    glutAddMenuEntry("Flood Fill (Fixed Point)", 1);
    glutAddMenuEntry("Clear Screen", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill - Mouse + Keyboard + Menu");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    createMenu();
    glutMainLoop();
    return 0;
}
