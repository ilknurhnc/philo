/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:57:14 by ihancer           #+#    #+#             */
/*   Updated: 2025/06/30 16:21:17 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_program(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_current_time();
	while (++i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->philo[i].last_meal_mutex);
		info->philo[i].time_of_last_meal = get_current_time();
		pthread_mutex_unlock(&info->philo[i].last_meal_mutex);
		if (pthread_create(&info->philo[i].thread, NULL, loop,
				(void *)&info->philo[i]))
		{
			printf("Thread creation error.\n");
			return (1);
		}
		usleep(100);
	}
	dead_check(info);
	i = -1;
	while (++i < info->num_of_philo)
		if (ft_join(info, i))
			break ;
	return (0);
}

void	finish_program(t_info *info)
{
	int	i;

	i = -1;
	if (info->num_of_philo != 1)
	{
		while (++i < info->num_of_philo)
		{
			pthread_mutex_destroy(&info->forks[i]);
			pthread_mutex_destroy(&info->philo[i].last_meal_mutex);
		}
	}
	pthread_mutex_destroy(&info->end_mutex);
	pthread_mutex_destroy(&info->write_mutex);
}

static int	check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
		if (argv[1][0] == '0' || ft_atol(argv[1]) > 200)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_arg(argc, argv))
	{
		printf("Invalid argument! \n");
		return (1);
	}
	if (init_info(&info, argc, argv) || init_philo(&info) || init_forks(&info)
		|| init_mutex(&info))
	{
		printf("There are something that cannot be initialized\n");
		return (1);
	}
	start_program(&info);
	finish_program(&info);
}
