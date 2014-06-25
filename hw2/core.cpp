#include "core.h"

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <map>

#include "DLlist.h"
#include "assistantfun.h"


using namespace std;

void* splitspace(int req,int space);
void* combine(int indexnumber,void* address);
void* search(int target);
void* drop(void* address,int size);


extern void* pool;
extern pnode freespace[5];

map<void*,int> usage;
map<void*,int>::iterator l_it;

class Efull{};

void* splitspace(int req,int space)
{
    void* head=getaddress(log2(space));
    deletenode(log2(space),head);
    while(space!=req)
    {
        space/=2;
        insertnode(log2(space),(char*)head+space);
    };
    return head;
    
};


void* combine(int indexnumber,void* address)
{
    void* previousaddress;
    void* nextaddress;
    if ((previousaddress=getpreviousaddress(indexnumber,address))
        &&(getrelativeaddress(previousaddress,address)==power(indexnumber))
        &&(getrelativeaddress(previousaddress,pool)%power(indexnumber+1)==0))
    {
        deletenode(indexnumber,previousaddress);
        deletenode(indexnumber,address);
        insertnode(indexnumber+1,previousaddress);
        return previousaddress;
    };
    if ((nextaddress=getnextaddress(indexnumber,address))
        &&(getrelativeaddress(nextaddress,address)==power(indexnumber))
        &&(getrelativeaddress(address,pool)%power(indexnumber+1)==0))
    {
        deletenode(indexnumber,nextaddress);
        deletenode(indexnumber,address);
        insertnode(indexnumber+1,address);
        return address;
    };
    return 0;    
};

void* search(int target)
{
    int i;
    void* address0;
    target=log2(target);
    if(!_isempty(target))
    {
        address0=getaddress(target);
        deletenode(target,address0);
        usage[address0]=power(target);
        return address0;
    };
    for(i=target+1;i<5;i++)
    {
        if(!_isempty(i))
        {
            address0=splitspace(power(target),power(i));
            usage[address0]=power(target);
            return address0;
        };
    };
    throw Efull();
};

void* drop(void* address,int size)
{
    int i;
    l_it=usage.find(address);
    usage.erase(l_it);
    void* address0=address;
    insertnode(i=log2(size),address);
    for(;i<4;i++)
    {
        address=combine(i,address);
        if(address)
        {
            address0=address;

        }
        else
        {

            return address0;
        };
    };
    return address0;
};

void* acquire(int size)
{
    void* temp;
    
    try
    {
        temp=search(size);
        return temp;
    }
    catch(Efull)
    {
        cout<<"Pool full\nPorgramme exited."<<endl;
        exit(3);
        return 0;
    }
};

void* reclaim(void* address)
{
    int m=(int)usage[address];
    return drop(address,m);
};

void show()
{
    int i;
    pnode p;
    cout<<endl<<"---------------------begin of table-----------------"<<endl;
    for(i=4;i>=0;i--)
    {
        cout<<"head address of free block with size "<<power(i)<<endl;
        p=freespace[i]->next;
        while(p->address!=0)
        {
            cout<<getrelativeaddress(p->address,pool)<<"   ";
            p=p->next;
        };
        cout<<endl;
    };
    cout<<"---------------------end of table-----------------"<<endl;
};
 
/*
 void* operator new[] (std::size_t size)throw(std::bad_alloc)
{
    void* a;
    try
    {
    a=acquire(size);
    return a;
    }
    catch(Efull)
    {
        cout<<"pool is full";
    };
};
void operator delete[]( void* ptr )throw()
{
    reclaim(ptr);
};
*/


void init(void* pool,int poolsize)
{
    int i;
    for(i=0;i<5;i++)
    {
        freespace[i]=createDLlist();            
    };
    for(i=0;i<poolsize/16;i++)
    {
        insertnode(4,(char*)pool+16*i);
    };
    return ;
}
