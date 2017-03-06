
struct node
{
	int pid,val;
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

void insert(struct node ret)
{
	struct queue *temp, *prev, *next;
	temp=malloc(sizeof(queue));
	temp->Node.pid = ret.pid;
	temp->Node.name = ret.name;
	temp->Node.val = ret.val;
	if(Head == NULL)
	{
		Head=temp;
	}

	else
	{	next = Head;
		prev = NULL;
		while(next!=NULL && next->Node.val<=ret.val)
		{
			prev = next;
			next = next->Next;
		}
		if(next==NULL)
		{
			prev->Next= temp;
		}
		else
		{
			if(prev)
			{
			temp->Next=prev->Next;
			prev->Next=temp;
			}
			else
			{
			temp->Next=Head;
			Head=temp;
			}
		}
	}
}
