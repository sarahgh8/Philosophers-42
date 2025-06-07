/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:21 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:25:30 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * This fucntion prints a customized error msg
 * @param err_type an enum data type that has the error types
 * @return always returns 0,
	cuz this function is only called when there's an error
 */

int	print_err_msg(t_error err_type)
{
	if (err_type == WRONG_NUM)
		printf("Arguments must be 4 or 5\n");
	else if (err_type == NOT_DIGIT)
		printf("Arguments must only have digits\n");
	else if (err_type == NOT_VALID)
		printf("Number is not valid\n");
	return (0);
}

/**
 * This fucntion prints the status of the thread in this format
 * [Timestamp] [thread ID] [Status]
 * with a mutex to prevent data races
 *
 * @param philo a struct with philos info
 * @param msg a string contains the thread's status
 */
void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!philo->global_info->stop_sim)
	{
		timestamp = gettimeinms() - philo->global_info->start_time;
		pthread_mutex_lock(&philo->global_info->print);
		printf("%ld %d %s\n", timestamp, philo->id, msg);
		pthread_mutex_unlock(&philo->global_info->print);
	}
}

void	print_status_death(t_philo *philo)
{
	long	timestamp;

	timestamp = gettimeinms() - philo->global_info->start_time;
	pthread_mutex_lock(&philo->global_info->print);
	printf("%ld %d %s\n", timestamp, philo->id, "died");
	pthread_mutex_unlock(&philo->global_info->print);
}
