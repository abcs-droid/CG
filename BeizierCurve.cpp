#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

Point controlPoints[4]; // Cubic Bezier requires 4 points

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0); // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240); // Y-axis
    glEnd();
}

// Bezier curve using Bernstein polynomial form
void bezierCurve(Point p[], int numPoints = 1000) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numPoints; ++i) {
        float t = (float)i / numPoints;
        float x = pow(1 - t, 3) * p[0].x +
                  3 * t * pow(1 - t, 2) * p[1].x +
                  3 * pow(t, 2) * (1 - t) * p[2].x +
                  pow(t, 3) * p[3].x;

        float y = pow(1 - t, 3) * p[0].y +
                  3 * t * pow(1 - t, 2) * p[1].y +
                  3 * pow(t, 2) * (1 - t) * p[2].y +
                  pow(t, 3) * p[3].y;

        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0); // Black axes
    drawAxes();

    glColor3f(1, 0, 0); // Red control polygon
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 4; ++i)
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    glEnd();

    glColor3f(0, 0, 1); // Blue Bezier curve
    bezierCurve(controlPoints);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 0);               // White background
    gluOrtho2D(-320, 320, -240, 240);       // 2D view
}

int main(int argc, char** argv) {
    cout << "Enter 4 control points (x y) for the cubic Bezier curve:\n";
    for (int i = 0; i < 4; ++i) {
        cout << "Point " << i + 1 << ": ";
        cin >> controlPoints[i].x >> controlPoints[i].y;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
