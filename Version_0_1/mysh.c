#include "mysh.h"

int fetch_command()
{
	/* Local Variable defined
		int -
		status = judge the command status for shell , and do exit if it catch exit() ...etc 
		cmd = do the specific command , the value is generate by split_and_read(string)
		String -
		line = line of command , catch from function - read_command()
	*/
	int status = 1,cmd = 0;
	char *line;
	// do the loop to fetch command from user
	while(status){
		// fetch the line of command 
		line = read_command();
		// Split the command , and read
		cmd = split_and_read(line);
		// Depend on cmd , do the specific function
		status = apply_command(line,cmd);
	}
}

char* read_command()
{
	/* Local variable */
	char c;
	int index = 0;
	char *buffer = malloc(LINE_BUF*sizeof(char));
	/* Loop for getchar */
	while(1){
		c = getchar();
		if(c == '\n' || c == EOF){
			buffer[index] = '\0';
			return buffer;	
		}
		else{
			buffer[index] = c;
			index++;
		}
		// TODO: Check if > LINE_BUF
	}
}

int split_and_read(char *line)
{
	/* Local Variable */
	char clsfy[256],leftover[512];
	// split the first string , and then classify
	sscanf(line,"%s %[^\n]",clsfy,leftover);
	// do the first judgement layer
	if(!strcmp(clsfy,"ls")){
		// do the listing classification
		
		// FIXME : change to correct return value when this classification is implemented
		return 1;
	}
	else if(!strcmp(clsfy,"disk")){
		// do the disk operation - for file system
		
		// FIXME : change to correct return value when this classification is implemented
		return 1;
	}
	else if(!strcmp(clsfy,"file")){
		// do the file operation - for file system
		
		// FIXME : change to correct return value when this classification is implemented
		return 1;
	}
	else if(!strcmp(clsfy,"help")){
		// do the guide line of the shell - list all command (optional)
		
		// FIXME : change to correct return value when this classification is implemented
		return 1;
	}
	else if(!strcmp(clsfy,"exit")){
		// do exit
		return 0;
	}
	else{
		// not match any command
		printf("Command not found : %s , Not match any existed command!!\nPlease try again , or using 'help' to look up command\n",clsfy);		
		return -1;		
	}
	// for debug
	printf("%s , %s\n",clsfy,leftover);
	
	return 0;
}

int apply_command(char *line , int cmd)
{
	if(cmd == 0){
		// exit
		printf("goodbye!\n");
		return 0;
	}
	// FIXME : do the specific , if-else operator
	else{
		// Not match
		return 1;
	}
}
