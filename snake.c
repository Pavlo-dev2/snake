#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlistlib.h"

listelement *movesnake(char d, listelement *st, int x, int y, int length, int heigth, char apple);
//moves snake in direction d(u- up; r- rigth; d- down; l- left) appele 1 if hit apple, 0 if not;
//st == NULL if need to create new snake, returns NULL if hit the border;

int checksnake(listelement *snake);
//chesk if snake hit itselve, 1 if true, 0 if not

int createapple(char *feld, int length, int heigth, int snakelen, int r);
//create and print  new apple if r == -1 or print old one if not

int checkapple(listelement *snake, int apple, int length);
//chek is snake hit the apple, 1 if true, 0 if not

listelement *movesnake(char d, listelement *st, int x, int y, int length, int heigth, char apple)
{
	char p = 0;//flag, if st was NULL

	//count new cords
	int new_x, new_y;
	if (st == NULL)
	{
		printf("ST = NULL\n");
		p = 1;
		new_y = y;
		new_x = x;
	}
	else
	{
		new_x = ((int*)(retel(st, 0)->el))[0];
		new_y = ((int*)(retel(st, 0)->el))[1];
		switch(d)
		{
			case 'u':
				new_y--;
				break;
			case 'd':
				new_y++;
				break;
			case 'r':
				new_x++;
				break;
			case 'l':
				new_x--;
				break;	
		}
	}
	if (new_x < 0 || new_y < 0 || new_x > 15 || new_y > 15)
	{
		printf("You hit the border...\n");
		printel(retel(st, 0), "; ");
		printf("\n");
		rmlist(st);
		return NULL;
	}
	int cords_arr[] = {new_x, new_y};
	st = append(cords_arr, 2, 'i', st, 0);
	if ((!apple) && !p)
	{
		st = pop(st, -1);
	}
	return st;
}

int checksnake(listelement *snake)
//chesk if snake hit itselve, 1 if true, 0 if not
{
	int tot, act, length;
	length = len(snake);
	tot = act = 0;
	while (tot < length)
	{
		int totvelx = *(int*)(retel(snake, tot)->el);
		int totvely = ((int*)(retel(snake, tot)->el))[1];
		listelement actel;
		for (act = tot+1; act < length; act++)
		{
			actel = *retel(snake, act);
			if (totvelx == *(int*)actel.el && totvely == ((int*)actel.el)[1])
			{
				return 1;
			}
		}
		tot++;
	}
	return 0;
}

int createapple(char *feld, int length, int heigth, int snakelen, int r)
//create new apple if r == -1 or print old one if not
{
	if (r == -1)
	{
		int avpos[length*heigth-snakelen], i, p;//availible possions
		for (i = 0, p = 0; i < length*heigth; i++)
		{
			if (feld[i] != '#') 
			{
				avpos[p] = i;
				p++;
			}
		}

		r = (rand() % length*heigth-snakelen + 1);//chouse random availible possion
		while (r < 0)
		{
			r = (rand() % length*heigth-snakelen + 1);
		}
		
		//add apple on feld
		feld[(avpos[r])] = '$';
		return avpos[r];
	}
	feld[r] = '$';
	return r;
}

int checkapple(listelement *snake, int apple, int length)
//chek is snake hit the apple, 1 if true, 0 if not
{
	if (snake != NULL && ((*(int*)snake->el) + (length)*(((int*)(snake->el))[1])) == apple)
	{
		return 1;
	}
	return 0;
}
