/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 21:08:42 by tgildero          #+#    #+#             */
/*   Updated: 2021/06/12 14:15:49 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

struct				s_info;

typedef struct s_philo
{
	int				id;
	int				fork_left;
	int				fork_right;
	pid_t			thread;
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
	sem_t			*sem;
	sem_t			*do_only_this;
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
int					ft_init_semaphore(t_info *info);
int					ft_init_philo(t_info *info);
int					ft_init_fork(t_info *info, int i, void (*f)(void *));

#endif
