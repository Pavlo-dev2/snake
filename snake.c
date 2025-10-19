#include <stdio.h>
#include "linkedlistlib.h"

listelement *movesnake(char d, listelement *st, int x, int y, int length, int heigth, char apple)
//moves snake in direction d(u- up; r- rigth; d- down; l- left) appele 1 if hit apple, 0 if not;
//st == NULL if need to create new snake, returns NULL if hit the border;
{
	printf("Function started\n");
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
				new_y++;
				break;
			case 'd':
				new_y--;
				break;
			case 'r':
				new_x++;
				break;
			case 'l':
				new_x--;
				break;	
		}
	}
	printf("New cords: %d:%d\n", new_x, new_y);
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
	if (len(st) >= 3 && ((int*)(retel(st, 2)->el))[0] == new_x && ((int*)(retel(st, 2)->el))[1] == new_y)
	{
		printf("Ops!, wrong direction\n");
		printlist(st, ";", "\n");
		printf("\tLen: %ld\n\tPNX: %d\n\tNX: %d\n\tPNY: %d\n\tNY: %d\n", len(st), ((int*)(retel(st, 2)->el))[0], new_x, ((int*)(retel(st, 2)->el))[1], new_y);
		rmlist(st);
		return NULL;
	}
	return st;
}
