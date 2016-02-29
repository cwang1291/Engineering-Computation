//
//  PS08.cpp
//  framework
//
//  Created by Chris Wang on 10/22/15.
//  Copyright © 2015 24780. All rights reserved.
//




#include <stdio.h>
#include "fssimplewindow.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int Parse(int wordTop[],int wordLength[],int maxNumWord,char str[])
{
    int state=0;  // 0:Blank   1:Visible Letter
    int nw=0;
    for(int i=0; 0!=str[i]; ++i)
    {
        switch(state)
        {
            case 0:
                if(' '!=str[i] && isprint(str[i]))
                {
                    if(nw<maxNumWord)
                    {
                        wordTop[nw]=i;
                        wordLength[nw]=1;
                    }
                    else
                    {
                        goto LOOPOUT;
                    }
                    ++nw;
                    state=1;
                }
                else
                {
                }
                break;
            case 1:
                if(' '!=str[i] && isprint(str[i]))
                {
                    wordLength[nw-1]++;
                }
                else
                {
                    state=0;
                }
                break;
        }
    }
LOOPOUT:
    
    return nw;
}





class Line2D
{
protected:
    int X1,X2,Y1,Y2,R,G,B;
    
public:
    void Draw(int movex,int movey) const;
    void MakeFromString(char str[256]) ;
    Line2D();
    ~Line2D();
};

void Line2D::Draw(int movex,int movey) const
{
    glColor3ub(R, G, B);
    glBegin(GL_LINES);
    glVertex2d(X1+movex, Y1+movey);
    glVertex2d(X2+movex, Y2+movey);
    glEnd();
}

void Line2D::MakeFromString(char str[256])
{
    int wordtop[7];
    int wordlength[7];
    Parse(wordtop,wordlength,7,str);
    
    X1+=atoi(str+wordtop[0]);
    Y1+=600-atoi(str+wordtop[1]);
    X2+=atoi(str+wordtop[2]);
    Y2+=600-atoi(str+wordtop[3]);
    R=atoi(str+wordtop[4]);
    G=atoi(str+wordtop[5]);
    B=atoi(str+wordtop[6]);
}

Line2D::Line2D()
{
    X1=0;
    X2=0;
    Y1=0;
    Y2=0;
    R=0;
    G=0;
    B=0;
}
Line2D::~Line2D()
{
    X1=NULL;
    X2=NULL;
    Y1=NULL;
    Y2=NULL;
    R=NULL;
    G=NULL;
    B=NULL;
}



class Drawing2D
{
protected:
    Line2D *line2D_ptr;
    int numoflines;
    
public:
    void Draw(int movex,int movey);
    char filename[256];
    Drawing2D();
    ~Drawing2D();
    void cleanup();
    void ReadFile(char filename[256]);
    Drawing2D(const Drawing2D &Source)
    {
        numoflines = Source.numoflines;
        line2D_ptr=Source.line2D_ptr;
    }
    Drawing2D& operator= (const Drawing2D &Source);
};

Drawing2D& Drawing2D::operator= (const Drawing2D &Source)
{
    numoflines = Source.numoflines;
    line2D_ptr=Source.line2D_ptr;
    return *this;
}


void Drawing2D::Draw(int movex,int movey)
{
    ReadFile(filename);
    for (int i=0;i<numoflines;i++)
    {
        line2D_ptr[i].Draw(movex,movey);
    }
}


Drawing2D::Drawing2D()
{
    numoflines=NULL;
}


Drawing2D::~Drawing2D()
{
    cleanup();
}

void Drawing2D::cleanup()
{
    if (line2D_ptr!=nullptr)
    {
        delete[] line2D_ptr;
    }
}

void Drawing2D::ReadFile(char filename[256])
{
    FILE *fp;
    fp= fopen(filename,"r");
    if (fp!=nullptr)
    {
        char str[256];
        numoflines=atoi(fgets(str, 255, fp));
        line2D_ptr = new Line2D[numoflines];

        for (int i=0 ; fgets(str, 255, fp)!=nullptr ; i++)
        {
            line2D_ptr[i].MakeFromString(str);
        }
    }
    fclose(fp);
}

int main()
{
    bool term=false;
    printf("Enter File Name>");
    char name[256];
    fgets(name,255,stdin);
    if (name[strlen(name)-1]=='\n')
    {
        name[strlen(name)-1]='\0';
    }
    
    Drawing2D Drawing;

    int startx=0;
    int starty=0;
    int movex=0;
    int movey=0;
    int xlast = 0;
    int ylast = 0;
    FsOpenWindow(0, 0, 800, 600, 1);
    while (true!=term)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        auto key=FsInkey();
        if (key==FSKEY_ESC)
        {
            term=true;
        }

        for( int i=0; i<=strlen(name);i++)
        {
            Drawing.filename[i]=name[i];
        }
        
        
        
        int lb,mb,rb,mx,my;
        
        int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
        
        
        
        if(FSMOUSEEVENT_LBUTTONDOWN==evt)
        {
            startx=mx;
            starty=my;
            xlast = movex;
            ylast = movey;
        }
        
        if (lb==1)
        {
            movex=xlast+mx-startx;
            movey=ylast+my-starty;
        }
        
        if (key==FSKEY_SPACE)
        {
            startx=0;
            starty=0;
            movex=0;
            movey=0;
            
        }
        
        
        Drawing.Draw(movex,movey);

        
        FsSwapBuffers();
        FsSleep(25);
    }
   
}