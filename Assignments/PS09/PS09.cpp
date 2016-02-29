//
//  PS09.cpp
//  framework
//
//  Created by Chris Wang on 11/1/15.
//  Copyright © 2015 24780. All rights reserved.
//



#include <stdio.h>
#include "fssimplewindow.h"
#include <string.h>
#include <stdlib.h>


template <class T>
class BitmapTemplate
{
private:
    int wid,hei;
    T* pix;
public:
    BitmapTemplate();
    BitmapTemplate(const BitmapTemplate <T>&incoming);
    const BitmapTemplate &operator=(const BitmapTemplate <T> &incoming);
    ~BitmapTemplate();
    void CleanUp(void);
    void Create(int w,int h);
    int GetWidth(void) const;
    int GetHeight(void) const;
    void SetPixel(int x,int y,T p);
    T GetPixel(int x,int y);
};


template<class T>
const BitmapTemplate<T> &BitmapTemplate<T>::operator=(const BitmapTemplate<T> &incoming)
{
    if(&incoming!=this)
    {
        Create(incoming.wid, incoming.hei);
        for(int i=0; i<incoming.wid*incoming.hei; i++)
        {
            
            pix[i]=incoming.pix[i];
            
        }
    }
    
    return *this;
}


template <class T>
BitmapTemplate<T>::BitmapTemplate(const BitmapTemplate <T>&incoming)
{
    if(&incoming!=this)
    {
        Create(incoming.wid, incoming.hei);
        for(int i=0; i<incoming.wid*incoming.hei; i++)
        {
            pix[i]=incoming.pix[i];
        }
    }
}


class CharBitmap : public BitmapTemplate<char>
{
public:
    CharBitmap();
    ~CharBitmap();
    void Draw(void) ;
};

CharBitmap::CharBitmap()
{
    
}
CharBitmap::~CharBitmap()
{
    
}


template <class T>
BitmapTemplate<T>::BitmapTemplate()
{
    wid=0;
    hei=0;
    pix=nullptr;
}

template <class T>
BitmapTemplate<T>::~BitmapTemplate()
{
    CleanUp();
}

template <class T>
void BitmapTemplate<T>::CleanUp(void)
{
    wid=0;
    hei=0;
    if(nullptr!=pix)
    {
        delete [] pix;
    }
    pix=nullptr;
}

template <class T>
void BitmapTemplate<T>::Create(int w,int h)
{
    CleanUp();
    
    pix=new T [w*h];
    wid=w;
    hei=h;
    
    for(int i=0; i<wid*hei; ++i)
    {
        pix[i]=0;
    }
}

template <class T>
void BitmapTemplate<T>::SetPixel(int x,int y,T p)
{
    if(0<=x && x<wid && 0<=y && y<hei)
    {
        pix[y*wid+x]=p;
    }
}

template <class T>
T BitmapTemplate<T>::GetPixel(int x,int y)
{
    if(0<=x && x<wid && 0<=y && y<hei)
    {
        return pix[y*wid+x];
    }
    return 0;
}

template <class T>
int BitmapTemplate<T>::GetHeight() const
{
    return hei;
}

template <class T>
int BitmapTemplate<T>::GetWidth() const
{
    return wid;
}


void CharBitmap::Draw(void) 
{
    glBegin(GL_QUADS);
    int W=GetWidth();
    int H=GetHeight();
    
    for(int y=0; y<H; ++y)
    {
        for(int x=0; x<W; ++x)
        {
            auto pix=GetPixel(x,y);
            // If you use switch & case, that's ok, too.
            int b=255*(pix%2);
            int r=255*((pix/2)%2);
            int g=255*((pix/4)%2);
            
            glColor3ub(r,g,b);
            glVertex2i(x*20   ,y*20);
            glVertex2i(x*20+20,y*20);
            glVertex2i(x*20+20,y*20+20);
            glVertex2i(x*20   ,y*20+20);
        }
    }
    
    glEnd();
}

int main(void)
{
    
    printf("Enter Dimension>");
    
    char str[256];
    fgets(str,255,stdin);
    int wid=0,hei=0;
    {
        // Either cut & paste Parse function, or write parsing algorithm here.
        int state=0,n=0;
        for(int i=0; 0!=str[i]; ++i)
        {
            if(0==state)
            {
                if(' '!=str[i])
                {
                    if(0==n)
                    {
                        wid=atoi(str+i);
                    }
                    else if(1==n)
                    {
                        hei=atoi(str+i);
                    }
                    ++n;
                    state=1;
                }
            }
            else
            {
                if(' '==str[i])
                {
                    state=0;
                }
            }
        }
        if(2>n || 0>wid || 0>hei)
        {
            return 0;
        }
    }
    
    
    CharBitmap bmp;
    bmp.Create(wid,hei);
    CharBitmap undo(bmp);
    FsOpenWindow(0,0,wid*20,hei*20,1);
    
    for(;;)
    {
        FsPollDevice();
        auto key=FsInkey();
        
        int lb,mb,rb,mx,my;
        FsGetMouseEvent(lb,mb,rb,mx,my);
        
        if(FSKEY_ESC==key)
        {
            break;
        }
        if(FSKEY_0<=key && key<=FSKEY_7)
        {
            undo=bmp;
            int px=mx/20;
            int py=my/20;
            int colorCode=key-FSKEY_0;
            bmp.SetPixel(px,py,colorCode);   //why can int colorcode call the function setpixel which takes unsigned char?
            
        }
        if(FSKEY_U==key)
        {
            bmp=undo;
        }
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        bmp.Draw();
        FsSwapBuffers();
        
        FsSleep(25);
    }
}
