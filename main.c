#include <stdio.h>
#include <string.h>
#include "linkedlistlib.h"
#define HEIGTH 18
#define LENGTH 18

listelement *createfeld(int heigth, int length);
int printfeld(listelement *st, int height, int lenght);

int main(int argc, char *args[])
{
	listelement *feld = createfeld(HEIGTH, LENGTH);
	printfeld(feld, HEIGTH, LENGTH);
	rmlist(feld);
}

listelement *createfeld(int heigth, int length)
{
	listelement *st = NULL;
	char border[] = {'#', ' '};
	char empty[] = {' ', ' '};
	for(int i = 0; i < heigth; i++)
	{
		for(int e = 0; e < length; e++)
		{
			if (e == 0 || e == length-1 || i == 0 || i == length-1)
			{
				st = append(border, 2, 'c', st, -1);
			}
			else
			{
				st = append(empty, 2, 'c', st, -1);
			}
		}
	}
	return st;

}
int printfeld(listelement *st, int height, int length)
{
	int xd, yd, c;
	xd = yd = c = 0;
	while (yd < height)
	{
		while (xd < length)
		{
			printel(retel(st, c), "");
			xd++;
			c++;
		}
		xd = 0;
		yd++;
		printf("\n");
	}
	return 0;
}
