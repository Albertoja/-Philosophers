#include "philo.h"

void	ft_start(t_list *philo)
{
	t_list	*temp;

	temp = philo;
	while (temp)
	{
		pthread_create(&temp->thread, NULL, &ft_routine, (void *)temp);
		temp = temp->next;
	}
	temp = philo;
	while (temp)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
}
