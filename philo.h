#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_input {
				int	n_philo;
	unsigned	int	time_die;
	unsigned	int	time_eat;
	unsigned	int	time_sleep;
	unsigned	int	n_eat;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_print;

}	t_input;

typedef struct s_list {
	pthread_t			thread;
	int					philo;
	int					left_fork;
	struct s_input		*data;
	struct s_list		*next;
}						t_list;

typedef struct s_all {
	t_input		input;
	pthread_t	thread;

}	t_all;

int	ft_atoi_philo(const char *str);
void	ft_error(char *str);
void	philo_init(t_all all);
t_list	*create_lst_philo(t_input *data);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_routine(void *s);
void	ft_start(t_list *philo);

#endif