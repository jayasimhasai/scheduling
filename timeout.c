#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


int pid;
void term_child()
{
// signal handler, the termination process
 printf("\n parent terminating child after timeout");
 kill(pid, SIGTERM);
exit(0);
}

void child_comp()
{
printf("\n child completed before timeout");
exit(0);
}

int main(int argc, char const *argv[])
{
	
	signal(SIGALRM, term_child);
	signal(SIGCHLD, child_comp);
	int i,qt;


	if(argc>2)
	{
		qt = atoi(&argv[1][0]);
	}

	else
	{

		printf("%s qt prog[1] prog[2] .... prog[n]",argv[0]);
		exit(-1);

	}

	for(i=2; i<argc; i++)
	    {
	      

	      printf("message from father: creating program %s\n", argv[i]);
	     
	      pid= fork();
	     
	      if(pid==0)
		{ 
		   execl(argv[i], argv[i], NULL); 
		   kill(getppid(),SIGCHLD);
		   exit(0);
		   
		}

	    }
	sleep(1);
	kill(pid,SIGCONT);

	 alarm(qt);
	 pause();
	   

}



