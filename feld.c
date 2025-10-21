#include <stdio.h>
#include <stdlib.h>
#include "linkedlistlib.h"

char *createfeld(int heigth, int length);//create the game feld array
int printfeld(char *st, int height, int lenght);//prints the game feld array
int updatesnake(listelement *snake, char *feld, int length, int heigth);//represents snake on the feld, check if snake does not hit its own body

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

int updatesnake(listelement *snake, char *feld, int length, int heigth)
//1. Free the feld
//2. add the snake
{
	//free the feld
	int count = 0;
        for (int i = 0; i < 2*heigth*length; i++)
        {
                feld[i] = '.';
                count++;
        }

	//add snake
	int x, y;
	while (snake != NULL)
	{
		x = ((int*)snake->el)[0];
		y = (((int*)snake->el)[1]) * length;
		feld[(x+y)*2] = feld[(x+y)*2+1] = '#';
		snake = snake->next;
	}
	return 0;
}
