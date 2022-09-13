#include "philo.h"
int	print_mutex(t_list *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%i%s\n", philo->philo, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
	return(0);
}

int	ft_eat(t_list *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]);
	printf("%i%s%i\n", philo->philo, " coge el tenedor ", philo->left_fork);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->philo]);
	printf("%i%s%i\n", philo->philo, " coge el tenedor ", philo->philo);
	if (print_mutex(philo, " is eating") == 1)
		return (0);
	usleep(philo->data->time_eat);
	if (print_mutex(philo, " end eating") == 1)
		return (0);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->philo]);
	return(0);
}

void	*ft_routine(void *temp)
{
	t_list	*philo;
	
	write(1, "aqui2\n", 6);
	philo = (t_list *)temp;
	if (philo->philo % 2 != 0)
		sleep(1);
	while (1)
	{
		if (ft_eat(philo) == 1)
			return (0);
		if (print_mutex(philo, " is sleeping") == 1)
			return (0);
		usleep(philo->data->time_sleep);
		if (print_mutex(philo, " is thinking") == 1)
			return (0);
		sleep(1);
	}
}
