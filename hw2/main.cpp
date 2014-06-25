#include <iostream>
#include <stdlib.h>

#include "core.h"

using namespace std;

void* pool;
pnode freespace[5];

int  main()
{
    int poolsize;
    cout<<"input poolsize(%16=0)"<<endl;
    cin>>poolsize;
    
    
    pool=malloc(poolsize);
    init(pool,poolsize);
    
    void* temp[5];
    
    show();
    temp[0] =acquire(2);
    cout<<endl<<"address is "<<temp[0]<<endl;
    show();
    temp[1]=acquire(16);
    cout<<endl<<"address is "<<temp[1]<<endl;
    show();
    temp[2] =acquire(4) ;
    cout<<endl<<"address is "<<temp[2]<<endl;
    show();
    temp[3]=acquire(8) ;
    cout<<endl<<"address is "<<temp[3]<<endl;
    show();
    temp[4]=acquire(1) ;
    cout<<endl<<"address is "<<temp[4]<<endl;
    show();
    reclaim(temp[0]);
    show();
    reclaim(temp[1]);
    show();
    reclaim(temp[2]);
    show();
    reclaim(temp[3]);
    show();
    reclaim(temp[4]);
    show();
};
