/*
Assignment 2 Question 2
Matthew Souter & John Hebb
October 3, 2018
Description: This program takes in an input text file and interprets it through a pipe. It then prints that out to an output file.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
//This if statement is checking to see if there were 3 arguments entered into the commandline	
if (argc != 3){
	printf("Usage: filecopy <Input File> <Output File>\n");
exit(1);
}	
	

FILE *fp; //Pointer of type "file", needed for communication between file and program
long lSize;
char *buffer;

	fp = fopen ( "input.txt" , "rb" ); //Takes the file that exists (input.txt) and opens it for reading in binary mode
	if( !fp ) perror("Input File Does Not Exist"),exit(1); //Perror is a C library function that prints descriptive error messages to stderr (Example: "Error: : No such file or directory")
//This is to ensure that failed system calls are handled appropriately

//Fseek is seeking out the sursor to the given record in the file. The las variable is the Whence, in this case, SEEK_END starts the offset from the end of the file
	fseek( fp , 0L , SEEK_END); 
	lSize = ftell( fp );

//Sets the file position to the beginning of the file of a given stream	
	rewind( fp );

//Allocate memory for entire content
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) fclose(fp),fputs("Memory Alloc Fails",stderr),printf("Memory Alloc Fails"),exit(1);

//Copy the file into the buffer 
	if( 1!=fread( buffer , lSize, 1 , fp) )
	fclose(fp),free(buffer),fputs("Entire Read Fails",stderr),printf("Entire Read Fails"),exit(1);

//Do your work here, buffer is a string contains the whole text
int     fd[2], nbytes;
	pid_t childpid;
	
//char    string[] = buffer;
char readbuffer[80];
	pipe(fd);
        
	if((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}

	if(childpid == 0)
	{
//Child process closes up input side of pipe
		close(fd[0]);

//Send "string" through the output side of pipe
		write(fd[1], buffer, (strlen(buffer)+1));
		exit(0);
	}
		
	else
	{
//Parent process closes up output side of pipe
		close(fd[1]);

//Read in a string from the pipe
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		//printf("Received string: %s\n", readbuffer);//uncomment this to see it print to the console as the program is run
	}
        
int num;
FILE *fptr;
	fptr = fopen("copy.txt","w");

	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}

//Writing the content of the collected buffer to the output file
	fprintf(fptr,"%s",buffer);
	fclose(fptr);
//Closing the pointer once the data has been written
			
//Closing the file pointer that opened the original input file
	fclose(fp);
//Deallocates the memory previously allocated
	free(buffer);

return(0);
}//End of main