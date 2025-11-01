#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define ADDRES "/dev/input/event2"

struct input_event ev;

char input()
{
	static char dr = 'u';
	int fd = open(ADDRES, O_RDONLY);
	int code = 0;
	while(1)
	{
		printf("Before raed\n");
		read(fd, &ev, sizeof(ev));
		printf("After read\n");
		if (ev.type == EV_KEY)
		{
			switch(ev.code)
			{
				case 17:
					dr = 'u';
					return 'u';
				case 32:
					dr = 'r';
					return 'r';
				case 31:
					dr = 'd';
					return 'd';
				case 30:
					dr = 'l';
					return 'l';
				case 18:
					return 'E';
			}
		}
		printf("Dr: %c\n", dr);
		//return dr;
	}
	close(fd);
}
