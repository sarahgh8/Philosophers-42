/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:55:30 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:34:24 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**

	* This function checks whether the arguments passed to
	it only contain digits or not

	* if there is a plus sign at the beginning of the number
	it skips it and checks for the other chars
 *
 * @param argv the arguments inputed while executing
 * @return returns 0 if one of the arguments doesn't only contain digits,
	1 if the argument is a number.
 */
int	only_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '+')
			j++;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * atoi() function re-implementation
 * @param str The number as a string
 * @return returns the string as an integer,
	if 0 whether there's an issue or the string passed is zero
 */
int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (sign * result);
}

void	swap_forks(int *fork1, int *fork2)
{
	int		temp;

	temp = *fork1;
	*fork1 = *fork2;
	*fork2 = temp;
}
