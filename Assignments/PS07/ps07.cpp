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



class CharBitmap
{
public:
    int wid,hei;
    char *pix;
    void cleanup();
    void create(int w,int h);
    void SetPixel(int x,int y,char p) const;
    char GetPixel(int x,int y);
    void Draw() const;
    CharBitmap();
    ~CharBitmap();
};

CharBitmap::CharBitmap()
{
    wid=0;
    hei=0;
    pix=nullptr;
}

CharBitmap::~CharBitmap()
{
    cleanup();
    wid=0;
    hei=0;
    pix=nullptr;
}



char CharBitmap::GetPixel(int x, int y)
{
    if (x>wid-1 || y>hei-1)
    {
        return '0';
    }
    else
    {
        return pix[y*wid+x];
    }
}

void CharBitmap::create(int w,int h)
{
    pix=new char[w*h];
    wid=w;
    hei=h;
    for (int i=0;i<w*h;i++)
    {
        pix[i]='0';
    }
    
}

void CharBitmap::SetPixel(int x,int y,char p) const
{
    
    if (x>0 && x<=wid-1 && y>0 && y<=hei-1)
    {
        pix[y*wid+x]=p;
    }
    
}


void CharBitmap::cleanup(void)
{
    if(pix!=nullptr)
    {
        delete [] pix;
    }
}


void CharBitmap::Draw() const
{
    for (int i=0;i<wid*hei;i++)
    {
        if (pix[i]=='0')
            glColor3ub(0, 0, 0);
        
        else if (pix[i]=='1')
            glColor3ub(0, 0, 255);
        
        else if (pix[i]=='2')
            glColor3ub(255, 0, 0);
        
        else if (pix[i]=='3')
            glColor3ub(255, 0, 255);
        
        else if (pix[i]=='4')
            glColor3ub(0,255, 0);
        
        else if (pix[i]=='5')
            glColor3ub(0, 255, 255);
        
        else if (pix[i]=='6')
            glColor3ub(255, 255, 0);
        
        else if (pix[i]=='7')
            glColor3ub(255, 255, 255);
        
        
        glBegin(GL_QUADS);
        glVertex2d(i%wid*20,i/wid*20);
        glVertex2d(i%wid*20+20, i/wid*20);
        glVertex2d(i%wid*20+20, i/wid*20+20);
        glVertex2d(i%wid*20, i/wid*20+20);
        glEnd();
        
    }
    
    
}


int main()
{
    
    bool term=false;
    printf("Enter Dimension>");
    CharBitmap bmp;
    
    int w,h;
    char str[256];
    fgets(str,255,stdin);
    
    
    int wordtop[10];
    int wordlength[10];
    if ( Parse(&wordtop[10], &wordlength[10], 10, str)==2)
    {
        w=atoi(&str[0]);
        h=atoi(&str[2]);
    }
    else if ( Parse(&wordtop[10],&wordlength[10], 10, str)!=2 || w==0 || h==0)
    {
        term=true;
    }
    bmp.create(w,h);
    
    
    
    FsOpenWindow(0, 0, w*20,h*20, 1);
    while(true!=term)
    {
        
        FsPollDevice();
        int lb,mb,rb,mx,my;
        FsGetMouseEvent(lb,mb,rb,mx,my);
        int x=mx/20;
        int y=my/20;
        
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        auto key=FsInkey();
        
        switch (key)
        {
            case FSKEY_ESC:
                term=true;
                break;
            case FSKEY_0:
                bmp.SetPixel(x,y,'0');
                
                break;
            case FSKEY_1:
                bmp.SetPixel(x,y,'1');
                break;
            case FSKEY_2:
                bmp.SetPixel(x,y,'2');
                break;
            case FSKEY_3:
                bmp.SetPixel(x,y,'3');
                break;
            case FSKEY_4:
                bmp.SetPixel(x,y,'4');
                break;
            case FSKEY_5:
                bmp.SetPixel(x,y,'5');
                break;
            case FSKEY_6:
                bmp.SetPixel(x,y,'6');
                break;
            case FSKEY_7:
                bmp.SetPixel(x,y,'7');
                break;
            case FSKEY_S:
                printf("Enter a file name:");
                char name[256];
                fgets(name, 255, stdin);
                
                if (name[strlen(name)-1]=='\n')
                {
                    name[strlen(name)-1]='\0';
                }
                strcat(name, ".txt");
                
                FILE *fp;
                fp = fopen(name,"w");
                
                fprintf(fp,"%d %d\n",w,h);
                for (int i=0; i<h; i++) {
                    for (int j=0; j<w; j++) {
                        fprintf(fp,"%c",bmp.pix[i*w+j]);
                    }
                    fprintf(fp,"\n");
                }
                fclose(fp);
                
                break;
                
            
                
                    
                
                
                
        }
        bmp.Draw();
        
        
        FsSwapBuffers();
        
        FsSleep(25);
    }
}