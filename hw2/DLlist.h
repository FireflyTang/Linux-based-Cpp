typedef struct node* pnode;

struct node
{
    void* address;
    pnode next,previous;
};

pnode createDLlist();
pnode createnode();
void* insertnode(int indexnumber,void* address);
void* deletenode(int indexnumber,void* address);
void* getaddress(int indexnumber);
void* getnextaddress(int indexnumber,void* address);
void* getpreviousaddress(int indexnumber,void* address);
bool _isempty(int indexnumber);

