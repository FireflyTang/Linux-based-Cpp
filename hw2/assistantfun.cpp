#include <iostream>
#include <stdlib.h>
#include  <cmath>

#include "assistantfun.h"

int power(int n)
{
    return pow(2,n); 
};

long getrelativeaddress(void* a,void* b)
{
    long c=abs((int)((char*)a-(char*)b));
    return c;
};


