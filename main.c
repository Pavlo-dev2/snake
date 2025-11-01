#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linkedlistlib.h"
#include "feld.h"
#include "snake.h"
#include "input.h"
#include "consoleinput.h"
#define HEIGTH 16//heigth of the feld with borders
#define LENGTH 16//weigth of the feld with borders
#define SPEED 100//speed on the begining of the game
#define SPEEDDIF 20//how fast speed drows up
#define SPEEDMAX 20//max speed

//char *createfeld(int heigth, int length);//create the game feld list
//int printfeld(char *st, int height, int lenght);//prints the game feld list

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

	char c, i, a;
	int apple = createapple(feld, LENGTH, HEIGTH, len(snake), -1);
	a = checkapple(snake, apple, LENGTH);
	int applecount = 0;
	float speed = SPEED;
	float time;
	while ((c = input()) != 'E')
	{
		printf("Speed: %f\n", speed);
		time = clock()/CLOCKS_PER_SEC;
		if (a)
		{
			applecount++;
			if (speed > SPEEDMAX)
			{
				speed -= SPEEDDIF;
			}
		}
		printf("Cycle started\n");
		if (c != '\n')
		{
			snake = movesnake(c, snake, 0, 0, LENGTH, HEIGTH, a);
			if (checksnake(snake))
			{
				printf("You hit yourselfe...\n");
				break;
			}
			else if (snake == NULL)
			{
				break;
			}
			updatesnake(snake, feld, LENGTH, HEIGTH);
			if (a = checkapple(snake, apple, LENGTH))
			{
				apple = createapple(feld, LENGTH, HEIGTH, len(snake), -1);
			}
			else
			{
				apple = createapple(feld, LENGTH, HEIGTH, len(snake), apple);
			}
			printf("Hit the apple: %d\nApple: %d\n", a, apple);
			printfeld(feld, HEIGTH, LENGTH);
			printf("I: %d, %p\n", i++, snake);
			while((clock()/CLOCKS_PER_SEC)-time < speed/100);
		}
		printf("Apple count: %d\n", applecount);
	}

	printf("Pointer to snake: %p\n", snake);
	printlist(snake, "; ", "\n");
	printf("\n");
	free(feld);
}

