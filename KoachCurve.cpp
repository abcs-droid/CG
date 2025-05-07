#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Global user inputs
int x_start, y_start, x_end, y_end, depth;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0); // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240); // Y-axis
    glEnd();
}

void kochCurve(float x1, float y1, float x2, float y2, int d) {
    if (d == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float xA = x1 + dx;
    float yA = y1 + dy;

    float xB = x1 + 2 * dx;
    float yB = y1 + 2 * dy;

    // Coordinates of peak of the triangle
    //float midX = (x1 + x2) / 2.0;
    // float midY = (y1 + y2) / 2.0;

    float px = xA + (dx * cos(M_PI / 3) - dy * sin(M_PI / 3));
    float py = yA + (dx * sin(M_PI / 3) + dy * cos(M_PI / 3));

    kochCurve(x1, y1, xA, yA, d - 1);
    kochCurve(xA, yA, px, py, d - 1);
    kochCurve(px, py, xB, yB, d - 1);
    kochCurve(xB, yB, x2, y2, d - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0); // Black Axes
    drawAxes();

    glColor3f(0, 0, 1); // Blue Koch curve
    glBegin(GL_LINES);
    kochCurve(x_start, y_start, x_end, y_end, depth);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 0);               // White background
    gluOrtho2D(-320, 320, -240, 240);       // 2D centered at (0, 0)
}

int main(int argc, char** argv) {
    // Get user input
    cout << "Enter x1 y1: ";
    cin >> x_start >> y_start;
    cout << "Enter x2 y2: ";
    cin >> x_end >> y_end;
    cout << "Enter recursion depth (0-5): ";
    cin >> depth;

    // OpenGL window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Koch Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}