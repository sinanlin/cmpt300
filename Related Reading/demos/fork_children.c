/*
 * fork_children.c
 *
 * Shows the creation of multiple processes, each runs for long 
 * time to compute a prime number
 * allows to see multiple children running and their PIDs
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "prime.h"

#define NUM_CHILDREN 5


int main()
{
	printf("[PARENT] Demo using fork with child processes finding primes.\n");

	// Make many children
	for (int i = 0; i < NUM_CHILDREN; i++) {
		// Spawn child
		pid_t child_pid = fork();

		// Handle errors
		if (child_pid < 0) {
			printf("[PARENT] Error forking.\n");
			exit (EXIT_FAILURE);
		}

		// If "I am child":
		if (child_pid == 0) {  // I will not replace my parent's code (no exec)
			printf ("[CHILD %d] I am child #%d, pid=%d\n", i, i, (int) getpid());
			long long answer = findPrime(i);
			printf("[CHILD #%d] My prime is %lld\n", i, answer);
			exit(EXIT_SUCCESS);
		}
	}

	printf("[PARENT] Now waiting for children...\n");
	for (int i = 0; i < NUM_CHILDREN; i++) {
		// Wait for any child to complete 
		// (status is just "what caused the child to end")
		int status = 0;
		int pid = wait(&status);
		printf("[PARENT] # children complete: %d     status: %d,  pid: %d.\n",
			 i + 1,
			 status,
			 pid);

	}

	printf("[PARENT] Done running process %d\n", (int) getpid());
	return 0;
}

