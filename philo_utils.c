/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:06:56 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:25:57 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_philo(const char *str)
{
	unsigned long long int	ans;
	int						sign;

	ans = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
	{
		sign *= -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (*str > 47 && *str < 58)
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	if (ans > 9223372036854775807 && sign < 0)
		return (0);
	else if (ans > 9223372036854775807 && sign > 0)
		return (-1);
	return ((int)(ans * sign));
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*a;

	if (lst || new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		a = ft_lstlast(*lst);
		a->next = new;
	}
	else
		return ;
}

t_list	*ft_lstnew(int philo)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	(list)->philo = philo;
	(list)->next = NULL;
	return (list);
}

unsigned long int	c_time(unsigned long int time_start)
{
	struct timeval		time;
	unsigned long int	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000) - time_start;
	return (ms);
}

int	ft_usleep(t_list *philos, unsigned long int time)
{
	unsigned long int	slept;

	slept = c_time(philos->data->time_start);
	while (c_time(philos->data->time_start) - slept < time)
	{
		usleep(50);
		if (check_dead(philos) == 1)
			return (0);
	}
	return (0);
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
		pthread_mutex_destroy(&philos->mutex_ate);
		free(philos);
	}
}
