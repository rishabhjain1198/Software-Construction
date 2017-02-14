#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
  //Making sure number of arguments is 3
  if(argc != 3)
  {
  	fprintf(stderr, "Exactly 2 arguments are required");
  	exit(1);
  }
  char* from = argv[1];
  char* to = argv[2];
    
  //Checking to see if they're the same length
  if(strlen(from) != strlen(to))
  {
  	fprintf(stderr, "Inputs were not of the same size");
  	exit(1);
  }

  //Taking care of the case of duplicate bytes
  for(size_t i = 0; i < strlen(from); i++)
  {
  	for(size_t j = i+1; j < strlen(from); j++)
	{
	  if(from[j] == from[i])
	  {
	  	fprintf(stderr, "Duplicate bytes found. Exiting");
	  	exit(1);
	  }
	}
  }

//USING BUFFERED STREAM
    
  char curr = getchar();        //get character from buffer
  int matchInFrom = 0;  //this keeps track of whether a match was found or not
  while(curr != EOF)    //go through till the end of input
  {
  	for(size_t i = 0; i < strlen(from); i++)
	{
	  if(curr == from[i])
	  {
        //match was found
	  	putchar(to[i]);
	  	matchInFrom = 1;
	  	break;
	  }
	}
	if(!matchInFrom)
	{
        putchar(curr);
	}
    else
    {
        matchInFrom = 0;
    }
	curr = getchar();
  }

  return 0;
}
