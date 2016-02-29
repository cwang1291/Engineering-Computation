//
//  PS11.cpp
//  framework
//
//  Created by Chris Wang on 11/16/15.
//  Copyright © 2015 24780. All rights reserved.
//

#include <stdio.h>

template <const int NR, const int NC>
class MatrixTemplate
{
protected:
    double array[NR*NC];
public:
    void Set(int row,int col, double value);
    double Value(int row, int col) const;
    void Print(void) const;
    void swap(int row,int col);
};

template <const int NR,const int NC>
void MatrixTemplate<NR,NC>:: swap(int row,int col)
{
    double c;
    c=array[row*4+col];
    array[row*4+col]=array[col*4+row];
    array[col*4+row]=c;
}

template <const int NR,const int NC>
void MatrixTemplate <NR,NC> ::Set(int row, int col, double value)
{
    array[(row-1)*4+(col-1)]=value;
}

template <const int NR, const int NC>
double MatrixTemplate <NR,NC> ::Value(int row, int col) const
{
    return array[(row-1)*4+(col-1)];
}

template <const int NR, const int NC>
void MatrixTemplate <NR,NC> ::Print(void) const
{
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
        {
            printf("%0.2f  ",Value(i,j));
        }
        printf("\n");
    }
}


class Matrix4x4 : public MatrixTemplate <4,4>
{
public:
    void Transpose(void);
};

void Matrix4x4::Transpose(void)
{
    for (int i=1;i<=4;i++)
    {
        for (int j=1;j<=4;j++)
        {
            if (j>i)
            {
                swap(i-1,j-1);
            }
        }
    }
}

int main(void)
{
    Matrix4x4 mat;
    const double v[]=
    {
        6.0,1.0,4.0,9.0,
        9.0,8.0,6.0,1.0,
        7.0,2.0,9.0,4.0,
        1.0,7.0,5.0,9.0
    };
    for(int i=0; i<16; ++i)
    {
        const int r=1+i/4;
        const int c=1+i%4;
        mat.Set(r,c,v[i]);
    }
    mat.Print();
    mat.Transpose();
    printf("\n");
    mat.Print();
    // If you go for extra credit, uncomment the following three lines.
    // printf("\n");
    // mat.Invert();
    // mat.Print();
    return 0;
}