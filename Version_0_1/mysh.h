#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define LINE_BUF 512
#define CMD_LEN 64
/*
=======Global variable=======
	* clsfy(define in .c) - for judge the classify
		** oper_1 - for first string follow by command
		** oper_2 - follow by op1
		** oper_3 - follow by op2
		** oper_4 - follow by op3
*/
char oper_1[CMD_LEN];
char oper_2[CMD_LEN];
char oper_3[CMD_LEN];
char oper_4[CMD_LEN];

/* Do the command from main.c , and return status back*/
int fetch_command();
/* Read the command from user*/
char *read_command();
/* Split and read the command , fetch from read_command() */
int split_and_read(char *line);
/* Depend on cmd , and do the specific function */
int apply_command(char *line , int cmd);
/* Flush the user command string buffer */
void flush_and_set();
