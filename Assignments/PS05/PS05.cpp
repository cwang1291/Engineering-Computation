#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"fssimplewindow.h"
const double pi = 3.1416;

bool CheckCollision(double branchX,double branchY,double ballX,double ballY)
{
    
    if(ballX>=branchX && ballX<branchX+15 && ballY < branchY-15 && ballY > branchY-30-15)
    {
        return true;
    }
    return false;
}

void drawbranch(double xi,double yi, double li)
{
    glColor3ub(150, 100, 50);
    glBegin(GL_LINES);
    glVertex2i(xi, yi-15);
    glVertex2i(xi, yi-li-15);
    glEnd();
    
}

void moveapple (double &x,double &y,double &vx,double &vy,double m,double dt)
{
    x+=vx*dt;
    y-=vy*dt;
    
    
    double Fx=0.0;
    double Fy=98*m;
    
    double ax=Fx/m;
    double ay=Fy/m;
    
    vx+=ax*dt;
    vy-=ay*dt;
}


void MoveBall(double &x,double &y,double &vx,double &vy,double m,double dt)
{
    x+=vx*dt;
    y-=vy*dt;
    
    
    double Fx=0.0;
    double Fy=98*m;
    
    double ax=Fx/m;
    double ay=Fy/m;
    
    vx+=ax*dt;
    vy-=ay*dt;
}


void DrawBall(double xi,double yi,double ri)
{
 
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=pi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        glVertex2d(xi+c*ri,yi+s*ri);
    }
    glEnd();
}

void drawcannon(double xi,double yi,double angle,double li)
{

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(xi, yi);
    glVertex2i(xi+li*cos(angle*pi/180),yi-li*sin(angle*pi/180));
    glEnd();
}

void drawweapon(double xi,double yi,double ri)
{

    
    glBegin(GL_LINE_LOOP);
    
    for(int a=0; a<64; ++a)
    {
        const double radian=pi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        glVertex2d(xi+c*ri,yi+s*ri);
    }
    glEnd();
}


void drawapple(int xi,int yi,int ri)
{
    glColor3ub(255, 0, 0);
    double x=(double)xi;
    double y=(double)yi;
    double r=(double)ri;
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=pi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        glVertex2d(x+c*r,y+s*r);
    }
    glEnd();
}

void drawtreetrunk(double xi,double yi,double wi, double hi)
{
    double x=xi;
    double y=yi;
    double w=wi;
    double h=hi;
    glShadeModel(GL_SMOOTH);
    
    glBegin(GL_QUADS);
    glColor3ub(150, 100,50);


    glVertex2i(x, y);
    glColor3ub(150, 50,50);

    glVertex2i(x, y-h);
    glVertex2i(x+w, y-h);
    glVertex2i(x+w, y);
    glEnd();
}

void drawtree(double xi,double yi,double wi, double hi)
{
    double w=wi;
    double h=hi;
    double x=(double(xi));
    double y=(double(yi));
    for (int i=0;i<6;i++)
    {
        glShadeModel(GL_SMOOTH);

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 255, 0);
        glVertex2i(x-w/2, y);
        glColor3ub(0, 100, 0);

        glVertex2i(x+w/2,y);
        glColor3ub(0, 50, 0);

        glVertex2i(x,y-h);
        y-=50;
    }
    

    glEnd();
}




int main()
{
    srand((int)time(NULL));
    FsOpenWindow(0,0,800,600,1);
    
    int ballstate = 0;
    bool term = false;
    double angle = 45;
    double ballVX = 400*cos(angle*pi/180);
    double ballVY = 400*sin(angle*pi/180);
    double ballX = 150*cos(angle*pi/180);
    double ballY = 600-150*sin(angle*pi/180);
    double weaponX = 0;
    double weaponY = 600;
    double appleX[5]={670,640,730,700,600};
    double appleY[5]={250,250,180,150,120};
    double applestate[5]={0,0,0,0,0};
    double dt=0.025;
    double appleVX[5]={0,0,0,0,0};
    double appleVY[5]={0,0,0,0,0};
    
    
    
    
    
    
    while (true != term)
    {
        FsPollDevice();
        auto key = FsInkey();
        switch (key)
        {
            case FSKEY_LEFT:
                angle += 1;
                if(ballstate == 0)
                {
                    ballX = 150*cos(angle*pi/180);
                    ballY = 600-150*sin(angle*pi/180);
                    ballVX = 400*cos(angle*pi/180);
                    ballVY = 400*sin(angle*pi/180);
                }
                break;
            case FSKEY_RIGHT:
                angle-=1;
                if(ballstate==0)
                {
                    ballX = 150*cos(angle*pi/180);
                    ballY = 600-150*sin(angle*pi/180);
                    ballVX = 400*cos(angle*pi/180);
                    ballVY = 400*sin(angle*pi/180);
                }
                break;
            
            case FSKEY_ESC:
                term=true;
                break;
            case FSKEY_SPACE:
                ballstate=1;
                break;
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawtree(650,400,300,150);
        drawtreetrunk(600,600,100,200);
        drawweapon(weaponX,weaponY,100);
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,0xff00);

        drawcannon(0,600,angle,150);
        glDisable(GL_LINE_STIPPLE);



        
        for (int i=0;i<5;i++)
        {
            if (applestate[i]==0)
            {
                drawapple(appleX[i],appleY[i],15);
                drawbranch(appleX[i],appleY[i],30);
                if (ballstate==1 && true==CheckCollision(appleX[i], appleY[i], ballX, ballY))
                {
                    applestate[i]=1;
                }
            
            }
            if ( applestate[i]==1)
            {
                moveapple(appleX[i],appleY[i],appleVX[i],appleVY[i],1,0.025);
                drawapple(appleX[i],appleY[i],15);
            }
            
            
        }
        
        
        if ( ballstate==1)
        {
            MoveBall(ballX,ballY,ballVX,ballVY,1,dt);
            DrawBall(ballX,ballY,3);
        }
        if (ballX>800 || ballX<0 || ballY>600 || ballY<0)
        {
            ballstate =0;
            ballVX = 400*cos(angle*pi/180);
            ballVY = 400*sin(angle*pi/180);
            ballX = 150*cos(angle*pi/180);
            ballY = 600-150*sin(angle*pi/180);
        }
        
        

       
        
        
        
        FsSwapBuffers();
        
        FsSleep(25);
    }
    
    
    
    
    
    
    
    
    
    
    
    
}