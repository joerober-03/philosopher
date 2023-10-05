/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joerober <joerober@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:02:06 by joerober          #+#    #+#             */
/*   Updated: 2023/03/09 14:31:25 by joerober         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	check_finish_destroy(t_var *v)
{
	int	yes;
	int	i;

	yes = 1;
	while (yes)
	{
		i = -1;
		while (++i < v->philo_num)
		{
			if (yes && check_death(&v->philo[i]))
				yes = 0;
		}
	}
	i = -1;
	while (++i < v->philo_num)
		pthread_join(v->philo[i].thread, NULL);
	i = -1;
	while (++i < v->philo_num)
		pthread_mutex_destroy(&v->forks[i]);
	pthread_mutex_destroy(&v->write);
	pthread_mutex_destroy(&v->eat_mutex);
	pthread_mutex_destroy(&v->finish_mutex);
	free_values(v);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->v->eat_mutex);
	if (get_time() - philo->last_time_eaten >= philo->v->time_to_die)
	{
		print_thing("died", philo, 1);
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->v->eat_mutex);
		return (1);
	}
	if (philo->v->finished_philos >= philo->v->philo_num)
	{
		print_thing(" ", philo, 2);
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->v->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->v->eat_mutex);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->v->forks[philo->left_fork]);
	print_thing("has taken his left fork", philo, 1);
	pthread_mutex_lock(&philo->v->forks[philo->right_fork]);
	print_thing("has taken his right fork", philo, 1);
	print_thing("is eating", philo, 1);
	ft_usleep(philo->v->time_to_eat, philo);
	pthread_mutex_lock(&philo->v->eat_mutex);
	philo->eat_count += 1;
	if (philo->eat_count == philo->v->num_to_eat)
		philo->v->finished_philos++;
	philo->last_time_eaten = get_time();
	pthread_mutex_unlock(&philo->v->eat_mutex);
	pthread_mutex_unlock(&philo->v->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->v->forks[philo->left_fork]);
}

void	*function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->v->time_to_eat * 100);
	while (1)
	{
		if (check_finish(philo, 0))
			return (0);
		eat(philo);
		print_thing("is sleeping", philo, 1);
		ft_usleep(philo->v->time_to_sleep, philo);
		print_thing("is thinking", philo, 1);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_var	*v;

	if (argc >= 5 && argc <= 6)
	{
		v = (t_var *)malloc(sizeof(t_var));
		if (!v)
			return (0);
		if (initiate_values(v, argv, argc) || initiate_values2(v))
			exit(1);
		if (v->philo_num == 1)
		{
			one_philo(v);
			exit(1);
		}
		v->i = -1;
		while (++v->i < v->philo_num)
		{
			if (pthread_create(&v->philo[v->i].thread, NULL,
					function, &(v->philo[v->i])) != 0)
				return (0);
		}
		check_finish_destroy(v);
	}
	return (0);
}
