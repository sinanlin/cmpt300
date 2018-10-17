/*
 * signal_ctrl_c.c
 * 
 * Defines a signale handler for SIGINT (CTRL-C), which 
 * overrides the default  handler in the kernel (which kills the process)
 */



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int count = 3;

/* Signal handler function */
void handle_SIGINT()
{
	printf("\nI caught a Ctrl-C!! count = %d!\n", count);
	if(--count == 0)
		exit(0);   
}

int main(int argc, char *argv[])
{
	/* set up the signal handler */
	struct sigaction handler;
	handler.sa_handler = handle_SIGINT;
	sigaction(SIGINT, &handler, NULL);

	printf("Program now waiting for Ctrl-C.\n");
	
	while (1);

	return 0;
}

