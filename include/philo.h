/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghunmin <sghunmin@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:17:13 by sghunmin          #+#    #+#             */
/*   Updated: 2025/06/07 19:27:40 by sghunmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef enum e_error
{
	DEFAULT,
	NOT_DIGIT,
	NOT_VALID,
	WRONG_NUM
}					t_error;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	int				left_f;
	int				right_f;
	long			last_meal;
	int				meals_num_p;

	pthread_mutex_t	meals_num_m;

	struct s_global	*global_info;

}					t_philo;
typedef struct s_global
{
	int				philo_num;
	long			eat_time;
	long			die_time;
	long			sleep_time;
	int				meals_num;
	long			start_time;
	int				done_eating;
	int				stop_sim;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	stop_sim_m;
	pthread_mutex_t	done_eating_m;
	t_philo			*philos;

}					t_global;

int					print_err_msg(t_error err_type);
int					ft_atoi(char *str);
void				init_philos(t_global *g);
int					check_args(char **argv, int argc);
int					only_digits(char **argv);
int					take_forks(t_philo *philo);
void				print_status(t_philo *philo, char *msg);
void				release_forks(t_philo *philos);
long				gettimeinms(void);
void				end_all(t_global *g);
void				my_usleep(long time, t_global *g);
void				swap_forks(int *fork1, int *fork2);
void				print_status_death(t_philo *philo);
void				lock_done_eating(t_global *g);
int					init_global(t_global *g, char **argv, int argc);
int					get_stop_flag(t_philo *p);
void				lock_stop_sim(t_global *g);
int					get_done_eating(t_global *g);
void				start_simulation(t_global *g);
void				lock_last_meal(t_philo *philo);

#endif