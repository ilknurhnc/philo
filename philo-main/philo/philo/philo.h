/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilknurhancer <ilknurhancer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:39 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/23 21:26:05 by ilknurhance      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	int				eat_count;
	size_t				start_time;
	size_t				time_of_last_meal;
	pthread_t			thread;
	t_info				*info;
}						t_philo;

typedef struct s_info
{
	int					num_of_philo;
	size_t				time_eat;
	size_t				time_die;
	size_t				time_sleep;
	int					num_meals;
	int eat_done;
	int					end;
	int					start;
	pthread_mutex_t		forks[200];
	t_philo				philo[200];
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		eat_done_mutex;
	pthread_mutex_t		end_mutex;
}						t_info;

int						init_info(t_info *info, char **av);
int						init_philo(t_info *info);
int						init_forks(t_info *info);
int						init_mutex(t_info *info);
void					check_philo(t_info *info);
int						is_still_alive(t_info *info);
void					*life_cycle(void *arg);
void					write_status(t_philo *philo, char *status);
long					ft_atol(char *str);
size_t					current_time(void);
void					ft_usleep(t_philo *philo, size_t ms);
int	check_starvation(t_info *info);
int	is_complated_eat(t_info *info);
void	finish_program(t_info *info);



#endif
