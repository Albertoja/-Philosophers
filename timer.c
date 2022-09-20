/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:07:05 by aespinos          #+#    #+#             */
/*   Updated: 2022/09/20 21:25:22 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

unsigned long int	c_time(unsigned long int time_start)
{
	struct timeval		time;
	unsigned long int	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000) - time_start;
	return (ms);
}
