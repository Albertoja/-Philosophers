/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:07:05 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/26 17:01:42 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

unsigned long int	ft_timer(unsigned long int time_start)
{
	struct timeval		time;
	unsigned long int	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000) - time_start;
	return (ms);
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

void	ft_lstclear(t_list *philos)
{
	t_list	*temp;

	temp = philos;
	while (temp)
	{
		philos = temp;
		temp = temp->next;
		pthread_mutex_destroy(&philos->data->mutex_eat);
		free(philos);
	}
}

static unsigned long long int	ft_check(unsigned long long int result, int sig)
{
	if (result > 9223372036854775807 && sig < 0)
		return (0);
	else if (result > 9223372036854775807 && sig > 0)
		return (-1);
	else
		return (result);
}

int	ft_atoi_philo(const char *str)
{
	int						x;
	int						sig;
	unsigned long long int	result;
	{
		x = 0;
		sig = 1;
		result = 0;
		while (str[x] == ' ' || str[x] == '\t' || str[x] == '\n'
			|| str[x] == '\v' || str[x] == '\f' || str[x] == '\r')
			x++;
		while (str[x] == '+' || str[x] == '-')
		{
			if (str[x] == '-')
				sig = sig * (-1);
			if (str[x + 1] == '+' || str[x + 1] == '-')
				return (0);
			x++;
		}
		while (str[x] >= '0' && str[x] <= '9')
			result = (str[x++] - 48) + (result * 10);
		if (str[x] && (str[x] < '0' || str[x] > '9'))
			return (-1);
		return ((int)ft_check(result, sig) * sig);
	}
}
