//
//  PS12.cpp
//  framework
//
//  Created by Chris Wang on 11/22/15.
//  Copyright © 2015 24780. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <thread>

class CalPi
{
public:
    double *PIptr;
    double res;
    double x0,x1,y0,y1;
};

void calculatePI(CalPi *ptr)
{
    auto &PI = *ptr;    // why "&" and "*" ???
    int M = 0;
    const int N = PI.res*PI.res;
    for(int x=PI.x0; x<PI.x1; ++x)
    {
        for(int y=0; y<PI.res; ++y)
        {
            const double xx=(double)x/(double)PI.res;
            const double yy=(double)y/(double)PI.res;
            
            if(xx*xx+yy*yy<=1.0)
            {
                
                M++;
                
            }
        }
    }
    *ptr->PIptr += 2.0*2.0*(double)M/(double)N;
}



int main(void)
{
    const int res=40000;
    
    double PItotal=0.0;
    
    
    auto t0=time(nullptr);
    
    CalPi cal[4];
    for (int i=0;i<4;i++)
    {
        cal[i].PIptr=&PItotal;
        cal[i].res=res;
        cal[i].x0=res*i/4;
        cal[i].x1=res*(i+1)/4;
        cal[i].y0=res*i/4;
        cal[i].y1=res*(i+1)/4;
    }
    
    std::thread th0(calculatePI,&cal[0]);
    std::thread th1(calculatePI,&cal[1]);
    std::thread th2(calculatePI,&cal[2]);
    std::thread th3(calculatePI,&cal[3]);
    
    th0.join();
    th1.join();
    th2.join();
    th3.join();
    
    printf("Estimated PI=%lf\n",PItotal);
    printf("Time Elapsed=%d\n",(int)(time(nullptr)-t0));
    
    return 0;
}