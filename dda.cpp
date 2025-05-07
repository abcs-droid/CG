#include <GL/glut.h>
#include <iostream>
using namespace std;

// Global variables to store user input
int x_start, y_start, x_end, y_end;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0);  // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240);  // Y-axis
    glEnd();
}

void DDA_Line(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1, dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));      // Ensure enough steps for any slope
    float xInc = dx / steps, yInc = dy / steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i((int)x, (int)y);  // Draw point (cast to int)
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);      // Black color for axes
    drawAxes();

    glColor3f(1, 0, 0);      // Red color for user-defined line
    DDA_Line(x_start, y_start, x_end, y_end);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 0);                  // White background
    gluOrtho2D(-320, 320, -240, 240);          // 2D projection with center at (0,0)
}

int main(int argc, char** argv) {
    // Take user input
    cout << "Enter x1 y1: ";
    cin >> x_start >> y_start;

    cout << "Enter x2 y2: ";
    cin >> x_end >> y_end;

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line with User Input");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}