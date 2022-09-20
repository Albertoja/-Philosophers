/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:07:02 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:07:03 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate(t_list *philos)
{
	t_list	*temp;

	temp = philos;
	while (philos)
	{
		pthread_mutex_lock(&philos->mutex_ate);
		if (philos->nbr_ate < philos->data->n_eat)
		{
			pthread_mutex_unlock(&philos->mutex_ate);
			return (0);
		}
		pthread_mutex_unlock(&philos->mutex_ate);
		philos = philos->next;
	}
	pthread_mutex_lock(&temp->data->mutex_dead);
	temp->data->dead = -2;
	pthread_mutex_unlock(&temp->data->mutex_dead);
	return (1);
}

static int	death_checker(t_list *philos)
{
	while (philos)
	{
		pthread_mutex_lock(&philos->data->mutex_dead);
		if (c_time(philos->data->time_start) - philos->last_dinner > philos->data->time_die)
		{
			philos->data->dead = philos->philo;
			pthread_mutex_unlock(&philos->data->mutex_dead);
			pthread_mutex_lock(&philos->data->mutex_print);
			printf(RED"[%lu ms] philo %d has died\n",
				c_time(philos->data->time_start), philos->philo + 1);
			pthread_mutex_unlock(&philos->data->mutex_print);
			return (1);
		}
		pthread_mutex_unlock(&philos->data->mutex_dead);
		philos = philos->next;
	}
	return (0);
}

void	ft_start(t_list *philo)
{
	t_list	*temp;
	int nbr_ate;

	nbr_ate = 0;
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
			break ;
		if (temp->data->n_eat != -1 && all_ate(temp) == 1)
			break ;
	}
	while (temp)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
}
