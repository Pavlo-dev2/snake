#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <sys/select.h>
#include "timing.h"

int retfd(char type, char num);
//returns file deckriptor;
//type - type of the deckriptor, 0: Blocking, 1: Nonblocking;
//num - number of the /dev/input/event* file;

int ifevent(int fd, int keynum, char evval, long double time);
//returns 1 if event with code keynum and value evtype hapend, else 0;
//waits time second if nonblocking;
//if time == -1 wait until event hapend

int* ifevents(int fd, void *events, char type, long double time);
//events - array of intger arrays, 2 element ech, code of key and value of the event, last element must be NULL;
//returns event([code, value])if event from events hapend, else NULL;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;

int ifeventscode(int fd, int *events, long arrlen, char type, long double time);
//events - array of intgers, codes of keys;
//returns event code if event from events hapend(key pressed or let), else -1;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;
//if events == NULL reacts to all of events;

int ifeventsvalue(int fd, int eventsvalue, char type, long double time, int *ignor, long arrlen);
//eventsvalue - value of event(0 or 1);
//returns event code if event with this value hapend(key pressed or let), else -1;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;
//if events == NULL reacts to all of events;
//ignor - array of codes that should be ignored:

int* ifanyevents(int fd, char type, long double time, void *ignor);
//returns event([code, value]) if any event hapend else &{-1, -1};
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;
//ignor - array of pointers to integer arrays([code, value]) that should be ignored, ends with NULL

static int ifinparr(int **arr, int *vel);
static int ifinarr(int *arr, long arrlen, int vel);

static long double sleeptime = 0.001;//time * sleeptime = waiting time;

int retfd(char type, char num)
{
	char addres[] = "/dev/input/event ";//16 - possion of the file number;
	addres[16] = '0' + num;
	int fd = -1;
	switch (type)
	{
		case 0:
			fd = open(addres, O_RDONLY);
			break;
		case 1:
			fd = open(addres, O_RDONLY | O_NONBLOCK);
			break;
	}
	return fd;
}

int ifevent(int fd, int keynum, char evval, long double time)
{
	struct input_event ev;
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		//printf("Type: %d Code: %d Value: %d\n", ev.type == EV_KEY, (int) ev.code, (int) ev.value);
		if (ev.type == EV_KEY && ev.code == keynum && (ev.value == evval || evval == 2))
		{
			return 1;
		}

	}
	return 0;

}

int* ifevents(int fd, void* events, char type, long double time)
{
	struct input_event ev;
	
	if (time == -1 && type != 0)
	{
		return NULL;//check
	}

	int last_event[2] = {-1, -1};//list with events that alredy hapend;

	int *nev = calloc(2, sizeof(int));//new event
	
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		nev[0] = ev.code;
		nev[1] = ev.value;
		if (ifinparr(events, nev))
		{
			if (type == 1)
			{
				last_event[0] = nev[0];
				last_event[1] = nev[1];
			}
			else if (type == 0)
			{
				return nev;
			}
		}
		sleepsec(sleeptime);
	}
	nev[0] = last_event[0];
	nev[1] = last_event[1];
	return nev;
}

int ifeventscode(int fd, int *events, long arrlen, char type, long double time)
{
	struct input_event ev;
	
	if (time == -1 && type != 0)
	{
		return -1;//check
	}

	int last_code = -1;//code of events that alredy hapend;

	int nec = -1;//new code;
	
	long double bt = rettime();//begining time;
	//float vel = 0;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		//printf("Vel: %f\n", vel);
		read(fd, &ev, sizeof(ev));
		nec = ev.code;
		for(int i = 0; i < arrlen; i++)
		{
			if (nec == events[i])
			{
				if (type == 1)
				{
					last_code = nec;
				}
				else if (type == 0)
				{
					return nec;
				}
			}
		}
		sleepsec(sleeptime);
	}
	return last_code;
}

int ifeventsvalue(int fd, int eventsvalue, char type, long double time, int *ignor, long arrlen)
{
	struct input_event ev;
	
	if (time == -1 && type != 0)
	{
		return -1;//check
	}

	int last_code = -1;//code of events that alredy hapend;

	int nec = -1;//new code;
	
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		nec = ev.code;
		if (ev.type == EV_KEY && (ignor == NULL || !(ifinarr(ignor, arrlen, nec))) && ev.value == eventsvalue)
		{
			if (type == 1)
			{
				last_code = nec;
			}
			else if (type == 0)
			{
				return nec;
			}
		}
		sleepsec(sleeptime);
	}
	return last_code;
}

int* ifanyevents(int fd, char type, long double time, void *ignor)
{
	//printf("Masseg 1\n");
	printf("ignor: %p\n", ignor);
	struct input_event ev;
	
	if (time == -1 && type != 0)
	{
		return NULL;//check
	}

	int last_event[2] = {-1, -1};//list with events that alredy hapend;

	int *nev = calloc(2, sizeof(int));//new event
	
	long double bt = rettime();//begining time;
	while (timediff(bt, rettime()) < time || time == -1)
	{
		read(fd, &ev, sizeof(ev));
		nev[0] = ev.code;
		nev[1] = ev.value;
		if (ev.type == EV_KEY && !(ifinparr(ignor, nev)))
		{
			if (type == 1)
			{
				last_event[0] = nev[0];
				last_event[1] = nev[1];
			}
			else if (type == 0)
			{
				return nev;
			}
		}
		sleepsec(sleeptime);
	}
	nev[0] = last_event[0];
	nev[1] = last_event[1];
	return nev;
}

static int ifinparr(int **arr, int *vel)
{
	if (arr == NULL)
	{
		return 0;
	}
	for(int i = 0; arr[i] != NULL; i++)
	{
		//if ((((int*)arr)[i])[0] == vel[0] && (((int*)arr)[i])[1] == vel[1])
		if (*(arr[i]) == vel[0] && *(arr[i]+1) == vel[1])
		{
			return 1;
		}
	}
	return 0;
}

static int ifinarr(int *arr, long arrlen, int vel)
{
	for(int i = 0; i < arrlen; i++)
	{
		if (arr[i] == vel)
		{
			return 1;
		}
	}
	return 0;
}

