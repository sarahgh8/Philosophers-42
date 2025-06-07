/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:27 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:33:08 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * This function converts the current time to milliseconds
 * @return returns the time after converting it to milliseconds
 */
long	gettimeinms(void)
{
	struct timeval	time;
	long			my_time;

	gettimeofday(&time, NULL);
	my_time = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
	return (my_time);
}

/**
 * A customized usleep fucntion that sleep a certain amount of time
 * until the wanted time is reached
 * @param time the sleep duration
 */
void	my_usleep(long ms, t_global *g)
{
	long	start;

	start = gettimeinms();
	while (1)
	{
		pthread_mutex_lock(&g->stop_sim_m);
		if (g->stop_sim)
		{
			pthread_mutex_unlock(&g->stop_sim_m);
			return ;
		}
		pthread_mutex_unlock(&g->stop_sim_m);
		if (gettimeinms() - start >= ms)
			return ;
		usleep(100);
	}
}
