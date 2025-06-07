/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:17 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:30:35 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*is_done_eating(void *global)
{
	t_global	*g;

	g = (t_global *)global;
	while (1)
	{
		if (get_stop_flag(g->philos))
			return (0);
		pthread_mutex_lock(&g->done_eating_m);
		if (g->done_eating == g->philo_num)
		{
			pthread_mutex_unlock(&g->done_eating_m);
			pthread_mutex_lock(&g->stop_sim_m);
			g->stop_sim = 1;
			pthread_mutex_unlock(&g->stop_sim_m);
			return (0);
		}
		pthread_mutex_unlock(&g->done_eating_m);
	}
	return (0);
}

void	*is_dead(void *global)
{
	int			i;
	t_global	*g;
	long		current_time;

	g = (t_global *)global;
	while (1)
	{
		i = -1;
		if (get_done_eating(g))
			return (0);
		while (++i < g->philo_num)
		{
			current_time = gettimeinms() - g->start_time;
			pthread_mutex_lock(&g->philos[i].meals_num_m);
			if ((current_time - g->philos[i].last_meal) > g->die_time)
			{
				pthread_mutex_unlock(&g->philos[i].meals_num_m);
				lock_stop_sim(g);
				print_status_death(g->philos);
				return (0);
			}
			pthread_mutex_unlock(&g->philos[i].meals_num_m);
		}
	}
	return (0);
}

void	*start_routine(void *philos)
{
	t_philo		*philo;
	t_global	*g;

	philo = (t_philo *)philos;
	g = philo->global_info;
	while (!get_stop_flag(philo))
	{
		if (take_forks(philo))
			return (0);
		lock_last_meal(philo);
		print_status(philo, "\033[38;5;197mis eating\033[0m");
		my_usleep(g->eat_time, g);
		release_forks(philo);
		if (philo->global_info->meals_num > 0)
		{
			philo->meals_num_p++;
			if (philo->meals_num_p == g->meals_num)
				lock_done_eating(g);
		}
		print_status(philo, "\033[38;5;135mis sleeping\033[0m");
		my_usleep(g->sleep_time, g);
		print_status(philo, "\033[38;5;228mis thinking\033[0m");
		usleep(100);
	}
	return (NULL);
}

void	start_simulation(t_global *g)
{
	int			i;
	t_philo		*p;
	pthread_t	undertaker;
	pthread_t	waiter;

	p = g->philos;
	i = -1;
	g->start_time = gettimeinms();
	pthread_create(&undertaker, NULL, &is_dead, g);
	if (g->meals_num > 0)
		pthread_create(&waiter, NULL, &is_done_eating, g);
	while (++i < g->philo_num)
		pthread_create(&p[i].thread, NULL, &start_routine, &p[i]);
	i = 0;
	while (i < g->philo_num)
		pthread_join(p[i++].thread, NULL);
	pthread_join(undertaker, NULL);
	if (g->meals_num > 0)
		pthread_join(waiter, NULL);
}
