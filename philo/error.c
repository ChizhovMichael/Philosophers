/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:38:58 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/12 13:40:41 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int	error_msg(char *str)
{
	printf("%s", str);
	return (0);
}

int	clear_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number)
		pthread_mutex_destroy(&info->mutexs[i]);
	pthread_mutex_destroy(&info->do_only_this);
	free(info->mutexs);
	free(info->philo);
	return (1);
}

void	*monitor(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	while (info->stop != 1)
	{
		if (!check_philo_done(info))
		{
			info->stop = 1;
			return (NULL);
		}
	}
	return (NULL);
}
