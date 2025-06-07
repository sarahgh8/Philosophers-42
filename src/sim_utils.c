/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:31:03 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:42:20 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_done_eating(t_global *g)
{
	int	res;

	pthread_mutex_lock(&g->done_eating_m);
	res = g->done_eating;
	pthread_mutex_unlock(&g->done_eating_m);
	return (res);
}

int	get_stop_flag(t_philo *p)
{
	t_global	*g;
	int			res;

	g = p->global_info;
	pthread_mutex_lock(&g->stop_sim_m);
	res = g->stop_sim;
	pthread_mutex_unlock(&g->stop_sim_m);
	return (res);
}

void	lock_done_eating(t_global *g)
{
	pthread_mutex_lock(&g->done_eating_m);
	g->done_eating++;
	pthread_mutex_unlock(&g->done_eating_m);
}

void	lock_stop_sim(t_global *g)
{
	pthread_mutex_lock(&g->stop_sim_m);
	g->stop_sim = 1;
	pthread_mutex_unlock(&g->stop_sim_m);
}

void	lock_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_num_m);
	philo->last_meal = gettimeinms() - philo->global_info->start_time;
	pthread_mutex_unlock(&philo->meals_num_m);
}
