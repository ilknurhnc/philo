#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	last_meal_mutex;
	size_t			time_of_last_meal;
	int				eat_count;
	int				chair_no;
	bool is_done;
	struct s_info	*t_info;

}					t_philo;

typedef struct s_info
{
	int				num_of_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				num_meals;
	size_t			start_time;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	int				completed_philos;
	bool 				end;

}					t_info;

void				dead_check(t_info *info);
int					init_info(t_info *data, int argc, char **argv);
int					init_philo(t_info *info);
int					init_forks(t_info *info);
int					init_mutex(t_info *info);
void				*routine(void *arg);
void				life_cycle(t_philo *philo);
long				ft_atol(char *str);
void				ft_usleep(size_t ms);
size_t				get_current_time(void);
int					join(t_info *info, int i);
int					write_status(t_philo *philo, char *status);
int					start_program(t_info *info);

#endif