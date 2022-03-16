/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:38:58 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/12 14:15:18 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_three.h"

int	error_msg(char *str)
{
	printf("%s", str);
	return (0);
}

int	clear_philo(t_info *info)
{
	free(info->philo);
	if (sem_close(info->sem) == -1)
		return (error_msg("sem close sem fail\n"));
	if (sem_close(info->do_only_this) == -1)
		return (error_msg("sem close do_only_this fail\n"));
	return (1);
}

void	*monitor(void *data)
{
	int		status;
	t_info	*info;
	int		j;
	int		i;

	info = (t_info *)data;
	i = -1;
	while (++i < info->number)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			j = -1;
			while (++j < info->number)
				kill(info->philo[j].thread, SIGKILL);
			return (NULL);
		}
	}
	return (NULL);
}
