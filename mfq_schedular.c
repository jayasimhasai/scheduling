#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int handler=1;
struct node
{
	int pid,level;
	char *name;

}node;

struct queue
{
struct node Node;
struct queue* Next;

}queue;

struct queue* Head1=NULL;
struct queue* Tail1=NULL;
struct queue* Head2=NULL;
struct queue* Tail2=NULL;

void Enqueue(struct node ret)
{
	struct queue* temp=malloc(sizeof(queue));

	temp->Node.pid = ret.pid;
	temp->Node.name = ret.name;
	temp->Node.level = ret.level;
	temp->Next = NULL;
	if(ret.level==1)
	{
		if(Head1 == NULL && Tail1 == NULL)
		{
			Head1=Tail1=temp;
			return;
		}
		else
		{
		Tail1->Next= temp;
		Tail1 = temp;
		}
	}
	else
	{
		if(Head2 == NULL && Tail2 == NULL)
		{
			Head2=Tail2=temp;
			return;
		}
		else
		{
		Tail2->Next= temp;
		Tail2 = temp;
		}
	}


}

struct node Dequeue(int level)
{	int pid;
	struct queue* temp;
	struct node ret;
	if(level==1)
	{
	ret.pid=Head1->Node.pid;
	ret.name=Head1->Node.name;
	temp=Head1;
	Head1=Head1->Next;
	free(temp);
	}
	else
	{
	ret.pid=Head2->Node.pid;
	ret.name=Head2->Node.name;
	temp=Head2;
	Head2=Head2->Next;
	free(temp);	
	}
	return ret;

}


void term_child()
{
// signal handler, the termination process
 signal(SIGCHLD, term_child);
 printf("\n a child is dead");
 handler=0;
}


int main(int argc, char const *argv[])
{
struct node arg;
 signal(SIGCHLD, term_child);
int pid,i,qt;


//part:1   ************************************checking arguments********************************

	if(argc>2)
	{
		qt = 1000*atoi(&argv[1][0]);
	}

	else
	{

		printf("%s qt prog[1] prog[2] .... prog[n]",argv[0]);
		exit(-1);

	}


//part:2   *************************************child creation************************************

	for(i=2; i<argc; i++)
	    {
	      

	      printf("message from father: creating program %s\n", argv[i]);
	     
	      pid= fork();
		arg.pid=pid;
		arg.name=(char*) argv[i];
		arg.level=1;
	      Enqueue(arg);
	     
	      if(pid==0)
		{ 
		   execl(argv[i], argv[i], NULL); 
		   kill(getppid(),SIGCHLD);
		   exit(0);
		   
		}

	    }

	sleep(1);



//part:3   ************************************scheduling********************************************
	printf("I am the schedular i will begin scheduling my programs\n");
   while(Head1!=NULL||Head2!=NULL)
{	struct node ret;
	while(Head1!=NULL)// scheduling loop
	{	
	      
	      /* send the signal SIGCONT to the first element in queue */
		kill(Head1->Node.pid,SIGCONT);
		usleep(qt);

	 	if(handler)
		{
		    kill(Head1->Node.pid,SIGUSR1); 
		    usleep(1000);
		    ret=Dequeue(1);
		    ret.level=2;
		    Enqueue(ret);   
		   
		  /* dequeue and re-enqueue */
		    }

		else
		  {struct node ret;
		    /* remove from list */
		    ret=Dequeue(1);
		    handler=1;
		    printf("process %s is dead",ret.name);
		    /* mark chils as dead */
		    }
	       
	    }
	while(Head2!=NULL&&Head1==NULL)// scheduling loop
	{	
	      
	      /* send the signal SIGCONT to the first element in queue */
		kill(Head2->Node.pid,SIGCONT);
		usleep(qt*2);

	 	if(handler)
		{
		    kill(Head2->Node.pid,SIGUSR1); 
		    usleep(1000);
		    ret=Dequeue(2);
		    ret.level=2;
		    Enqueue(ret);   
		   
		  /* dequeue and re-enqueue */
		    }

		else
		  {
		    /* remove from list */
		    ret=Dequeue(2);
		    handler=1;
		    printf("process %s is dead",ret.name);
		    /* mark chils as dead */
		    }
	       
	    }
       }

  printf("\n All of my children are dead... so bye....");



}



