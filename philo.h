/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:06:58 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:19:53 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/time.h>
# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

typedef struct s_input {
	int					n_philo;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	int					n_eat;
	unsigned int		die_aux;
	unsigned long int	time_start;
	int					dead;
	char				*forks;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		*mutex_eat;

}	t_input;

typedef struct s_list {
	pthread_t			thread;
	pthread_mutex_t		mutex_ate;
	int					nbr_ate;
	int					philo;
	int					left_fork;
	unsigned long int	last_dinner;
	struct s_input		*data;
	struct s_list		*next;

}	t_list;

typedef struct s_all {
	t_input		input;
	pthread_t	thread;

}	t_all;

int					ft_atoi_philo(const char *str);
void				ft_error(char *str);
void				philo_init(t_all all);
t_list				*create_lst_philo(t_input *data);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				*ft_routine(void *s);
void				ft_start(t_list *philo);
unsigned long int	c_time(unsigned long int time_start);
int					ft_usleep(t_list *philos, unsigned long int time);
int					check_dead(t_list *philos);
size_t				ft_strlen(const char *str);
unsigned long int	ft_timer(unsigned long int pretime);
void				ft_lstclear(t_list *lst);

#endif
