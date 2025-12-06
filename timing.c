#include <time.h>
#include <stdio.h>

long double rettime();//return actual time sinse start of the timer
long double timediff(long double time1, long double time2);//return diferense in times(time2 - time1)
int sleepsec(long double time);//sleep time seconds

long double rettime()
//return actual time sinse start of the timer
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return (long double) (time.tv_sec + time.tv_nsec/1e9);
}

long double timediff(long double time1, long double time2)
//return diferense in times(time2 - time1)
{
	return time2 - time1;
}

int sleepsec(long double time)
//sleep time seconds
{
	struct timespec req;
	req.tv_sec = (time_t) time;
	req.tv_nsec = (long) ((time - req.tv_sec) * 1e9);
	nanosleep(&req, NULL);
	return 0;
}
