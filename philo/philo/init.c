/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:55:45 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/08 19:11:35 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int init_philo(t_info *info)
// {
//     int i;

//     i = 0;
//     while (i < info->num_of_philo)
//     {
//         info->philo[i].id = i + 1;
//         info->philo[i].eat_count = 0;
//         info->philo[i].eat_done = 0;
//         info->philo[i].start_time = current_time();
//         info->philo[i].time_of_last_meal = current_time();
//         info->philo[i].right_fork = &info->forks[i]; // Sağ çatal: kendi indeksi
//         if (i == 0)
//             info->philo[i].left_fork = &info->forks[info->num_of_philo - 1]; // İlk filozof için sol çatal: son filozofun çatalı
//         else
//             info->philo[i].left_fork = &info->forks[i - 1]; // Diğer filozoflar için sol çatal: bir önceki filozofun çatalı
//         i++;
//     }
//     return (0);
// }

int init_philo(t_info *info)
{
    int i;

    i = 0;
    while (i < info->num_of_philo)
    {
        info->philo[i].id = i + 1;
        info->philo[i].eat_count = 0;
        info->philo[i].start_time = current_time();
        info->philo[i].time_of_last_meal = current_time();
        info->philo[i].left_fork = &info->forks[i];

        // if (i == 0)
        //     info->philo[i].right_fork = &info->forks[info->num_of_philo - 1];
        // else
        //     info->philo[i].right_fork = &info->forks[i - 1];
        info->philo[i].right_fork = &info->forks[(i + 1) % info->num_of_philo];
        info->philo[i].info = info;
        i++;
    }
    return (0);
}

int	init_info(t_info *info, char **av)
{
	info->num_of_philo= ft_atol(av[1]);
	info->time_die = ft_atol(av[2]);
	info->time_eat = ft_atol(av[3]);
	info->time_sleep = ft_atol(av[4]);
	if (av[5])
		info->num_meals = ft_atol(av[5]);
	else
		info->num_meals = -1;
	info->end = 0;
	return (0);
}

int init_forks(t_info *info)
{
    int i;

    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_mutex_init(&info->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

int init_mutex(t_info *info)
{
    if (pthread_mutex_init(&info->eat_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&info->write_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&info->eat_done_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&info->end_mutex, NULL) != 0)
        return (1);
    return (0);
}
