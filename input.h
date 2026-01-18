#ifndef INPUT_H
#define INPUT_H

int retfd(char type, char num);
//returns file deckriptor;
//type - type of the deckriptor, 0: Blocking, 1: Nonblocking;
//num - number of the /dev/input/event* file;

int ifevent(int fd, int keynum, char evval, long double time);
//returns 1 if event with code keynum and value evtype hapend, else 0;
//waits time second if nonblocking;
//if time == -1 wait until event hapend

int* ifevents(int fd, void *events, char type, long double time);
//events - array of intger arrays, 2 element ech, code of key and value of the event;
//returns event([code, value])if event from events hapend, else NULL;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;

int ifeventscode(int fd, int *events, long arrlen, char type, long double time);
//events - array of intgers, codes of keys;
//returns event code if event from events hapend(key pressed or let), else -1;
//type - type of shering, 0 for first event, 1 for last;
//waits time seconds if nonblocking;
//if events == NULL reacts to all of events;

int ifeventsvalue(int fd, int eventsvalue, char type, long double, int *ignor, long arrlen);
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

#endif 
