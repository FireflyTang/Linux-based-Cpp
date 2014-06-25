#include <iostream>
#include <stdlib.h>

#include "DLlist.h"

extern pnode freespace[5];

pnode createDLlist()
{
    pnode t =new node;
    t->address=0;
    t->next =t;
    t->previous =t;
    return t;
};

pnode createnode()
{
    pnode t = new node;
    return t;
};

void* insertnode(int indexnumber,void* address)
{
    pnode p;
   p=freespace[indexnumber];
    while((p->next->address<address)&&(p->next->address!=0))
    {
        p=p->next;
    }
    pnode t= createnode();
    p->next->previous=t;                                                
    t->next=p->next;
    t->previous=p;
    p->next=t;
    t->address=address;
    return address;            
};

void* deletenode(int indexnumber,void* address)
{
    pnode p;
    p=freespace[indexnumber]->next ;
    while(p->address!=address)
    {
        if(p->address==0)
        {
            exit(1);
        }
        else
        {
            p=p->next;
        };
    };
    p->previous->next=p->next;
    p->next->previous=p->previous;
    delete p;
    return p;
};

void* getaddress(int indexnumber)
{
    if(_isempty(indexnumber))
    {
        return 0;
    }
    else
    {
        return freespace[indexnumber]->next->address;
    };
};

void* getnextaddress(int indexnumber,void* address)
{
    pnode p;
    p=freespace[indexnumber]->next;
    while(p->address!=address)
    {
        if(p->address==0)
        {
            exit(2);
        }
        else
        {
            p=p->next;       
        };
    };
    return p->next->address;
};

void* getpreviousaddress(int indexnumber,void* address)
{
    pnode p;
    p=freespace[indexnumber]->next;
    while(p->address!=address)
    {
        if(p->address==0)
        {
            exit(3);
        }
        else
        {
            p=p->next;       
        };
            
    };
    return p->previous->address;
};

bool _isempty(int indexnumber)
{
  if(freespace[indexnumber]->next==freespace[indexnumber])
  {
      return true;
  };
  return false;
};

