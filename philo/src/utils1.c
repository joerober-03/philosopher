/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:32:17 by joerober          #+#    #+#             */
/*   Updated: 2023/03/09 14:32:21 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_values(t_var *v)
{
	free(v->philo);
	free(v->forks);
	free(v);
}

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_usleep(long long ms, t_philo *philo)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < ms && check_finish(philo, 0) == 0)
		usleep(100);
}

void	print_thing(char *str, t_philo *philo, int n)
{
	long long	temp;

	pthread_mutex_lock(&philo->v->write);
	if (n == 1)
	{
		if (check_finish(philo, 0) == 0)
		{
			temp = get_time() - philo->v->start;
			printf("%lld Philosopher %d %s\n", temp, philo->id, str);
		}
		pthread_mutex_unlock(&philo->v->write);
	}
	if (n == 2)
	{
		if (check_finish(philo, 0) == 0)
		{
			temp = get_time() - philo->v->start;
			printf("%lld everyone finished\n", temp);
		}
		pthread_mutex_unlock(&philo->v->write);
	}
}

int	check_finish(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->v->finish_mutex);
	if (n != 0)
	{
		philo->v->trigger = 1;
		pthread_mutex_unlock(&philo->v->finish_mutex);
		return (1);
	}
	if (philo->v->trigger != 0)
	{
		pthread_mutex_unlock(&philo->v->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->v->finish_mutex);
	return (0);
}
