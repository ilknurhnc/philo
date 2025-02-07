/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:29 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/07 15:41:08 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
		if (argv[1][0] == '0' || ft_atol(argv[1]) > 200)
			return (1);
	}
	return (0);
}

static int	init_program(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&info->philo[i].thread, NULL, life_cycle, (void *)&info->philo[i]))
			printf("Thread creation failed for philosopher %d\n", i);
		i++;
	}
	check_philo(info);
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (info->num_of_philo == 1)
		{
			if (pthread_detach(info->philo[i].thread))
				return(printf("Detach Error for philosopher\n"));
		}
		else
		{
			if (pthread_join(info->philo[i].thread, NULL))
				return(printf("Join Error for philosopher %d\n", i));
		}
	}
	return 0;
}

static void	finish_program(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->end_mutex);
	pthread_mutex_destroy(&info->write_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->eat_done_mutex);

}

int	main(int argc, char *argv[])
{
	t_info info;

	if (check_arg(argc, argv))
	{
		printf("Invalid arguman!\n");
		return 1;
	}
	if (init_info(&info, argv) || init_philo(&info) || init_forks(&info)|| init_mutex(&info))
	{
		printf("There are something that cannot be initialized\n");
		return (1);
	}
	
	init_program(&info);
	finish_program(&info);
}