/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:16 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/05 04:55:29 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void waiting(t_philo *philo)
{
    printf("is sleeping\n");
    ft_usleep(philo, philo->info.time_sleep);
    printf("is thinking\n");
}
void eating(t_philo *philo)
{
    
}

