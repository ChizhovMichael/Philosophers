/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:02:07 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/06 13:58:24 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int	ft_validation(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("ERROR! Args count\n");
		return (0);
	}
	while (argv[i])
	{
		if (!is_numeric_str(argv[i]))
		{
			printf("ERROR! arg %d: %s - Not valid\n", i, argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_validation_arg(t_info *info)
{
	int	error;

	error = 0;
	if (!info->number || info->number < 2 || info->number > 200)
		error = printf("ERROR! number not valid (< 2 or NULL or > 200)\n");
	if (!info->time_to_die || info->time_to_die < 60)
		error = printf("ERROR! time_to_die not valid (0 or < 60)\n");
	if (!info->time_to_eat || info->time_to_eat < 60)
		error = printf("ERROR! time_to_eat not valid (0 or < 60)\n");
	if (!info->time_to_sleep || info->time_to_eat < 60)
		error = printf("ERROR! time_to_sleep not valid (0 or < 60)\n");
	if (!info->must_eat)
		error = printf("ERROR! must_eat not valid (0 or NULL)\n");
	if (error != 0)
		return (0);
	return (1);
}

int	check_philo_done(t_info *info)
{
	int	i;
	int	done;

	i = -1;
	done = 0;
	while (++i < info->number)
	{
		if (info->philo[i].done == 1)
			done++;
		if (done == info->number)
			return (0);
	}
	return (1);
}

int	check_philo_die(t_philo *philo)
{
	long	start_time;

	start_time = philo->start_time;
	if (philo->info->stop == 1)
		return (0);
	if ((timestamp_in_ms() - start_time - \
				philo->last_eat) > philo->info->time_to_die)
	{
		philo->info->stop = 1;
		printf("%ld ms id %d died\n", timestamp_in_ms() - start_time, philo->id);
		return (0);
	}
	return (1);
}
