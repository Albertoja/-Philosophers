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
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex_fork[i], NULL);
		i++;
	}
	return(data);
}

int main(int argc, char **argv)
{
	t_input	*data;
	t_list	*philos;
	int		a;

	a = 1;
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
}
