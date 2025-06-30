/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:57:24 by ihancer           #+#    #+#             */
/*   Updated: 2025/06/21 11:40:11 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philo[i].last_meal_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&info->end_mutex, NULL);
	pthread_mutex_init(&info->write_mutex, NULL);
	return (0);
}

int	init_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo - 1)
	{
		info->philo[i].left_fork = &info->forks[i];
		info->philo[i].right_fork = &info->forks[i + 1];
		i++;
	}
	info->philo[i].left_fork = &info->forks[i];
	info->philo[i].right_fork = &info->forks[0];
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].chair_no = i + 1;
		info->philo[i].eat_count = 0;
		info->philo[i].t_info = info;
		i++;
	}
	return (0);
}

int	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philo = ft_atol(argv[1]);
	info->time_die = ft_atol(argv[2]);
	info->time_eat = ft_atol(argv[3]);
	info->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->num_meals = ft_atol(argv[5]);
	else
		info->num_meals = -1;
	info->completed_philos = 0;
	info->end = false;
	return (0);
}
