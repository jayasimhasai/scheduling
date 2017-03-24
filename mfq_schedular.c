#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "mfq.h"
#define max	5
int handler=1;
struct queue q[max];

void term_child()
{
// signal handler, the termination process
 signal(SIGCHLD, term_child);
 printf("\n a child is dead");
 handler=0;
}


int main(int argc, char const *argv[])
{
 signal(SIGCHLD, term_child);
int pid,i,qt,qc;


//part:1   ************************************checking arguments********************************

	if(argc>3)
	{
		qt = 1000*atoi(&argv[1][0]);
		qc = atoi(&argv[2][0]);
	}

	else
	{

		printf("%s qt qc prog[1] prog[2] .... prog[n]",argv[0]);
		exit(-1);

	}


//part:2   *************************************child creation************************************

	for(i=3; i<argc; i++)
	    {
	      

	      printf("message from father: creating program %s\n", argv[i]);
	     
	      pid= fork();
		
	     
	      if(pid==0)
		{ 
		   execl(argv[i], argv[i], NULL); 
		   kill(getppid(),SIGCHLD);
		   exit(0);
		   
		}
		enqueue(pid,argv[i],&q[0]);

	    }

	sleep(1);



//part:3   ************************************scheduling********************************************
	printf("I am the schedular i will begin scheduling my programs\n");
 for(int i=0;i<qc;i++)
   while(q[i].head!=NULL)
   {		      
	      /* send the signal SIGCONT to the first element in queue */
		kill(q[i].head->pid,SIGCONT);
		usleep((2*i+1)*qt);

	 	if(handler)
		{
		    kill(q[i].head->pid,SIGUSR1); 
		    usleep(1000);
		    if(i==qc-1)
	            enqueue(dequeue(&q[i]),NULL,&q[i]);  
		    else
		    enqueue(dequeue(&q[i]),NULL,&q[i+1]);   
		   
		  /* dequeue and re-enqueue */
		    }

		else
		  {struct node ret;
		    /* remove from list */
				    
		    printf("process %d is dead",dequeue(&q[i]));
			handler=1;
		    /* mark chils as dead */
		    }
	       
	    }
       
  printf("\n All of my children are dead... so bye....");



}



