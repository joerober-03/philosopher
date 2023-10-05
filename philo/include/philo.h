/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:00:03 by joerober          #+#    #+#             */
/*   Updated: 2023/03/09 14:39:51 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				eat_count;
	int				id;
	long long		last_time_eaten;
	struct s_var	*v;
	pthread_t		thread;
}					t_philo;

typedef struct s_var
{
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	finish_mutex;
	long long		start;
	long long		end;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				philo_num;
	int				trigger;
	int				finished_philos;
	int				i;
	t_philo			*philo;
}				t_var;

void		*function(void *arg);
int			initiate_values(t_var *v, char **argv, int argc);
int			initiate_values2(t_var *v);
int			assign_values(t_var *v, char **argv);
int			check_death(t_philo *philo);
int			check_finish(t_philo *philo, int n);
void		print_thing(char *str, t_philo *philo, int n);
void		ft_usleep(long long ms, t_philo *philo);
long long	get_time(void);
void		free_values(t_var *v);
void		one_philo(t_var *v);
void		eat(t_philo *philo);
int			ft_atoi(const char *str);

#endif
