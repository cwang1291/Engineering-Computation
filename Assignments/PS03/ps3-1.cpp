#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int sec;
    printf("24-780 Engineering Computation Problem Set 2-1 - Count-down Timer How many seconds?:");
    scanf("%d",&sec);
    auto T1=time(nullptr);
    auto T2=time(nullptr);
    for(int i=1; i<=sec;i++)
    {
        while((T2-T1)<=i)
        {
            T2=time(nullptr);
        }
        printf("%d seconds left\n",sec-i);
    }
    printf("Done.");
}