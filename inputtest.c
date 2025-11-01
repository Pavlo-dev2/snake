#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define ADDRES "/dev/input/event2"

struct input_event ev;

int main()
{
	int fd = open(ADDRES, O_RDONLY);
	while(1)
	{
		read(fd, &ev, sizeof(ev));
		if (ev.type == EV_KEY && ev.value == 1)
		{
			printf("Code: %d\n", ev.code);
		}
	}
	close(fd);
}
