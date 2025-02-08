/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:14:48 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/08 19:24:00 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	check_starvation(t_info *info)
// {
// 	int	i;
// 	size_t	time;

// 	i = 0;
// 	while (i < info->num_of_philo)
// 	{
// 		pthread_mutex_lock(&info->philo[i].info->eat_mutex);
// 		time = current_time();
// 		if (time - info->philo[i].time_of_last_meal >= info->philo[i].info->time_die)
// 		{
// 			pthread_mutex_lock(&info->end_mutex);
// 			info->end = 1;
// 			pthread_mutex_unlock(&info->end_mutex);
// 			write_status(info->philo, "dead");
// 			pthread_mutex_unlock(&info->philo[i].info->eat_mutex);
// 			return (0);
// 		}
// 		pthread_mutex_unlock(&info->philo[i].info->eat_mutex);
// 		i++;
// 	}
// 	return (1);
// }

int	check_starvation(t_info *info)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		time = current_time();
		if (time - info->philo[i].time_of_last_meal > info->time_die)
		{
			pthread_mutex_lock(&info->end_mutex);
			info->end = 1;
			pthread_mutex_unlock(&info->end_mutex);
			write_status(&info->philo[i], "is dead");
			pthread_mutex_unlock(&info->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
	}
	return (1);
}

int	is_complated_eat(t_info *info)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (info->time_eat <= info->philo[i].eat_count)
			check++;
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
	}
	if (check == info->num_of_philo)
	{
		pthread_mutex_lock(&info->eat_done_mutex);
		info->eat_done = 1;
		pthread_mutex_unlock(&info->eat_done_mutex);
		write_status(&info->philo[i], "is full");
		return (0);
	}
	return (1);
}

int	is_still_alive(t_info *info)
{
	int i;

	i = 0;
	while(i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->end_mutex);
		pthread_mutex_lock(&info->eat_done_mutex);
		if (info->end == 1 || info->eat_done == 1)
		{
			pthread_mutex_unlock(&info->end_mutex);
			pthread_mutex_unlock(&info->eat_done_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->eat_done_mutex);
		pthread_mutex_unlock(&info->end_mutex);
		i++;
	}
	return (1);
}
void	check_philo(t_info *info)
{
	while (1)
	{
		if (!check_starvation(info) || !is_complated_eat(info))
			break ;
	}
}