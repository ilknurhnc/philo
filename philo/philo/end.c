/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:14:48 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/05 06:28:32 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (!is_ate(&info->philo[i]))
		{
			pthread_mutex_lock(&info->end_mutex);
			info->end = 1;
			pthread_mutex_unlock(&info->end_mutex);
			write_message(info->philo, "dead");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_complated_eat(t_info *info)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (info->time_eat == -1)
		return (1);
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		if (info->time_eat <= info->philo[i]->eat_num)
			check++;
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
	}
	if (check == info->num_of_philo)
	{
		pthread_mutex_lock(&info->eat_done_mutex);
		info->philo[0]->eat_done = 1;
		pthread_mutex_unlock(&info->eat_done_mutex);
		return (0);
	}
	return (1);
}
void check_philo(t_philo *philo)
{
	while (1)
	{
		if (!is_dead(info) || !is_complated_eat(info))
			break ;
	}
}