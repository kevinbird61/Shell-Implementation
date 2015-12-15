/* Reference by  Stephen Brennan , Github : https://github.com/brenns10*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* Define */
#define BUFFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM "\t\r\n\a" // filter of token

/* For fetching the command */
void fetch_command();
/*In fetch_command ==>*/ char *command_read(); 
/*In fetch_command ==>*/ char **command_split(char *line); 
/*In fetch_command ==>*/ int command_execute(char **args);

/* For Start process */
int command_launch(char **args);

/* 
	Function of shell command
*/
int cd_cmd(char **args);
int help_cmd(char **args);
int exit_cmd(char **args);
/*
	List of builtin commands 
*/
char *builtin_str[] = {
	"cd",
	"help",
	"exit",
};

int (*builtin_func[])(char **) = {
	&cd_cmd,
	&help_cmd,
	&exit_cmd
}; // For function array

int builtin_cmd_num(){
	return sizeof(builtin_str) / sizeof(char *);
}

/*  Main funciton */
int main(int argc , char **argv){
	// Enter Loop (the command)
	fetch_command();
	return 0;
}

/*
	Builtin function implementations
*/
int cd_cmd(char **args){
	if(args[1] == NULL){
		fprintf(stderr , "Expected argument to \"cd\"\n");
	}
	else{
		if(chdir(args[1])!=0){
			perror("Cmd cd fail\n");
		}
	}
	return 1;
}

int help_cmd(char **args){
	int i;
	printf("Kevin Chiu's mini shell \n");
	printf("Here are some useful tips:\n");
	for(i = 0; i < builtin_cmd_num(); i++){
		printf("	%s \n" , builtin_str[i]);
	}
	printf("Use above command to manipulate\n");
	return 1;
}

int exit_cmd(char **args){
	return 0;
}

void fetch_command(){
	char *line;
	char **args;
	int status = 1;
	printf("Welcome using the mini-shell by Kevin Chiu!!\n");
	printf("Some useful command : \n\'help\' : to list some tip in shell\n\n");
	do{
		printf("kevin@mini-shell:~$");
		// fetch user input
		line = command_read();
		//printf("%s\n" , line);
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

/*In fetch_command ==>*/ 
char **command_split(char *line){
	int bufsize = TOK_BUFSIZE , position = 0;
	/* FIXME : why 2D array? */
	char **tokens = malloc(bufsize*sizeof(char*));
	char *token;
	
	if(!tokens){
		fprintf(stderr , "Token malloc error\n");
		exit(EXIT_FAILURE);
	}
	/* split out the token */
	token = strtok(line , TOK_DELIM);
	while(token!=NULL){
		tokens[position] = token;
		position++;
		if(position >= bufsize){
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens , bufsize*sizeof(char*));
			if(!tokens){
				fprintf(stderr , "Token realloc error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL , TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

/*In fetch_command ==>*/ 
int command_execute(char **args){
	// For executing cmd function
	int i;
	if(args[0] == NULL){
		// an empty cmd was entered
		return 1;
	}
	
	for(i = 0; i < builtin_cmd_num(); i++){
		if(strcmp(args[0] , builtin_str[i]) == 0){
			return (*builtin_func[i])(args);
		}
	}
	return command_launch(args);
}

/* For Start process */
int command_launch(char **args){
	pid_t pid,wpid;
	int status;
	
	pid = fork();
	if(pid == 0){
		// Child process
		if(execvp(args[0] , args) == -1){
			perror("Execvp error");
		}
		exit(EXIT_FAILURE);
	}else if(pid < 0){
		// Error
		perror("Fork Error");
	}else{
		// Parent process
		do{
			wpid = waitpid(pid , &status , WUNTRACED);
		}while (!WIFEXITED(status) && !WIFSIGNALED(status));
		/*FIXME : what is WIFEXITED and WIFSIGNALED*/
	}
	 return 1;
}	
