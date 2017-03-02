
struct node
{
	int pid;
	char *name;

}node;

struct queue
{
struct node Node;
struct queue* Next;

}queue;

struct queue* Head=NULL;
struct queue* Tail=NULL;

void Enqueue(struct node ret)
{
	struct queue* temp=malloc(sizeof(queue));

	temp->Node.pid = ret.pid;
	temp->Node.name = ret.name;
	temp->Next = NULL;

	if(Head == NULL && Tail == NULL)
	{
		Head=Tail=temp;
		return;
	}
	else
	{
	Tail->Next= temp;
	Tail = temp;
	}
}

struct node Dequeue()
{	int pid;
	struct queue* temp;
	struct node ret;
	ret.pid=Head->Node.pid;
	ret.name=Head->Node.name;
	temp=Head;
	Head=Head->Next;
	free(temp);
	return ret;

}

