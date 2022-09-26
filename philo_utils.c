/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:06:56 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/26 16:20:52 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_usleep(t_list *philos, unsigned long int time)
{
	unsigned long int	slept;

	slept = ft_timer(philos->data->time_start);
	while (ft_timer(philos->data->time_start) - slept < time)
	{
		usleep(50);
		if (check_dead(philos) == 1)
			return (0);
	}
	return (0);
}
