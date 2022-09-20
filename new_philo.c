/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:06:54 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:16:09 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*create_philo(int nbr, t_input *data)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	if (!philo)
		return (NULL);
	philo->philo = nbr;
	if (nbr == 0)
		philo->left_fork = data->n_philo - 1;
	else
		philo->left_fork = nbr - 1;
	philo->data = data;
	philo->next = NULL;
	return (philo);
}

t_list	*create_lst_philo(t_input *data)
{
	t_list	*philo;
	int		aux;

	aux = 0;
	philo = create_philo(aux++, data);
	while (aux < data->n_philo)
		ft_lstadd_back(&philo, create_philo(aux++, data));
	return (philo);
}
