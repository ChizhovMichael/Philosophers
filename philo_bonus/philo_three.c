/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 21:08:11 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/09 21:08:15 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

int	philo_eat(t_philo *philo)
{
	long	start_time;

	start_time = philo->start_time;
	sem_wait(philo->info->sem);
	sem_wait(philo->info->do_only_this);
	check_philo_die(philo);
	sem_post(philo->info->do_only_this);
	sem_wait(philo->info->do_only_this);
	printf("%ld %d has taken a fork\n", \
			timestamp_in_ms() - start_time, philo->id);
	printf("%ld %d is eating\n", timestamp_in_ms() - start_time, philo->id);
	sem_post(philo->info->do_only_this);
	philo->last_eat = timestamp_in_ms() - start_time;
	my_sleep(philo->info->time_to_eat);
	philo->count_eat++;
	sem_post(philo->info->sem);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long	start_time;

	start_time = philo->start_time;
	sem_wait(philo->info->do_only_this);
	printf("%ld %d is sleeping\n", timestamp_in_ms() - start_time, philo->id);
	printf("%ld %d is thinking\n", timestamp_in_ms() - start_time, philo->id);
	sem_post(philo->info->do_only_this);
	my_sleep(philo->info->time_to_sleep);
	return (1);
}

void	*philo_live(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_time = timestamp_in_ms();
	while (philo->info->stop != 1)
	{
		if (!philo_eat(philo))
			return (NULL);
		if (philo->info->must_eat != -1 \
				&& philo->count_eat == philo->info->must_eat)
			exit(0);
		if (!philo_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	ft_start(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number)
		if (!ft_init_fork(info, i, (void *)philo_live))
			return (0);
	monitor(info);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!ft_validation(argc, argv))
		return (0);
	if (!ft_init_args(&info, argv))
		return (0);
	if (!ft_init_semaphore(&info))
		return (0);
	if (!ft_init_philo(&info))
		return (0);
	if (!ft_start(&info))
		return (0);
	clear_philo(&info);
	return (0);
}
