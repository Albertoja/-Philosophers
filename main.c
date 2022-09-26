/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:06:47 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/26 17:09:43 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	t_input	*init_data_2(t_input *data)
{
	int		i;

	i = 0;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_eat, NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	i = 0;
	return (data);
}

static	t_input	*init_data(char **argv, int argc)
{
	t_input	*data;

	data = malloc(sizeof(t_input));
	data->time_start = 0;
	data->n_philo = ft_atoi_philo(argv[1]);
	data->time_die = ft_atoi_philo(argv[2]);
	data->time_eat = ft_atoi_philo(argv[3]);
	data->time_sleep = ft_atoi_philo(argv[4]);
	data->dead = -1;
	if (argc == 6)
		data->n_eat = ft_atoi_philo(argv[5]);
	else
		data->n_eat = -1;
	data = init_data_2(data);
	return (data);
}

int	main(int argc, char **argv)
{
	t_input	*data;
	t_list	*philos;
	int		a;

	a = 1;
	if (argc < 5 || argc > 6)
		ft_error("Invalid arguments");
	while (argv[++a])
		if (ft_atoi_philo(argv[a]) == -1)
			ft_error("Invalid arguments");
	data = init_data(argv, argc);
	philos = create_lst_philo(data);
	ft_start(philos);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_eat);
	a = 0;
	while (++a < data->n_philo)
		pthread_mutex_destroy(&data->mutex_fork[a]);
	free(data->mutex_fork);
	free(data);
	ft_lstclear(philos);
	exit(0);
}
