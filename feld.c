#include <stdio.h>
#include <stdlib.h>
#include "output.h"
#include "linkedlistlib.h"
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>

char *createfeld(int heigth, int length);
//create the game feld array

int printfeld(char *st, int height, int lenght);
int drawfeld(char *st, int height, int lenght);
//prints the game feld array

int updatesnake(listelement *snake, char *feld, int length, int heigth);
//represents snake on the feld, check if snake does not hit its own body

char *createfeld(int heigth, int length)
{
	int count = 0;
	char *st = malloc(sizeof(char)*heigth*length);
	for (int i = 0; i < heigth*length; i++)
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
		for (int x = 0; x < length; x++)
		{
			putchar(st[tot]);
			putchar(st[tot]);
			tot++;
		}
		printf("\n");
	}
	return 0;
}

int drawfeld(char *st, int heigth, int length)
{
	int fb0 = open("/dev/fb0", O_RDWR);
	
	drawrect(0, 255, 255, 0, 0, 1, fb0);
	clear(0, 0, 0, fb0);
	int tot = 0;
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < length; x++)
		{
			switch (st[tot])
			{
				case '.':
					drawrect(100, 100, 100, x, y, heigth, fb0);
					break;
				case '#':
					drawrect(0, 250, 0, x, y, heigth, fb0);
					break;
				case '$':
					drawrect(250, 0, 0, x, y, heigth, fb0);
					break;
			}
			tot++;
		}
		//printf("\n");
	}
	return 0;
}

int updatesnake(listelement *snake, char *feld, int length, int heigth)
//1. Free the feld
//2. add the snake
{
	//free the feld
	int count = 0;
        for (int i = 0; i < heigth*length; i++)
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
		feld[(x+y)] = '#';
		snake = snake->next;
	}
	return 0;
}
