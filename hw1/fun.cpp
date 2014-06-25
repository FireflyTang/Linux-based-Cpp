#include <stdio.h>
#include <math.h>

#ifndef __fun__
#include "fun.h"
#endif

static void Recursion(int n,int initn);

int GetIntegerFromKeyboard()
{
    int i;
    scanf("%d",&i);
    return i;
}

void Factorize(int initn)
{
    printf("%d=",initn);
    Recursion(initn,initn);
}

void Recursion(int n,int initn)
{
    int i=2;
    if (!(n%2==0))
    {
        i=3;    
    }
    for(;i<((int)sqrt(n))+1;i+=2)
    {
        if(n%i==0)
        {
            printf("%d*",i);
            Recursion(n/i,initn);
            return;
        }
    }
    printf("%d\n",n);
    if(n==initn)
    {
        printf("%d is a prime number.\n",initn);
    }
}
