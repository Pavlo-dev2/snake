#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "linkedlistlib.h"
#include "feld.h"
#include "snake.h"
#include "input.h"
#include "consoleinput.h"
#define HEIGTH 16//heigth of the feld with borders
#define LENGTH 16//weigth of the feld with borders
#define SPEED 100//speed on the begining of the game
#define SPEEDDIF 10//how fast speed drows up
#define SPEEDMAX 200//max speed

int main(int argc, char *args[])
{
	//create feld
	char *feld = createfeld(HEIGTH, LENGTH);

	//create snake
	listelement *snake = movesnake('u', NULL, 0, 15, LENGTH, HEIGTH, 0);

	//create apple
	int apple = createapple(feld, LENGTH, HEIGTH, len(snake), -1);
	
	float speed = SPEED;//snake speed
	float slt = 1*1000000;//time bitwine moves in sec
	float time = 1*1000000;//time to wate after input
	
	char c;//direction
	char a = checkapple(snake, apple, LENGTH);//1 if hit apple, 0, if not
	
	int applecount = 0;//counts apple

	//game loop
	while ((c = input(&time)) != 'E')//get input
	{
		//print information
		printf("Score: %d\nSpeed: %.0f\n", applecount, speed);

		//if hit apple
		if (a)
		{
			applecount++;
			if (speed < SPEEDMAX)
			{
				speed += SPEEDDIF;
				slt = slt-speed*1000;
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
		printfeld(feld, HEIGTH, LENGTH);
		
		//sleap
		printf("SLT: %f\n", slt);
		usleep(time);
		time = slt;
	}

	free(feld);
}

