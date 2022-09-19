#include "philo.h"

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
		{
			result = (str[x] - 48) + (result * 10);
			x++;
		}
		if (str[x] && (str[x] < '0' || str[x] > '9'))
			return(-1);
		return ((int)ft_check(result, sig) * sig);
	}
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
