#include <stdio.h>
#include <stdlib.h>

char *createfeld(int heigth, int length);//create the game feld array
int printfeld(char *st, int height, int lenght);//prints the game feld array

char *createfeld(int heigth, int length)
{
	int count = 0;
	char *st = malloc(sizeof(char)*2*heigth*length);
	for (int i = 0; i < 2*heigth*length; i++)
	{
		st[i] = '.';
		count++;
	}
	printf("Count: %d\n", count/2);
	return st;

}
int printfeld(char *st, int heigth, int length)
{
	int tot = 0;
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < length*2; x++)
		{
			putchar(st[tot]);
			tot++;
		}
		printf("\n");
	}
	return 0;
}
