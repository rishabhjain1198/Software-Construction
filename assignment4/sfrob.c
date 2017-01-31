#include<stdio.h>

int frobcmp(char const * first, char const * second)
{
	char a = '\0';
	char b = '\0';
	int i = 0;

	while(first[i] != ' ' && second[i] != ' ')
	{
		a = first[i];
		b = second[i];
		//TIME TO UNFROBNICATE BOTH CHARACTERS

		i++;
		printf("%c %c \n", a, b);	
	}

	return 4;
}

int main()
{
	char hello [5] = "tloa ";
	char test [5] = "lola ";
	int y = frobcmp(hello, test);

	return 0;
}
