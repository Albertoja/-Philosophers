#include "philo.h"
int	print_mutex(t_list *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%sPhilosopher %i%s\n", color, philo->philo, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
	return(0);
}

int	ft_eat(t_list *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]);
	//printf("%i%s%i\n", philo->philo, " coge el tenedor ", philo->left_fork);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->philo]);
	//printf("%i%s%i\n", philo->philo, " coge el tenedor ", philo->philo);
	if (print_mutex(philo, " is eating", GREEN) == 1)
		return (0);
	usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->philo]);
	return(0);
}

void	*ft_routine(void *temp)
{
	t_list	*philo;
	
	philo = (t_list *)temp;
	if (philo->philo % 2 != 0)
		sleep(1);
	while (1)
	{
		if (ft_eat(philo) == 1)
			return (0);
		if (print_mutex(philo, " is sleeping", BLUE) == 1)
			return (0);
		usleep(philo->data->time_sleep);
		if (print_mutex(philo, " is thinking", YELLOW) == 1)
			return (0);
		sleep(1);
	}
}
