/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:35 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:21:28 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	release_forks(t_philo *philos)
{
	pthread_mutex_unlock(&philos->global_info->forks[philos->left_f]);
	pthread_mutex_unlock(&philos->global_info->forks[philos->right_f]);
}

/**
 * This fucntion destroys all used mutexes to keep the program clean
 * @param g a struct pointer that points to global shared info
 */
void	end_all(t_global *g)
{
	int		i;

	i = 0;
	while (i < g->philo_num)
		pthread_mutex_destroy(&g->forks[i++]);
	pthread_mutex_destroy(&g->print);
	pthread_mutex_destroy(&g->stop_sim_m);
	pthread_mutex_destroy(&g->done_eating_m);
	i = 0;
	while (i < g->philo_num)
		pthread_mutex_destroy(&g->philos[i++].meals_num_m);
	free(g->forks);
	free(g->philos);
}
