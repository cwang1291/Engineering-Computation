#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "fssimplewindow.h"

void transform(double &x,double &y,double &L,double &h)
{
    x=200.0;
    y=300.0;
    L=L*100.0;
    h=h*100.0;
}

void drawwall(int x,int y)
{
    glColor3f(1.0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x,0);
    glVertex2i(x,2*y);
    for(int i=0;i<12;i++)
    {
        glVertex2i(x-50, 2*y-50*i);
        glVertex2i(x,2*y-50*(i+1));
    }
    glEnd();
}

void drawspring(double x,double y,double L,double h)
{
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex2d(x,y);
    glVertex2d(x+L/3.0,y);
    glVertex2d(x+L/3.0,y);
    glVertex2d(x+L/3.0+L/36.0,y+h/2);
    for(int i=0;i<5;i++)
    {
        glVertex2d(x+L/3.0+L/36.0+i*L/18.0,y+pow(-1,i)*h/2);
        glVertex2d(x+L/3.0+L/36.0+(i+1)*L/18.0,y+pow(-1,i+1)*h/2);
    }
    glVertex2d(x+L*2.0/3.0-L/36.0,y-h/2.0);
    glVertex2d(x+L*2.0/3.0,y);
    glVertex2d(x+L*2.0/3.0,y);
    glVertex2d(x+L,y);
    glEnd();
}

void drawbox(double x,double y,double L,double h)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2d(x+L,y-h/2.0);
    glVertex2d(x+L,y+h/2.0);
    glVertex2d(x+L+h,y+h/2.0);
    glVertex2d(x+L+h,y-h/2.0);
    glFlush();
    glEnd();

}
int main()
{
    double L,h;
    double x,y=0;
    printf("24-780 Engineering Computation Problem Set 2-2 – Mass-Spring System Enter L and h:");
    scanf("%lf %lf",&L,&h);
    FsOpenWindow(100,100,800,600,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    transform(x,y,L,h);
    drawwall(x,y);
    drawspring(x,y,L,h);
    drawbox(x,y,L,h);
    

    glEnd();
    glFlush();
    while(FSKEY_ESC!=FsInkey())
    {
        FsPollDevice();
        FsSleep(25);
    }
    
    return 0;
}