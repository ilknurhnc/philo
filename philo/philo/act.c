/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilknurhancer <ilknurhancer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:16 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/24 10:57:05 by ilknurhance      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, char *status)
{
	
	pthread_mutex_lock(&philo->info->write_mutex);
	printf("%zu %d %s\n", current_time() - philo->start_time, philo->id, status);
	pthread_mutex_lock(&philo->info->eat_done_mutex);
	
	pthread_mutex_lock(&philo->info->end_mutex);
	if(philo->info->end == 1 || philo->info->eat_done == 1)
	{
		pthread_mutex_unlock(&philo->info->end_mutex);
		pthread_mutex_unlock(&philo->info->write_mutex);
		pthread_mutex_unlock(&philo->info->eat_done_mutex);
		finish_program(philo->info);
	}
	pthread_mutex_unlock(&philo->info->end_mutex);
	pthread_mutex_unlock(&philo->info->write_mutex);
	pthread_mutex_unlock(&philo->info->eat_done_mutex);
	return ;
}
static void	waiting(t_philo *philo)
{
		write_status(philo, "is sleeping");
		ft_usleep(philo, philo->info->time_sleep);
		write_status(philo, "is thinking");
	return ;
}
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	write_status(philo, "has taken a fork");
	write_status(philo, "is eating");
	pthread_mutex_lock(&philo->info->eat_mutex);
	philo->time_of_last_meal = current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->info->eat_mutex);
	ft_usleep(philo, philo->info->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo[0].info->num_of_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		philo->info->end = 1;
		return (arg);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1);
	while(philo->info->end != 1 || philo->info->eat_done != 1)
	{
		eating(philo);
		waiting(philo);
	}
	return arg;
}
