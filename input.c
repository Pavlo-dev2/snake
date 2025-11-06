#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>

#define ADDRES "/dev/input/event2"

/*struct input_event ev;

char input()
{
	static char dr = 'u';
	int fd = open(ADDRES, O_RDONLY | O_NONBLOCK);
	//int fd = open(ADDRES, O_RDONLY);
	int code = 0;
	while(1)
	{
		printf("Before raed\n");
		read(fd, &ev, sizeof(ev));
		printf("After read\nCon2: %d\n", ev.type == EV_KEY);
		if (fd > -1 && ev.type == EV_KEY)
		{
			printf("In 1;\n");
			switch(ev.code)
			{
				case 17:
					dr = 'u';
					break;
				case 32:
					dr = 'r';
					break;
				case 31:
					dr = 'd';
					break;
				case 30:
					dr = 'l';
					break;
				case 18:
					return 'E';
			}
		}
		else if (fd == -1 && errno == EAGAIN)
		{
			printf("In 2;\n");
			close(fd);
			return dr;
		}
		close(fd);
		printf("Dr: %c\nfd: %d\n", dr, fd);
		//return dr;
		return dr;
	}
}*/

static int fd = -1;
static char lastdr = 'u';

char input(float *st)
{
	struct input_event ev;
	char dr = 0;
	fd = open(ADDRES, O_RDONLY | O_NONBLOCK);
	//fd = open(ADDRES, O_RDONLY);
	//while (read(fd, &ev, sizeof(ev)) == sizeof(ev))
	float time = clock()/CLOCKS_PER_SEC;
	float td = 0;
	while ((td = clock()/CLOCKS_PER_SEC - time) < 1)//TODO
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
				}
				break;
			//}
		}
	}

	if (dr != 0)
	{
		lastdr = dr;
	}
	//*st = *st - td/1000000;//TODO
	printf("Message 4, dr: %c dr == 0: %d\n", dr, dr == 0);
	return lastdr;
}
