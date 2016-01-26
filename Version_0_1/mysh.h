#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_BUF 512

/*
=======Global variable=======
*/

/* Do the command from main.c , and return status back*/
int fetch_command();
/* Read the command from user*/
char *read_command();
/* Split and read the command , fetch from read_command() */
int split_and_read(char *line);
/* Depend on cmd , and do the specific function */
int apply_command(char *line , int cmd);
