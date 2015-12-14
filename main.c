#include <stdio.h>
#include <stdlib.h>

/* Define */
#define BUFFSIZE 1024

void fetch_command();
/*In fetch_command ==>*/ char *command_read(); 


int main(int argc , char **argv){
	// Loop the command
	fetch_command();
	return 0;
}

void fetch_command(){
	char *line;
	char **args;
	int status = 1;
	printf("Welcome using the mini-shell by Kevin Chiu!!\n");
	printf("Some useful command : \n\'Help\' : to list some tip in shell\n");
	do{
		printf("kevin@mini-shell:~$");
		// fetch user input
		line = command_read();
		printf("%s\n" , line);
		// split the line
		args = command_split(line);
		// decide the status : when to exit	
		status = command_execute(args);
		// Free the memory
		free(line);
		free(args);
	}while(status);
}

/*In fetch_command ==>*/ 
char *command_read(){
	int bufsize = BUFFSIZE;
	int position = 0;
	char *buffer = malloc(bufsize*sizeof(char));
	char c;
	
	if(!buffer){
		fprintf(stderr , " cmd read : buffer malloc error\n ");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		// read a character
		c = getchar();
		// Judge to keep read or go next step
		if(c == EOF || c == '\n'){
			buffer[position] = '\0';
			// return the result
			return buffer; 
		}
		else{
			buffer[position] = c;
		}
		position++;
		
		// if  input is > 1024 
		if(position >= bufsize){
			bufsize+=BUFFSIZE;
			buffer = realloc(buffer, bufsize);
			if(!buffer){
				fprintf(stderr , " cmd read : buffer realloc error\n ");
				exit(EXIT_FAILURE);
			}
		}
	}	
}
