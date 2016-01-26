CC = gcc
OBJS = mysh.o main.o
EXEC = minshell

$(EXEC):$(OBJS)
	gcc -o $(EXEC) $(OBJS)  
mysh.o:mysh.c mysh.h
	gcc -c mysh.c
main.o:main.c mysh.h
	gcc -c main.c
	
run:
	./$(EXEC)
clean:
	rm $(EXEC) $(OBJS) 
