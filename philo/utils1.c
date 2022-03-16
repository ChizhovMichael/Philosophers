/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 12:49:26 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/06 12:52:59 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

long	timestamp_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	my_sleep(long ms)
{
	long	t;

	t = timestamp_in_ms();
	while (timestamp_in_ms() - t < ms)
		usleep(1);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	if (s == NULL)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

unsigned long long	ft_long_atoi(const char *str)
{
	unsigned long long	result;
	int					index;

	result = 0;
	index = 0;
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9' && str[index] != '\0')
		result = (result * 10) + str[index++] - 48;
	return (result);
}

int	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	if (ft_long_atoi(str) > 9223372036854775807U)
		return (0);
	return (1);
}
