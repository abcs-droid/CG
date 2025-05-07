#include <GL/glut.h>
#include <iostream>
using namespace std;

// Global variables for user input
int x_start, y_start, x_end, y_end;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0);  // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240);  // Y-axis
    glEnd();
}

// Bresenham's Line Drawing for Solid Line
void BresenhamSolidLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;

    int sx = (x2 > x1) ? 1 : -1;
    int sy = (y2 > y1) ? 1 : -1;

    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x, y);  // Draw the current point

        if (x == x2 && y == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);  // Black for axes
    drawAxes();

    glColor3f(1, 0, 0);  // Red for line
    BresenhamSolidLine(x_start, y_start, x_end, y_end);  // Draw the solid line

    glFlush();  // Render the graphics
}

void init() {
    glClearColor(1, 1, 1, 0);  // White background
    gluOrtho2D(-320, 320, -240, 240);  // Coordinate system with center at (0, 0)
}

int main(int argc, char** argv) {
    // Take user input for line endpoints
    cout << "Enter x1 y1: ";
    cin >> x_start >> y_start;

    cout << "Enter x2 y2: ";
    cin >> x_end >> y_end;

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Solid Line with Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}