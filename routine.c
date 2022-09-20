/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:07:00 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:07:01 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	check_dead(t_list *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->dead != -1)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (0);
}

int	print_mutex(t_list *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (check_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_print);
		return (1);
	}
	printf("%s[%lu ms] philo %d ", color,
		c_time(philo->data->time_start), philo->philo + 1);
	printf("%s\n"RESET, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
	return (0);
}

void	ft_eat(t_list *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->last_dinner = c_time(philo->data->time_start);
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->mutex_ate);
	philo->nbr_ate++;
	pthread_mutex_unlock(&philo->mutex_ate);
	ft_usleep(philo, philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->philo]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
}

int	start_eating(t_list	*philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left_fork]);
	print_mutex(philo, " has taken a fork", RESET);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->philo]);
	print_mutex(philo, " has taken a fork", RESET);
	if (print_mutex(philo, " is eating", GREEN) == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->philo]);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->left_fork]);
		return (1);
	}
	ft_eat(philo);
	return (0);
}

void	*ft_routine(void *temp)
{
	t_list	*philo;
	
	philo = (t_list *)temp;
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->last_dinner = c_time(philo->data->time_start);
	pthread_mutex_unlock(&philo->data->mutex_dead);
	if (philo->philo % 2 != 0)
		ft_usleep(philo, 20);
	while (1)
	{
		if (start_eating(philo) == 1)
			return (0);
		if (print_mutex(philo, " is sleeping", BLUE) == 1)
			return (0);
		ft_usleep(philo, philo->data->time_sleep);
		if (print_mutex(philo, " is thinking", YELLOW) == 1)
			return (0);
		//sleep(1);
	}
}
