#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>

#define ADDRES "/dev/input/event2"

static int fd = -1;//file deckriptor
static char lastdr = 'u';//last direction

char input(float *st)
{
	struct input_event ev;//event
	char dr = 0;//new ditection
	
	//open file deckriptor
	if (fd == -1)
	{
		fd = open(ADDRES, O_RDONLY | O_NONBLOCK);
	}

	float td = 0;
	float at = clock()/CLOCKS_PER_SEC;

	//wait on input as long as you have time
	while ((*st - (td = (clock()/CLOCKS_PER_SEC) - at)* 1000000) > 0)//TODO
	{
		read(fd, &ev, sizeof(ev));
		//printf("Message 1\n");
		if (ev.type == EV_KEY)
		{
			printf("Message 2\n");
			//if (ev.value == 1)
			//{
				printf("Message 3\n");
				switch (ev.code)
				{
					case KEY_W: dr = 'u'; break;
					case KEY_D: dr = 'r'; break;
					case KEY_S: dr = 'd'; break;
					case KEY_A: dr = 'l'; break;
					case KEY_E: dr = 'E'; break;
				}
				break;
			//}
		}
	}

	if (dr != 0)
	{
		lastdr = dr;
	}

	if (*st-td*1000000 > 0)
	{
		*st = *st - td*1000000;
	}
	else
	{
		*st = 0;
	}
	printf("Message 4, dr: %c dr == 0: %d\n", dr, dr == 0);
	return lastdr;
}
