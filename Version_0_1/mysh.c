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
		// Show the beginning
		printf("kevin@mini-shell:~$ ");
		// Clear the global buffer
		flush_and_set();
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
	sscanf(line,"%s %s %s %s %s %[^\n]",clsfy,oper_1,oper_2,oper_3,oper_4,leftover);
	printf("%s %s %s %s \n",oper_1,oper_2,oper_3,oper_4);
	// do the first judgement layer
	if(!strcmp(clsfy,"ls")){
		// do the listing classification
		printf("Your command will deal with the listing classification.\n");
		return 2;
	}
	else if(!strcmp(clsfy,"disk")){
		// do the disk operation - for file system
		printf("Your command will deal with the file-system : disk operation.\n");
		return 3;
	}
	else if(!strcmp(clsfy,"file")){
		// do the file operation - for file system
		printf("Your command will deal with the file-system : file operation.\n");
		return 4;
	}
	else if(!strcmp(clsfy,"help")){
		// do the guide line of the shell - list all command (optional)
		printf("Your command will show you the guide-line of this shell system.\n");
		return 1;
	}
	else if(!strcmp(clsfy,"exit")){
		// do exit
		return 0;
	}
	else if(!strcmp(clsfy,"compile")){
		// do compile , FIXME - "compile" could change to another significant word 
		return 5;
	}
	else{
		// not match any command
		printf("Command not found : %s , Not match any existed command!!\nPlease try again , or using 'help' to look up command\n",clsfy);		
		return -1;		
	}
}

int apply_command(char *line , int cmd)
{
	/* Info : this layer's return value is for shell status => 0 : exit , 1 : keep doing*/
	if(cmd == 0){
		// exit
		printf("goodbye!\n");
		return 0;
	}
	else if(cmd == 1){
		// help - print out all the command shell provide
		printf("Thanks to use 'help' command , here comes the useful command we provide:\n");
		printf("About File-System manipulation : \n");
		printf("\tDisk: some operation about disk - create , destroy ...\n");
		printf("\tFile: some operation about file - create , delete , read , write ...\n");
		printf("About System command : \n");
		printf("\t\"help\":list all the existed command\n");
		printf("\t\"ls\":list all the existed file(current directory read file)\n");
		printf("\t\t - \"ls disk\":list all the existed disk(virtual , create by user , apply to file system)\n");
		printf("\t\"exit\": exit the shell system\n");
		return 1;
	}
	else if(cmd == 2){
		// ls , ls disk
		
	}
	else if(cmd == 3){
		// disk 
	}
	else if(cmd == 4){
		// file
	}
	else if(cmd == 5){
		// compile
	}
	// FIXME : do the specific , if-else operator
	else{
		// -1 , Not match
		return 1;
	}
}

void flush_and_set()
{
	/* Global Variable Setting */
	memset(oper_1,'\0',CMD_LEN);
	memset(oper_2,'\0',CMD_LEN);
	memset(oper_3,'\0',CMD_LEN);
	memset(oper_4,'\0',CMD_LEN);
}
