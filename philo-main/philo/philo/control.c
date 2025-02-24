/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:14:48 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/24 19:10:22 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_unlock(&info->eat_mutex);
			pthread_mutex_lock(&info->end_mutex);
			info->end = 1;
			pthread_mutex_unlock(&info->end_mutex);
			write_status(&info->philo[i], "died");
			
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
	if(info->num_meals != -1)
	{
		while (i < info->num_of_philo)
		{
			pthread_mutex_lock(&info->eat_mutex);
			if (info->num_meals <= info->philo[i].eat_count)
				check++;
			pthread_mutex_unlock(&info->eat_mutex);
			i++;
		}
		if (check == info->num_of_philo)
		{
			pthread_mutex_lock(&info->end_mutex);
			info->end = 1;
			pthread_mutex_unlock(&info->end_mutex);
			return (0);
		}
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