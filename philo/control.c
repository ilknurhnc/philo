/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:22:30 by ihancer           #+#    #+#             */
/*   Updated: 2025/05/12 00:09:23 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_starvation(t_info *info)
{
	int	j;

	j = 0;
	while (j < info->num_of_philo)
	{
		pthread_mutex_lock(&info->philo[j].last_meal_mutex);
		pthread_mutex_lock(&info->end_mutex);
		if ((get_current_time()
				- info->philo[j].time_of_last_meal) > info->time_die
			&& !info->end)
		{
			pthread_mutex_unlock(&info->end_mutex);
			write_status(&info->philo[j], "died");
			pthread_mutex_lock(&info->end_mutex);
			info->end = true;
			pthread_mutex_unlock(&info->philo[j].last_meal_mutex);
			pthread_mutex_unlock(&info->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->philo[j].last_meal_mutex);
		pthread_mutex_unlock(&info->end_mutex);
		j++;
	}
}

void	dead_check(t_info *info)
{
	pthread_mutex_lock(&info->end_mutex);
	while (info->end == false)
	{
		pthread_mutex_unlock(&info->end_mutex);
		check_starvation(info);
		pthread_mutex_lock(&info->end_mutex);
	}
	pthread_mutex_unlock(&info->end_mutex);
}
