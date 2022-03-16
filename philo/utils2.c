/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:10:29 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/06 14:16:04 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int	ft_init_args(t_info *info, char **argv)
{
	info->number = ft_long_atoi(argv[1]);
	info->time_to_die = ft_long_atoi(argv[2]);
	info->time_to_eat = ft_long_atoi(argv[3]);
	info->time_to_sleep = ft_long_atoi(argv[4]);
	if (ft_strlen(argv[5]) > 0)
		info->must_eat = ft_long_atoi(argv[5]);
	else
		info->must_eat = -1;
	info->stop = 0;
	return (ft_validation_arg(info));
}

int	ft_init_mutex(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->do_only_this, NULL))
		return (error_msg("do_only_this not init"));
	info->mutexs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
			* info->number);
	if (!info->mutexs)
		return (error_msg("forks mutex not alloc\n"));
	i = -1;
	while (++i < info->number)
		if (pthread_mutex_init(&info->mutexs[i], NULL))
			return (error_msg("mutexs not init"));
	return (1);
}

int	ft_init_philo(t_info *info)
{
	int	i;

	i = -1;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number);
	if (!info->philo)
		return (error_msg("Not alloc philos\n"));
	while (++i < info->number)
	{
		info->philo[i].id = i + 1;
		info->philo[i].fork_left = i;
		info->philo[i].fork_right = i + 1;
		if (info->philo[i].fork_right > info->number - 1)
			info->philo[i].fork_right = 0;
		info->philo[i].count_eat = 0;
		info->philo[i].done = 0;
		info->philo[i].info = info;
		info->philo[i].last_eat = 0;
	}
	return (1);
}
