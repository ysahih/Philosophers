#include "philo.h"

unsigned long	timeInMs(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int main(int argc, char* argv[])
{

	unsigned long now = timeInMs();
	struct timeval	time;
	gettimeofday(&time, NULL);
	printf("%ld\n", time.tv_sec);
//    while(true)
//    {
//    	sleep(1);
// 	printf("%lu\n", timeInMs() - now);
//    }
	return 0;
}
