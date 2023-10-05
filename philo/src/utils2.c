/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:32:42 by joerober          #+#    #+#             */
/*   Updated: 2023/03/09 14:40:00 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	one_philo(t_var *v)
{
	print_thing("has taken his left fork", &v->philo[0], 1);
	ft_usleep(v->time_to_die, v->philo);
	print_thing("has died", &v->philo[0], 1);
	free_values(v);
}

int	assign_values(t_var *v, char **argv)
{
	v->philo_num = ft_atoi(argv[1]);
	v->philo = malloc(sizeof(t_philo) * v->philo_num);
	v->forks = malloc(sizeof(pthread_mutex_t) * v->philo_num);
	if (!v->forks || !v->philo)
		return (1);
	v->time_to_die = ft_atoi(argv[2]);
	v->time_to_eat = ft_atoi(argv[3]);
	v->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}

int	initiate_values(t_var *v, char **argv, int argc)
{
	if (assign_values(v, argv))
		return (1);
	if (argc == 6)
	{
		v->num_to_eat = ft_atoi(argv[5]);
		if (v->num_to_eat < 1)
		{
			printf("invalid values\n");
			free_values(v);
			return (1);
		}
	}
	else
		v->num_to_eat = -1;
	if (v->philo_num < 1 || v->time_to_die < 1 || v->time_to_eat < 1
		|| v->time_to_sleep < 1)
	{
		printf("invalid values\n");
		free_values(v);
		return (1);
	}
	v->i = -1;
	return (0);
}

int	initiate_values2(t_var *v)
{
	v->trigger = 0;
	v->finished_philos = 0;
	v->start = get_time();
	while (++v->i < v->philo_num)
	{
		v->philo[v->i].id = v->i + 1;
		v->philo[v->i].left_fork = v->i;
		v->philo[v->i].right_fork = (v->i + 1) % v->philo_num;
		v->philo[v->i].eat_count = 0;
		v->philo[v->i].last_time_eaten = v->start;
		v->philo[v->i].v = v;
	}
	v->i = -1;
	while (++v->i < v->philo_num)
	{
		if (pthread_mutex_init(&v->forks[v->i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&v->write, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&v->eat_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&v->finish_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sign * res);
}
