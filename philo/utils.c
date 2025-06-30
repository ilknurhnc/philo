/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:56:40 by ihancer           #+#    #+#             */
/*   Updated: 2025/06/21 14:39:56 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	size_t			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(size_t ms)
{
	size_t	time;

	time = get_current_time() + ms;
	while (get_current_time() < time)
		if (usleep(100) != 0)
			return ;
}

long	ft_atol(char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str[i])
		return (0);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_join(t_info *info, int i)
{
	if (info->num_of_philo == 1)
	{
		if (pthread_detach(info->philo[i].thread))
		{
			printf("Detach Error.\n");
			return (1);
		}
	}
	else
	{
		if (pthread_join(info->philo[i].thread, NULL))
		{
			printf("Join Error.\n");
			return (1);
		}
	}
	return (0);
}

int	write_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->t_info->write_mutex);
	pthread_mutex_lock(&philo->t_info->end_mutex);
	if (philo->t_info->end == false)
	{
		printf("%zu %d %s\n", get_current_time() - philo->t_info->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->t_info->write_mutex);
	pthread_mutex_unlock(&philo->t_info->end_mutex);
	return (0);
}
