#include "philo.h"
static int	death_checker(t_list *philo)
{
	while (philo)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		if (c_time(philo->data->time_start)
			- philo->last_dinner > philo->data->time_die)
		{
			philo->data->dead = philo->philo;
			pthread_mutex_unlock(&philo->data->mutex_dead);
			pthread_mutex_lock(&philo->data->mutex_print);
			printf(RED"[%lu ms] philo %d has died\n",
				c_time(philo->data->time_start), philo->philo + 1);
			pthread_mutex_unlock(&philo->data->mutex_print);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutex_dead);
		philo = philo->next;
	}
	return (0);
}

void	ft_start(t_list *philo)
{
	t_list	*temp;

	temp = philo;
	philo->data->time_start = ft_timer(0);
	while (temp)
	{
		pthread_create(&temp->thread, NULL, &ft_routine, (void *)temp);
		temp = temp->next;
	}
	temp = philo;
	while (1)
	{
		ft_usleep(philo, 1);
		if (death_checker(temp) == 1)
			exit(0);
		// if (temp->data->nbr_to_fin != -1 && all_ate(temp) == 1)
		// 	break ;
	}
	while (temp)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
}
