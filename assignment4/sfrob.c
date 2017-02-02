#include<stdio.h>

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

int main()
{
    
    char* one;
    char** all;
    one = (char*)malloc(sizeof(char));
    all = (char**)malloc(sizeof(char*));
    
    char curr = getchar();
    readErr();
    char next = getchar();
    readErr();
    
    int letterIterator = 0;
    int allIterator = 0;
    while(curr != EOF && !ferror(stdin)) //Read file until EOF
    {
        
        one[letterIterator] = curr; //Add letters to the one
        //Constantly reallocate space for growing all
        char* temp = realloc(one, (letterIterator+2)*sizeof(char));
        if(temp != NULL)
        {
            //Make the one equal to the reallocated space
            one = temp;
        }
        else //Allocation error, print error and exit
        {
            free(one);
            fprintf(stderr, "Error Allocation Memory!");
            exit(1);
        }
        
        
        if(curr == ' ') //Hit the end of the one
        {
            all[allIterator] = one; //Add one to all list
            //Constantly reallocate space for growing alllist
            char** anotherOne = realloc(all, (allIterator+2)*sizeof(char*));
            if(anotherOne != NULL)
            {
                //Make all equal to reallocated space
                all = anotherOne;
                allIterator++;
                //Set one back to empty by pointing it to other space
                one = NULL;
                one = (char*)malloc(sizeof(char));
                letterIterator = -1; //-1 to bring back to 0 when summed later
            }
            else //Allocation error, print error and exit
            {
                free(all);
                fprintf(stderr, "Error Allocation Memory!");
                exit(1);
            }
        }
        if(next == EOF && curr == ' ')
        {
            break;
        }
        else if (curr == ' ' && next == ' ') //Ignore Extra Spaces
        {
            while(curr == ' ')
            {
                curr = getchar();
                readErr();
            }
            next = getchar();
            readErr();
            letterIterator++;
            continue;
        }
        else if(next == EOF) //Add a space at the end if there isn't already one
        {
            curr = ' ';
            letterIterator++;
            continue;
        }
        //increment our letter counter and get the next character
        curr = next;
        next = getchar();
        readErr();
        letterIterator++;
        
    }
    
    
    //Sort the frobnicated all from our all list
    qsort(all, allIterator, sizeof(char*), compareit);
    
    //Output the all to STDOUT using putchar
    for(size_t i = 0; i < allIterator; i++)
    {
        for(size_t j = 0; ;j++)
        {
            //EOF error checking
            if(putchar(all[i][j]) == EOF)
            {
                fprintf(stderr, "Error while writing character!");
                exit(1);
            }
            if(all[i][j] == ' ')
            {
                break;
            }
        }
    }
    //De-allocate all the space taken up for the all
    for(size_t i = 0; i < allIterator; i++)
    {
        free(all[i]);
    }
    free(all);
    
    exit(0);
}
