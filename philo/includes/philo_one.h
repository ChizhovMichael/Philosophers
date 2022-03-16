/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:14:02 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/06 15:46:40 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

struct				s_info;

typedef struct s_philo
{
	int				id;
	int				fork_left;
	int				fork_right;
	pthread_t		thread;
	int				count_eat;
	struct s_info	*info;
	int				done;
	long			last_eat;
	long			start_time;
}				t_philo;

typedef struct s_info
{
	long			number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	pthread_mutex_t	*mutexs;
	pthread_mutex_t	do_only_this;
	t_philo			*philo;
	pthread_t		monitor;
	int				stop;
}				t_info;

long				timestamp_in_ms(void);
void				my_sleep(long ms);
size_t				ft_strlen(const char *s);
unsigned long long	ft_long_atoi(const char *str);
int					is_numeric_str(char *str);

int					ft_validation(int argc, char **argv);
int					ft_validation_arg(t_info *info);
int					check_philo_done(t_info *info);
int					check_philo_die(t_philo *philo);

int					error_msg(char *str);
int					clear_philo(t_info *info);
void				*monitor(void *data);

int					ft_init_args(t_info *info, char **argv);
int					ft_init_mutex(t_info *info);
int					ft_init_philo(t_info *info);

#endif
