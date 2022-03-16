/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:10:29 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/12 14:16:12 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

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

int	ft_init_semaphore(t_info *info)
{
	sem_unlink("sem");
	sem_unlink("do_only_this");
	info->sem = sem_open("sem", O_CREAT, 0664, info->number / 2);
	if (info->sem == SEM_FAILED)
		return (error_msg("Not open sem\n"));
	info->do_only_this = sem_open("do_only_this", O_CREAT, 0664, 1);
	if (info->sem == SEM_FAILED)
		return (error_msg("Not open do_only_this\n"));
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

int 	ft_init_fork(t_info *info, int i, void (*f)(void *))
{
	info->philo[i].thread = fork();
	if (info->philo[i].thread == 0)
		f(&info->philo[i]);
	else if (info->philo[i].thread == -1)
		return (error_msg("Not create philo live\n"));
	return (1);
}
