#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <linux/input.h>
#include "linkedlistlib.h"
#include "feld.h"
#include "snake.h"
#include "input.h"
#define HEIGTH 16//heigth of the feld with borders
#define LENGTH 16//weigth of the feld with borders
#define SPEEDDEV 0.75//how fast speed drows up
#define MINTIME 0.1//minimal time betwine moves in sec
#define STARTTIME 1//starting time

int getdir(int fd, long double time, int snakelen);//get directory

int main(int argc, char *args[])
{

	//create feld
	char *feld = createfeld(HEIGTH, LENGTH);

	//create snake
	listelement *snake = movesnake('u', NULL, 0, 15, LENGTH, HEIGTH, 0);

	//create apple
	int apple = createapple(feld, LENGTH, HEIGTH, len(snake), -1);
	
	int fd = retfd(1, 2);//input file deckriptor
	
	long double slt = STARTTIME;//time bitwine moves in sec
	
	char c;//direction
	char a = checkapple(snake, apple, LENGTH);//1 if hit apple, 0, if not
	
	int applecount = 0;//counts apple

	//game loop
	while ((c = getdir(fd, slt, applecount)) != 'E')//get input
	{
		//print information
		//printf("core: %d\nSpeed: %.0f\n", applecount, speed);

		//if hit apple
		if (a)
		{
			applecount++;
			if (slt*SPEEDDEV >= MINTIME)
			{
				slt *= SPEEDDEV;
			}
		}
		
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

		//update feld
		updatesnake(snake, feld, LENGTH, HEIGTH);
		if (a = checkapple(snake, apple, LENGTH))
		{
			apple = createapple(feld, LENGTH, HEIGTH, len(snake), -1);
		}
		else
		{
			apple = createapple(feld, LENGTH, HEIGTH, len(snake), apple);
		}
		//putchar('\n');
		drawfeld(feld, HEIGTH, LENGTH);
		
		//sleap
		//usleep(time);
	}

	printf("Score: %d\nSLT: %Lf\n", applecount, slt);
	free(feld);
}

int getdir(int fd, long double time, int snakelen)
//get directory
{
	static char dir = 'u';
	static int events[] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_E};
	int code = ifeventscode(fd, events, 5, 1, time);
	switch (code)
	{
		case KEY_W:
			if (dir != 'd' || snakelen == 0)
			{
				dir = 'u';
				break;
			}
		case KEY_D:
			if (dir != 'l' || snakelen == 0)
			{
				dir = 'r';
				break;
			}
		case KEY_S:
			if (dir != 'u' || snakelen == 0)
			{
				dir = 'd';
				break;
			}
		case KEY_A:
			if (dir != 'r' || snakelen == 0)
			{
				dir = 'l';
				break;
			}
		case KEY_E:
			dir = 'E';
			break;
	}
	return dir;
}
