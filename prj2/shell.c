// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define history_depth 10

static int number_of_commands = 0;
char historyCommand[history_depth][COMMAND_LENGTH];

//implicite funciton decleartion

void print_History();
int tokenize_command(char *buff, char *tokens[]);
void read_command(char *buff, char *tokens[], _Bool *in_background);
int internal_command_helper(char* buff, char* tokens[], _Bool* in_background);
int history_command_call(char *buff, char *tokens[], _Bool *in_background, int commandNum);
void signal_handler();
void handle_SIGINT(int sig);
void inputpromt();
/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */

void inputpromt(){
	char curr_dir[COMMAND_LENGTH];

if (getcwd(curr_dir, COMMAND_LENGTH) != NULL) {
	write(STDOUT_FILENO, curr_dir, strlen(curr_dir));
}
else
{
	write(STDOUT_FILENO, "Unable to get current directory\n", strlen("Unable to get current directory\n"));
}
write(STDOUT_FILENO, "$ ", strlen("$ "));


}



int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */

void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);




	if ( (length < 0) && (errno !=EINTR) ){
	    perror("Unable to read command. Terminating.\n");
	    exit(-1);  /* terminate with error */
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}




//Internal command helper

int internal_command_helper(char* buff, char* tokens[], _Bool* in_background){
	//exit. Exit the program
	//pwd. Display the current working directory
	//cd. Change the current working directory
	//type. Display information about command type.

	//This is for the history feature. Whenever there is a command. Increamented by 1.

	if( strcmp(tokens[0], "exit") == 0 ){

	//	write(STDERR_FILENO,"exit is a shell300 builtin\n",strlen("exit is a shell300 builtin\n"));
		strcpy(historyCommand[(number_of_commands%history_depth)],tokens[0]);
		number_of_commands++;
		return -1;
	}


	else if(strcmp(tokens[0],"pwd")==0){
	//	write(STDERR_FILENO,"pwd is a shell300 builtin\n",strlen("pwd is a shell300 builtin\n"));
		//printf("%s,%c\n",tokens[0], tokens[0][1]);

		//Display the current working directory
		char current_directory[COMMAND_LENGTH];

		if(getcwd(current_directory,sizeof(current_directory))!=0){
			//write(STDERR_FILENO,current_directory,strlen(current_directory));
			//write(STDERR_FILENO,"\n",strlen("\n"));
		}else{
			write(STDERR_FILENO,"Error getting current directory\n",strlen("Error getting current directory\n"));
		}

		strcpy(historyCommand[(number_of_commands%history_depth)],tokens[0]);
		number_of_commands++;
		return 1;
	}

	else if(strcmp(tokens[0],"cd")==0){
		//Change current working directory using chdir();
		if(chdir(tokens[1]) != 0){
			write(STDERR_FILENO,"Error in getting the indicated directory\n",strlen("Error in getting the indicated directory\n"));

		//	write(STDERR_FILENO,"cd is a shell300 builtin\n",strlen("cd is a shell300 builtin\n"));

		}
		if(tokens[1] != NULL){
			strcpy(historyCommand[(number_of_commands%history_depth)],tokens[0]);
			strcat(historyCommand[(number_of_commands%history_depth)],"	");
			strcat(historyCommand[(number_of_commands%history_depth)],tokens[1]);

			number_of_commands++;

		}

		return 1;
	}

	//5.1 history commands
	else if(strcmp(tokens[0],"history")==0){
		//Prints out the past ten history command.
		//We should have a counter to keep track of the number
		//We should have an array of strings to keep the comand.

		print_History();
		strcpy(historyCommand[number_of_commands%history_depth],tokens[0]);

		//printf("number_of_commands = %d, history_depth = %d, division = %d \n",number_of_commands,history_depth,(number_of_commands%history_depth));


		number_of_commands++;
		return 1;
	}

	// the ! commands which allows users to run commands directly from the history list:
	else if(tokens[0][0]== '!'){

		//Command "!n" runs command number n
		if(isdigit(tokens[0][1]) ){
			//Situation where n > 10. Don't know how to fix this.

			int num = atoi(&tokens[0][1]);
			return history_command_call(buff, tokens,in_background,num);

		}

		//Command "!!" runs the previous command.
		else if(tokens[0][1] == '!'){
			printf("%i\n",number_of_commands );
			return history_command_call(buff, tokens,in_background,number_of_commands);

		}
		else{
			perror("There is an Error.");
			return -1;
		}


	}

	else if(strcmp(tokens[0],"type")==0){
		if( strcmp(tokens[1],"cd")==0  || strcmp(tokens[1],"pwd")==0 || strcmp(tokens[1],"exit")==0  ){
			write(STDERR_FILENO, tokens[1],sizeof(tokens[1]));
			write(STDERR_FILENO," is a shell300 builtin \n",sizeof(" is a shell300 builtin \n"));
			return 1;
		}
		else{
			write(STDERR_FILENO, tokens[1],sizeof(tokens[1]));
			write(STDERR_FILENO," is not a shell300 builtin \n",sizeof(" is not a shell300 builtin \n"));
			return 1;
		}

	}

	else{
		strcpy(historyCommand[(number_of_commands%history_depth)],tokens[0]);
		int counter = 0;
		while(tokens[counter+1]!= NULL){
			strcat(historyCommand[number_of_commands%history_depth], " ");
			strcat(historyCommand[(number_of_commands%history_depth)],tokens[counter+1]);
			counter++;
		}

		number_of_commands++;
		return 1;

	}

}


