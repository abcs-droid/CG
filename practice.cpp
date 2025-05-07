#include<GL/gult.h>
#include<iostream>
#include<cmath>
using namespace std;
int x_start,y_start,x_end,y_end;

void drawAxes(){
    glBegin(GL_LINES)
    glVertex2i(-320,0);glVertex2i(320,0);
    glVertex2i(0,-240);glVertex2i(0,240);
    glEnd;
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    drawAxes();
    
    glColor3f(1,0,0);
    DDA_Line(x_start,y_start,x_end,y_end);

    glFlush();
}
void init(){
    glClearColor(1,1,1,0);
    gluOrtho2D(-320,320,-240,240);
}
int main(int argc ,char** argv){
    cout << "Enter x1 y1 :";
    cin >>x_start>>y_start;
    cout << "Enter x2 y2 :";
    cin >>x_end>>y_end;

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
}