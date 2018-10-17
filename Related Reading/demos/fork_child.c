/*
 * fork_child.c
 * 
 * Shows simple process creating using fork
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t child_pid = fork ();
	
	if (child_pid != 0)
		printf ("[PARENT] I am the Parent process with id %d\n\n", (int) getpid());
	else {
		printf ("[CHILD] I am the Child process with id %d\n\n", (int) getpid());

		execlp ("/bin/ls", "ls -l", NULL);

		printf("[CHILD] After execlp?\n");
	}

	printf("[PARENT] Parent now waiting for child...\n\n");
	
	wait(&child_pid);

	printf("\n[PARENT] My child has finished its task. \n\n");
	return 0;
}

