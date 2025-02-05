/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihancer <ihancer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:29 by ihancer           #+#    #+#             */
/*   Updated: 2025/02/05 04:02:14 by ihancer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

int	check_arg(int argc, char *argv[])
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
		if(argv[1][0] == '0' || ft_atol(argv[1]) > 200)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info info;
	
	if (check_arg(argc, argv))
		printf("Invalid arguman!\n");

	if (init_info(info, argv) || init_philo(info) || init_forks(info) || init_mutex(info))
	{
		printf("There are something that cannot be initialized\n");
		return (1);
	}


}