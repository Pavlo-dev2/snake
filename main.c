#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlistlib.h"
#include "feld.h"
#include "snake.h"
#define HEIGTH 16//heigth of the feld with borders
#define LENGTH 16//weigth of the feld with borders

char *createfeld(int heigth, int length);//create the game feld list
int printfeld(char *st, int height, int lenght);//prints the game feld list

int main(int argc, char *args[])
{
	//create feld
	char *feld = createfeld(HEIGTH, LENGTH);
	printfeld(feld, HEIGTH, LENGTH);

	//testd
	int testcords[] = {0, 0};
	listelement *snake = movesnake('u', NULL, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('u', snake, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('l', snake, 0, 0, LENGTH, HEIGTH, 0);
	snake = movesnake('l', snake, 0, 0, LENGTH, HEIGTH, 0);

	printf("Pointer to snake: %p\n", snake);
	printlist(snake, "; ", "\n");
	printf("\n");
	free(feld);
}

