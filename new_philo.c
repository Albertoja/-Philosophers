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
	return(philo);
}
