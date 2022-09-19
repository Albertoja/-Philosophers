#include"philo.h"

unsigned long int ft_timer(unsigned long int pretime)
{
	struct timeval	timer;
	unsigned long int ms;


	gettimeofday(&timer, NULL);
	ms = (timer.tv_sec * 1000) + (timer.tv_usec / 1000) - pretime;

	return(ms);
}

