#include "philo.h"
static	t_input	*init_data(char **argv, int argc)
{
	t_input	*data;

	int	i;

	i = 0;
	data = malloc(sizeof(t_input));
	data->time_start = 0;
	data->n_philo = ft_atoi_philo(argv[1]);
	data->time_die = ft_atoi_philo(argv[2]);
	data->time_eat = ft_atoi_philo(argv[3]);
	data->time_sleep = ft_atoi_philo(argv[4]);
	data->dead = -1;
	data->die_aux = data->time_die;
	if (argc == 6)
		data->n_eat = ft_atoi_philo(argv[5]);
	else
		data->n_eat = -1;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->mutex_eat = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex_eat[i], NULL);
		i++;
	}
	return(data);
}

void leaks()
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_input	*data;
	t_list	*philos;
	int		a;
	t_list	*temp;
	int		n;

	//atexit(leaks);
	a = 1;
	n = 0;
	if (argc < 5 || argc > 6)
		ft_error("Invalid arguments");
	while (argv[a])
	{
		if (ft_atoi_philo(argv[a]) == -1)
			ft_error("Invalid arguments");
		a++;
	}
	data = init_data(argv, argc);
	philos = create_lst_philo(data);
	ft_start(philos);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_print);
	temp = philos;
	while (++n < data->n_philo)
		pthread_mutex_destroy(&data->mutex_fork[n]);
	free(data->forks);
	free(data->mutex_fork);
	free(data->mutex_eat);
	free(data);
	ft_lstclear(philos);
	exit(0);
}
