#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x_start, y_start, x_end, y_end;

// Function to draw coordinate axes
void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0);  // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240);  // Y-axis
    glEnd();
}

// Function to draw a staircase line using DDA logic
void DDA_Staircase(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    float xInc = (dx > 0 ? 10 : -10); 
    float yInc = (dy > 0 ? 10 : -10);

    float x = x1, y = y1;

    glBegin(GL_LINES);
    for (int i = 0; i < steps/10; i++) {
        int x_prev = round(x);
        int y_prev = round(y);
        x += xInc;
        y += yInc;

        // Create a staircase pattern: first horizontal, then vertical
        glVertex2i(x_prev, y_prev);
        glVertex2i(round(x), y_prev); // horizontal segment

        glVertex2i(round(x), y_prev);
        glVertex2i(round(x), round(y)); // vertical segment
    }
    glEnd();
}

// OpenGL display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0); // Black color for axes
    drawAxes();

    glColor3f(0, 0, 1); // Blue color for staircase line
    DDA_Staircase(x_start, y_start, x_end, y_end);

    glFlush();
}

// OpenGL initialization
void init() {
    glClearColor(1, 1, 1, 0); // White background
    gluOrtho2D(-320, 320, -240, 240); // Set coordinate system with center at (0,0)
}

// Main function
int main(int argc, char** argv) {
    cout << "Enter x1 y1: ";
    cin >> x_start >> y_start;
    cout << "Enter x2 y2: ";
    cin >> x_end >> y_end;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Staircase Line with Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}