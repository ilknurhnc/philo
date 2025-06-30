/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:57:43 by ihancer           #+#    #+#             */
/*   Updated: 2025/06/21 13:18:19 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	write_status(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	write_status(philo, "is sleeping");
	ft_usleep(philo->t_info->time_sleep);
}

static void	eating(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->time_of_last_meal = get_current_time();
	philo->eat_count++;
	write_status(philo, "is eating");
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->t_info->time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	life_cycle(t_philo *philo)
{
	if (philo->chair_no % 2 == 0 || (philo->t_info->num_of_philo != 1
			&& philo->chair_no == philo->t_info->num_of_philo))
	{
		thinking(philo);
	}
	else
	{
		eating(philo);
		sleeping(philo);
	}
}

void	*loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->t_info->end_mutex);
		if (philo->t_info->end)
		{
			pthread_mutex_unlock(&philo->t_info->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->t_info->end_mutex);
		life_cycle(philo);
		pthread_mutex_lock(&philo->t_info->end_mutex);
		philo->chair_no = (philo->chair_no % philo->t_info->num_of_philo) + 1;
		if (philo->eat_count == philo->t_info->num_meals)
			philo->t_info->completed_philos++;
		if (philo->t_info->completed_philos >= philo->t_info->num_of_philo)
			philo->t_info->end = true;
		pthread_mutex_unlock(&philo->t_info->end_mutex);
	}
	return (NULL);
}
