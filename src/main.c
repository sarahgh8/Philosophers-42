/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:52:19 by sarahgh8          #+#    #+#             */
/*   Updated: 2025/06/07 19:23:16 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * This function is a full checker that checks all the cases for the arguments
 * and validate them
 * 1. it checks the number of the arguments
 * 2. it checks whether they only contain digits greater than zero or not
 *
 * @param argv the arguments that need to be checked
 * @param argc the number of arguments

	* @return it returns 1 in case of success
        (all the arguments match the requirments),
	    and returns 0 after printing
 *          the error message suitable for the enum passed
 */
int	check_args(char **argv, int argc)
{
	t_error	err_type;
	int		i;
	int		temp_num;

	i = 0;
	err_type = DEFAULT;
	if (argc != 5 && argc != 6)
		err_type = WRONG_NUM;
	else if (!only_digits(argv))
		err_type = NOT_DIGIT;
	while (++i < argc)
	{
		temp_num = ft_atoi(argv[i]);
		if (temp_num > INT_MAX || temp_num == 0)
			err_type = NOT_VALID;
	}
	if (err_type != DEFAULT)
		return (print_err_msg(err_type));
	return (1);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (!check_args(argv, argc))
		return (1);
	if (init_global(&g, argv, argc))
		return (1);
	init_philos(&g);
	start_simulation(&g);
	end_all(&g);
	return (0);
}
