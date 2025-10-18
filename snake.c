#include <stdio.h>
#include "linkedlistlib.h"

listelement *movesnake(char d, listelement *st, int x, int y, int length, int heigth, char apple)
//moves snake in direction d(u- up; r- rigth; d- down; l- left) appele 1 if hit apple, 0 if not;
//st == NULL if need to create new snake, returns NULL if hit the border;
{

	//count new cords
	int new_x, new_y;
	if (st == NULL)
	{
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
		return NULL;
	}
	int cords_arr[] = {new_x, new_y};
	st = append(cords_arr, 2, 'i', st, 0);
	//printf("St pointer: %p, %d\n", st, st != NULL);
	//printel(st, ";\n");
	if (len(st) >= 3 && ((int*)(retel(st, 2)->el))[0] == new_x && ((int*)(retel(st, 2)->el))[1])
	{
		printf("Ops!, wrong direction\n");
		return NULL;
	}
	return st;
}
