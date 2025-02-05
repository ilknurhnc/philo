/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:39 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/05 03:54:42 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h> //gettimeofday

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	int					eat_num;
	int 				eat_done;
	size_t				start_time;
	size_t				time_of_last_meal;
	pthread_t			thread;
	t_info				info;
}						t_philo;

typedef struct s_info
{
	int					num_of_philo;
	int					time_eat;
	int					time_die;
	int					time_sleep;
	int					num_meals;
	int					end;
	int					start;
	pthread_mutex_t		*forks[200];
	t_philo				*philo[200];
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		eat_done_mutex;
	pthread_mutex_t		end_mutex;
	;

}						t_info;

int						init_info(t_info info, char **av);
int						init_forks(t_info info);
int						init_mutex(t_info info);
int						init_philo(t_info info);
long					ft_atol(char *str);
size_t					current_time(void);
void					ft_usleep(t_philo *philo, size_t ms);

#endif
