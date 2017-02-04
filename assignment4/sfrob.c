#include<stdio.h>
#include<stdlib.h>

int frobcmp(char const * first, char const * second)
{
	while(1)
	{		//run loop until a value is returned
		if(*first==' ' && *second==' ')
			return 0;
		else if(*first==' ' || ((*first^42) < (*second^42)))
			return -1;
		else if(*second==' ' || ((*first^42) > (*second^42)))
			return 1;	//bitwise operator used to unfrobnicate single characters and then they are compared
		first++; 	//go onto next character for both pointers
		second++;
	}
}

int compareit(const void* l1, const void* l2)
{
    const char* x = *(const char**)l1;
    const char* y = *(const char**)l2;
    return frobcmp(x,y);
}       //function to be passed in qsort

//reading errors to be checked here
void errCheck()
{
    if(ferror(stdin))
    {
        fprintf(stderr, "error in file");
        exit(1);
    }
}


int main()
{
    
    char* one; //This holds a single words
    char** all; //This holds all the words
    one = (char*)malloc(sizeof(char));  //allocating space for a single word
    all = (char**)malloc(sizeof(char*));    //allocating space for all the words
    char letter = getchar();
    errCheck();
    char nextLetter = getchar();
    errCheck();
    int letterIterator = 0;
    int allIterator = 0;
    while(letter != EOF && !ferror(stdin)) //Read file until EOF
    {
        
        one[letterIterator] = letter; //Add letters to the one
        //Constantly reallocate space for growing all
        char* temp = realloc(one, (letterIterator+2)*sizeof(char));
        if(temp != NULL)
        {
            //If no error is found, assign the words
            one = temp;
        }
        else //Error was found, exit
        {
            free(one);
            fprintf(stderr, "memory not allocated");
            exit(1);
        }
        
        
        if(letter == ' ') //One word has been completed
        {
            all[allIterator] = one; //Adding word to list
            
            char** anotherOne = realloc(all, (allIterator+2)*sizeof(char*));
            if(anotherOne != NULL)
            {
                all = anotherOne;
                allIterator++;
                //Set one back to empty
                one = NULL;
                one = (char*)malloc(sizeof(char));  //allocating new space for the nextLetter word
                letterIterator = -1;
            }
            else
            {
                free(all);
                fprintf(stderr, "memory not allocated");
                exit(1);
            }
        }
       
        if (letter == ' ' && nextLetter == ' ') //Ignore Extra Spaces
        {
            while(nextLetter == ' ')
            {
                nextLetter = getchar();
                errCheck();
            }
            letter = nextLetter;
            nextLetter = getchar();
            errCheck();
            letterIterator++;
            continue;
        }
        else if(nextLetter == EOF)
        {
            letter = ' ';
            letterIterator++;
            continue;
        }
    
        letter = nextLetter;
        nextLetter = getchar();
        errCheck();
        letterIterator++;
        
    }
    
    
    //Using qsort to sort the list in all
    qsort(all, allIterator, sizeof(char*), compareit);
    
    //time to output the sorted list
    for(size_t i = 0; i < allIterator; i++)
    {
        for(size_t j = 0; ;j++)
        {
            //checking if file is already at end when it isn't supposed to be, so it'll be an error
            if(putchar(all[i][j]) == EOF)
            {
                fprintf(stderr, "Writing error");
                exit(1);
            }
            //If space is found time, to end the word
            if(all[i][j] == ' ')
            {
                break;
            }
        }
    }
   
    
    //giving back memory
    for(size_t i = 0; i < allIterator; i++)
    {
        free(all[i]);
    }
    free(all);
    
    exit(0);
}
