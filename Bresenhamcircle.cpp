#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Global variable for user input
int xc, yc, radius;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0);  // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240);  // Y-axis
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void BresenhamCircle(int xc, int yc, int radius) {
    int x = 0, y = radius;
    int p = 3 - 2 * radius;

    glBegin(GL_POINTS);
    while (x <= y) {
        // Draw the 8 symmetric points
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        x++;

        // Update the error term
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            y--;
            p = p + 4 * (x - y) + 10;
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);  // Black for axes
    drawAxes();

    glColor3f(1, 0, 0);  // Red for circle
    BresenhamCircle(xc, yc, radius);  // Draw the circle

    glFlush();  // Render the graphics
}

void init() {
    glClearColor(1, 1, 1, 0);  // White background
    gluOrtho2D(-320, 320, -240, 240);  // Coordinate system with center at (0, 0)
}

int main(int argc, char** argv) {
    // Take user input for the circle's center and radius
    cout << "Enter center (xc, yc): ";
    cin >> xc >> yc;
    cout << "Enter radius: ";
    cin >> radius;

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Circle with Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}