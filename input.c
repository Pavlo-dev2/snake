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

char input(float st)
{
	struct input_event ev;//event
	char dr = 0;//new ditection
	
	//open file deckriptor
	if (fd == -1)
	{
		fd = open(ADDRES, O_RDONLY | O_NONBLOCK);
	}

	long double bt = clock()/CLOCKS_PER_SEC;//begining time

	//wait on input as long as you have time
	//while ((st - (td = (clock()/CLOCKS_PER_SEC) - at)* 1000000) > 0)//TODO
	while (((clock()/CLOCKS_PER_SEC) - bt) < st)
	{
		//printf("Actual time: %ld\nBegining time: %f\nTime: %f\n", clock()/CLOCKS_PER_SEC, bt, st);
		read(fd, &ev, sizeof(ev));
		if (ev.type == EV_KEY)
		{
			switch (ev.code)
			{
				case KEY_W: dr = 'u'; break;
				case KEY_D: dr = 'r'; break;
				case KEY_S: dr = 'd'; break;
				case KEY_A: dr = 'l'; break;
				case KEY_E: dr = 'E'; break;
			}
			//break;
		}
		//printf("ST: %.0f\n", st);
		usleep(st*10);
	}

	if (dr != 0)
	{
		lastdr = dr;
	}

	return lastdr;
}
