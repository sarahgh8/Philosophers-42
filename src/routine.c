/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:24 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:35:19 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * This fucntion gives every thread 2 mutexes,
	which in our case are called forks
 * each thread takes 2 forks, so that is 2 mutexes
 * it gives the threads with odd IDs the priority of taking the forks first
 * to prevent deadlocks, by making the threads with even IDs wait
 *
 * @param philo a struct that holds each philo info
 */
int	take_forks(t_philo *philo)
{
	int	first_f;
	int	second_f;

	if (philo->id % 2 == 0)
		usleep(100);
	first_f = philo->left_f;
	second_f = philo->right_f;
	if (first_f > second_f)
		swap_forks(&first_f, &second_f);
	pthread_mutex_lock(&philo->global_info->forks[first_f]);
	print_status(philo, "\033[38;5;225mhas taken a fork\033[0m");
	if (philo->global_info->philo_num == 1)
	{
		pthread_mutex_unlock(&philo->global_info->forks[first_f]);
		return (1);
	}
	pthread_mutex_lock(&philo->global_info->forks[second_f]);
	print_status(philo, "\033[38;5;225mhas taken a fork\033[0m");
	return (0);
}