//5.Creating history feature

	void print_History(){

		char counter_num[10]= {};//Initialzed this value to avoid garbage.

		if(number_of_commands<history_depth){
			for(int i =0; i < number_of_commands; i++){
				sprintf(counter_num,"%d",(i+1));
				write(STDERR_FILENO,counter_num,sizeof(counter_num));
				write(STDERR_FILENO," ",sizeof(" "));
				write(STDERR_FILENO,historyCommand[i],strlen(historyCommand[i]));
				write(STDERR_FILENO,"\n",strlen("\n"));
			}

		}else{
			for(int j = 0; j<history_depth; j++){
				sprintf(counter_num,"%d",(number_of_commands-history_depth+j+1));
				write(STDERR_FILENO,counter_num,sizeof(counter_num));
				write(STDERR_FILENO,"	",sizeof("	"));
				write(STDERR_FILENO,historyCommand[(number_of_commands+j)%history_depth],strlen(historyCommand[(number_of_commands+j)%history_depth]));
				write(STDERR_FILENO,"\n",strlen("\n"));
			}

		}

	}


int history_command_call(char *buff, char *tokens[], _Bool *in_background, int commandNum){




	if(commandNum<1 || commandNum > number_of_commands || commandNum < (number_of_commands - 9)){
		perror("The command number is out of range.\n");
		return -1;
	}


	strcpy(buff,historyCommand[(commandNum-1)%history_depth]);
	int token_count = tokenize_command(buff,tokens);
	if(token_count == 0){
		perror("Error. Unable to get command");
	}
	*in_background = false;
	if(strcmp(tokens[token_count - 1 ], "&")==0){
		*in_background = true;
		tokens[token_count-1] = 0;
	}


	write(STDERR_FILENO,historyCommand[(commandNum-1)%history_depth],sizeof(historyCommand[(commandNum-1)%history_depth]));
	write(STDERR_FILENO,"\n",strlen("\n"));

	return internal_command_helper(buff,tokens,in_background);

}


//5.2 signals


void signal_handler(){
	struct sigaction handler;
	handler.sa_handler = handle_SIGINT;
	handler.sa_flags = 0;
	sigemptyset(&handler.sa_mask);
	sigaction(SIGINT,&handler,NULL);

}


void handle_SIGINT(int sig){

	write(STDERR_FILENO,"\n",strlen("\n"));
	print_History();
	inputpromt();
}



/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{

	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];

	signal_handler();

	while (true) {
		inputpromt();
		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().

		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		if (input_buffer[0] == '\0' || tokens[0] == NULL) {
			continue;
		}


		int internal_command = internal_command_helper(input_buffer,tokens,&in_background);
		if(internal_command == -1){
			return 0;
		}



  pid_t pid = fork();
//printf("fork returned: %d\n", (int)pid);

if(pid<0){
  perror("Fork failed");
}
if(pid == 0){
//printf("I'm the child process with pid %d\n",(int)pid);
//* 2. Child process invokes execvp() using results in token array.
	execvp(tokens[0], tokens);
	exit(0);
}else{
	pid = wait(NULL);
}


//handle any zomboe Processing
/*  3. If in_background is false, parent waits for
  *    child to finish. Otherwise, parent loops back to
  *    read_command() again immediately.
*/
if (in_background == false) {
	while (waitpid(-1, NULL, WNOHANG) > 0);
}
else {
	continue;
}

}
	return 0;
}
