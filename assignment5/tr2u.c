#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


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
    
    //USING UNBUFFERED STREAM
    
  char curr[1];     //this holds the inputted character
  ssize_t state = read(0,curr, 1);      //taking input one character at a time
  while(state > 0)
  {
  	for(size_t i = 0; i < strlen(from); i++)
	{
	  if(curr[0] == from[i])           //if byte is the same
	  {
	  	curr[0] = to[i];        //change byte to the byte in to
	  	write(1,curr,1);        //write it to stdout
	  	matchInFrom = 1;            //match was found
	  	break;
	  }
	  else
	  {
	  	matchInFrom = 0;
	  }
	}
	if(!matchInFrom)
	{
	  write(1,curr,1);      //if it was not a match, write it to stdout
	}
	state = read(0,curr,1);
  }
  return 0;
}
