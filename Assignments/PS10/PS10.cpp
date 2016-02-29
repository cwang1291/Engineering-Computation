//
//  PS10.cpp
//  framework
//
//  Created by Chris Wang on 11/4/15.
//  Copyright © 2015 24780. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"



class TextString
{
private:
    char *str;
    
public:
    TextString();
    TextString(const TextString &incoming);
    TextString &operator=(const TextString &incoming);
    ~TextString();
    void CleanUp(void);
    int interpret(char input);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    
    void Add(char c);
    void DeleteLast(void);
    void Set(const char incoming[]);
    const char *GetPointer(void) const;
    int Strlen(void) const;
    int score[10];
    int state=0;
    
    void ScoreFromFrame(const int pinsKnocked[21]);
};
void TextString::ScoreFromFrame(const int pinsKnocked[21])
{
    
    score[9]=pinsKnocked[18]+pinsKnocked[19]+pinsKnocked[20];
    
    for (int i=0;i<18;i++)
    {
        score[i/2]=pinsKnocked[i-1]+pinsKnocked[i];
    }
    
    for(int i=0;i<10;i++)
    {
        if (score[i]==10 && pinsKnocked[2*i]!=10 && pinsKnocked[2*i+1]!=10)
        {
            score[i]+=pinsKnocked[2*i+2];

        }
        else if (score[i]==10 && pinsKnocked[2*i+2]==10)
        {
            score[i]+=pinsKnocked[2*i+2]+pinsKnocked[2*i+4];
        }
        else if (score[i]==10)
        {
            score[i]+=score[i+1];
        }
    }
}
TextString::TextString()
{
    str=nullptr;
}

TextString::TextString(const TextString &incoming)
{
    str=nullptr;
    Set(incoming.GetPointer());
}

TextString &TextString::operator=(const TextString &incoming)
{
    Set(incoming.GetPointer());
    return *this;
}

TextString::~TextString()
{
    CleanUp();
}

void TextString::CleanUp(void)
{
    if(nullptr!=str)
    {
        delete [] str;
        str=nullptr;
    }
}

int TextString::interpret(char input)
{
    if (input=='0')
        return 0;
    else if (input=='1')
        return 1;
    else if (input=='2')
        return 2;
    else if (input=='3')
        return 3;
    else if (input=='4')
        return 4;
    else if (input=='5')
        return 5;
    else if (input=='6')
        return 6;
    else if (input=='7')
        return 7;
    else if (input=='8')
        return 8;
    else if (input=='9')
        return 9;
    else if (input=='x')
        return 10;
    else if (input=='X')
        return 10;
    else if (input=='/')
        return -2;
    else if (input==' ')
        return 0;
    else if (input=='-')
        return 0;
    else
        return 100;
}

const char *TextString::Fgets(FILE *fp)
{
    bool readSomething=false;
    
    CleanUp();
    
    char buf[256];
    while(nullptr!=fgets(buf,255,fp))
    {
        readSomething=true;
        
        for(int i=0; 0!=buf[i]; ++i)
        {
            Add(buf[i]);
        }
        
        const auto L=strlen(buf);
        if(0==isprint(buf[L-1]))
        {
            break;
        }
    }
    
    DeleteLastControlCode();
    
    if(true==readSomething)
    {
        return str;
    }
    return nullptr;
}

void TextString::DeleteLastControlCode(void)
{
    int i;
    for(i=0; 0!=str[i]; ++i)
    {
    }
    for(i=i; 0<=i && 0==isprint(str[i]); --i)
    {
        str[i]=0;
    }
}

void TextString::Add(char c)
{
    if(nullptr==str)
    {
        const char newstr[2]={c,0};
        Set(newstr);
    }
    else
    {
        auto L=strlen(str);
        auto newStr=new char [L+2];
        strcpy(newStr,str);
        newStr[L]=c;
        newStr[L+1]=0;
        
        CleanUp();
        
        str=newStr;
    }
}

void TextString::DeleteLast(void)
{
    if(nullptr!=str)
    {
        auto L=strlen(str);
        if(0<L)
        {
            str[L-1]=0;
        }
    }
}

void TextString::Set(const char incoming[])
{
    if(incoming!=str)
    {
        CleanUp();
        
        auto L=strlen(incoming);
        str=new char [L+1];
        strcpy(str,incoming);
    }
}

const char *TextString::GetPointer(void) const
{
    if(nullptr!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

int TextString::Strlen(void) const
{
    return strlen(GetPointer());
}



void SomethingUseful(TextString &a,const TextString &b)
{
    a.Set(b.GetPointer());
}

int main()
{
    TextString txt;
    int userinput[21];
    txt.Fgets(stdin);
    if (txt.Strlen()<21)
    {
        printf("Too Short\n");
        txt.state=1;
    }
    
    for (int i=0;i<21;i++)
    {
        userinput[i]=txt.interpret(txt.GetPointer()[i]);
        if (txt.state==1)
        {
            break;
        }
        else if (userinput[i]==100)
        {
            printf("Wrong Character\n");
            txt.state=1;
            break;
        }
        else if (userinput[i]==-2)
        {
            userinput[i]=10-userinput[i-1];
        }
    }
    
    if (txt.state==0)
    {
        txt.ScoreFromFrame(userinput);
        int totalscore=0;
        for (int i=0;i<10;i++)
        {
            totalscore+=txt.score[i];
        }
        printf("%d\n",totalscore);
    }
    
    

    
    return 0;
}
