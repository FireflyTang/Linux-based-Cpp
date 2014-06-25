#include <stdio.h>
#include <stdlib.h>

#ifndef __fun__
#include "fun.h"
#endif

int main()
{ 
    int n;
    printf( "This program factorize a number.\n ");
    printf( "Input an integer which is not less than 2: ");
    n = GetIntegerFromKeyboard();
    Factorize( n );
    system( "pause" );
    return 0;
}


