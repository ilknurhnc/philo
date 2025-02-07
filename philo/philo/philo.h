/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:39 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/07 16:22:19 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	size_t					eat_count;
	int					eat_done;
	size_t				start_time;
	size_t				time_of_last_meal;
	pthread_t			thread;
	t_info				*info;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		eat_done_mutex;
	pthread_mutex_t		end_mutex;
}						t_philo;

typedef struct s_info
{
	int					num_of_philo;
	size_t					time_eat;
	size_t					time_die;
	size_t					time_sleep;
	int					num_meals;
	int					end;
	int					start;
	pthread_mutex_t		forks[200];
	t_philo 			philo[200];
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		eat_done_mutex;
	pthread_mutex_t		end_mutex;
}						t_info;


int	init_info(t_info *info, char **av);
int init_philo(t_info *info);
int init_forks(t_info *info);
int init_mutex(t_info *info);
void	check_philo(t_info *info);
int is_still_alive(t_philo *philo);
void	*life_cycle(void *arg);
void write_status(t_philo *philo, char *status);
long	ft_atol(char *str);
size_t	current_time(void);
void	ft_usleep(t_philo *philo, size_t ms);

#endif
