#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlistlib.h"
#include "feld.h"
#include "snake.h"
#include "consoleinput.h"
#define HEIGTH 16//heigth of the feld with borders
#define LENGTH 16//weigth of the feld with borders

char *createfeld(int heigth, int length);//create the game feld list
int printfeld(char *st, int height, int lenght);//prints the game feld list

int main(int argc, char *args[])
{
	//create feld
	char *feld = createfeld(HEIGTH, LENGTH);

	//testd
	int testcords[] = {0, 0};
	listelement *snake = movesnake('u', NULL, 0, 15, LENGTH, HEIGTH, 0);
	/*updatesnake(snake, feld, LENGTH, HEIGTH);
	if (checksnake(snake))
	{
		printf("You hit yourselfe...\n");
	}
	printfeld(feld, HEIGTH, LENGTH);

	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 1);
	updatesnake(snake, feld, LENGTH, HEIGTH);
	if (checksnake(snake))
	{
		printf("You hit yourselfe...\n");
	}
	printfeld(feld, HEIGTH, LENGTH);

	snake = movesnake('d', snake, 0, 0, LENGTH, HEIGTH, 1);
	updatesnake(snake, feld, LENGTH, HEIGTH);
	if (checksnake(snake))
	{
		printf("You hit yourselfe...\n");
	}
	printfeld(feld, HEIGTH, LENGTH);*/

	/*snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 1);
	snake = movesnake('r', snake, 0, 0, LENGTH, HEIGTH, 1);
	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 1);
	snake = movesnake('r', snake, 0, 0, LENGTH, HEIGTH, 1);*/

	char c, i;
	while ((c = get_input()) != 'E')
	{
		printf("Cycle started\n");
		if (c != '\n')
		{
			snake = movesnake(c, snake, 0, 0, LENGTH, HEIGTH, 1);
			if (checksnake(snake))
			{
				printf("You hit yourselfe...\n");
				break;
			}
			updatesnake(snake, feld, LENGTH, HEIGTH);
			printfeld(feld, HEIGTH, LENGTH);
			printf("I: %d, %p\n", i++, snake);
		}
	}

	printf("Pointer to snake: %p\n", snake);
	printlist(snake, "; ", "\n");
	printf("\n");
	free(feld);
}

