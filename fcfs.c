#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "queue.h"

int handler=1;
void term_child()
{
// signal handler, the termination process
 signal(SIGCHLD, term_child);
 printf("\n a child is dead");
 handler=0;
}


int main(int argc, char const *argv[])
{
	struct node arg,ret;
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
		arg.name=argv[i];
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
	while(Head!=NULL)// scheduling loop
	{	
	      
	      /* send the signal SIGCONT to the first element in queue */
		kill(Head->Node.pid,SIGCONT);
		pause();
	      /* remove from list */
	        ret=Dequeue();
		  
	         printf("process %s is dead",ret.name);
	      /* mark chils as dead */
		   
	       
	    }

  printf("\n All of my children are dead... so bye....");



}



