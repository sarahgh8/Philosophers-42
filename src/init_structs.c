/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:32 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:22:28 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * This fucntion parse the arguments into useful values
 * by intializing them and assigning their values in the global struct
 * shared by all of the threads
 *
 * @param g The global struct of the type t_global
 * @param argv The arguments
 * @param argc number of the arguments
 */
int	init_global(t_global *g, char **argv, int argc)
{
	int	i;

	i = -1;
	g->philo_num = ft_atoi(argv[1]);
	g->die_time = ft_atoi(argv[2]);
	g->eat_time = ft_atoi(argv[3]);
	g->sleep_time = ft_atoi(argv[4]);
	g->done_eating = 0;
	g->stop_sim = 0;
	g->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	g->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!g->philos || !g->forks)
		return (1);
	if (argc == 6)
		g->meals_num = ft_atoi(argv[5]);
	else
		g->meals_num = -1;
	while (++i < g->philo_num)
		pthread_mutex_init(&g->forks[i], NULL);
	pthread_mutex_init(&g->print, NULL);
	pthread_mutex_init(&g->stop_sim_m, NULL);
	pthread_mutex_init(&g->done_eating_m, NULL);
	return (0);
}

/**
 * This fucntion intialize the philosophers info
 * @param g global struct of the type t_global
 */
void	init_philos(t_global *g)
{
	int		i;

	i = -1;
	while (++i < g->philo_num)
	{
		g->philos[i].id = i + 1;
		g->philos[i].left_f = (i + 1) % g->philo_num;
		g->philos[i].right_f = i;
		g->philos[i].meals_num_p = 0;
		g->philos[i].last_meal = 0;
		g->philos[i].global_info = g;
		pthread_mutex_init(&g->philos[i].meals_num_m, NULL);
	}
}
