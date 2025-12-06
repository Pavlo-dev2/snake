#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <sys/select.h>
#include "timing.h"

#define ADDRES "/dev/input/event2"

long double rettime();//return actual time sinse start of the timer
long double timediff(long double time1, long double time2);//return diferense in times(time2 - time1)
int sleepsec(long double time);//sleep time seconds

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

	long double bt = rettime();//begining time

	//wait on input as long as you have time
	//while ((st - (td = (clock()/CLOCKS_PER_SEC) - at)* 1000000) > 0)//TODO
	while (timediff(bt, rettime()) < st)
	{
		//printf("Actual time: %ld\nBegining time: %f\nTime: %f\n", clock()/CLOCKS_PER_SEC, bt, st);
		read(fd, &ev, sizeof(ev));
		if (ev.type == EV_KEY)
		{
			switch (ev.code)
			{
				case KEY_W:
					if (lastdr != 'd')
						dr = 'u'; break;
				case KEY_D:
					if (lastdr != 'l')
						dr = 'r'; break;
				case KEY_S:
					if (lastdr != 'u')
						dr = 'd'; break;
				case KEY_A:
					if (lastdr != 'r')
						dr = 'l'; break;
				case KEY_E:
					dr = 'E'; break;
			}
			//break;
		}
		//printf("ST: %.0f\n", st);
		sleepsec(st*0.001);
	}

	if (dr != 0)
	{
		lastdr = dr;
	}

	return lastdr;
}
