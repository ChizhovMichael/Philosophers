/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:11:56 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/06 15:57:08 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int	philo_eat(t_philo *philo)
{
	int		fork_left;
	int		fork_right;
	long	start_time;

	fork_left = philo->fork_left;
	fork_right = philo->fork_right;
	start_time = philo->start_time;
	pthread_mutex_lock(&philo->info->mutexs[fork_left]);
	pthread_mutex_lock(&philo->info->mutexs[fork_right]);
	pthread_mutex_lock(&philo->info->do_only_this);
	if (!check_philo_die(philo))
		return (0);
	pthread_mutex_unlock(&philo->info->do_only_this);
	pthread_mutex_lock(&philo->info->do_only_this);
	printf("%ld %d has taken a fork\n", \
			timestamp_in_ms() - start_time, philo->id);
	printf("%ld %d is eating\n", timestamp_in_ms() - start_time, philo->id);
	pthread_mutex_unlock(&philo->info->do_only_this);
	philo->last_eat = timestamp_in_ms() - start_time;
	my_sleep(philo->info->time_to_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->info->mutexs[fork_left]);
	pthread_mutex_unlock(&philo->info->mutexs[fork_right]);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long	start_time;

	start_time = philo->start_time;
	if (philo->info->stop == 1)
		return (0);
	pthread_mutex_lock(&philo->info->do_only_this);
	printf("%ld %d is sleeping\n", timestamp_in_ms() - start_time, philo->id);
	printf("%ld %d is thinking\n", timestamp_in_ms() - start_time, philo->id);
	pthread_mutex_unlock(&philo->info->do_only_this);
	my_sleep(philo->info->time_to_sleep);
	return (1);
}

void	*philo_live(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_time = timestamp_in_ms();
	pthread_detach(philo->thread);
	while (philo->info->stop != 1)
	{
		if (!philo_eat(philo))
			return (NULL);
		if (philo->info->must_eat != -1 \
				&& philo->count_eat == philo->info->must_eat)
		{
			philo->done = 1;
			return (NULL);
		}
		if (!philo_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	ft_start(t_info *info)
{
	int	i;

	if (pthread_create(&info->monitor, NULL, monitor, (void *)info) != 0)
		return (error_msg("Not create monitor\n"));
	i = -1;
	while (++i < info->number)
	{
		if (pthread_create(&info->philo[i].thread, NULL, \
					philo_live, &info->philo[i]) != 0)
			return (error_msg("Not create philo live\n"));
		my_sleep(1);
	}
	pthread_join(info->monitor, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!ft_validation(argc, argv))
		return (0);
	if (!ft_init_args(&info, argv))
		return (0);
	if (!ft_init_mutex(&info))
		return (0);
	if (!ft_init_philo(&info))
		return (0);
	if (!ft_start(&info))
		return (0);
	clear_philo(&info);
	return (0);
}
