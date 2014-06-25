typedef struct node* pnode ;

void show();
void init(void* pool,int poolsize);

void* acquire(int size);
void* reclaim(void* address);




