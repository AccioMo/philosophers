/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/07 22:55:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double	ft_get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

void	ft_print_action(t_philosopher *philo, char *action)
{
	double	timestamp;
	char	*spaces;

	timestamp = ft_get_time() - philo->env->start;
	printf("%.1f ms: philosopher %d %s\n", timestamp, philo->id, action);
}

int	ft_set_timer(int duration, void (*function)(t_philosopher *), t_philosopher *arg)
{
	double	current;

	arg->last_meal = ft_get_time();
	while (current <= arg->last_meal + duration)
	{
		if (function)
			function(arg);
		current = ft_get_time();
	}
	return (0);
}

void	ft_sleep(t_philosopher *philo)
{
	ft_print_action(philo, "is sleeping");
	pthread_mutex_unlock(philo->env->lock);
	ft_set_timer(philo->env->time_to_sleep, NULL, philo);
	pthread_mutex_lock(philo->env->lock);
}

void	ft_eat(t_philosopher *philo)
{
	ft_print_action(philo, "is eating");
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->env->lock);
	ft_set_timer(philo->env->time_to_eat, NULL, philo);
	pthread_mutex_lock(philo->env->lock);
}

void	ft_live(t_philosopher *philo)
{
	int	*forks;
	int	right;
	int	left;

	pthread_mutex_lock(philo->env->lock);
	forks = philo->env->forks;
	right = (philo->id + 1) * ((philo->id + 1) < philo->env->pop);
	left = philo->id;
	if (forks[left] == 0 && forks[right] == 0)
	{
		ft_print_action(philo, "has taken fork");
		forks[left] = 1;
		forks[right] = 1;
		ft_eat(philo);
		forks[left] = 0;
		forks[right] = 0;
		ft_sleep(philo);
	}
	else if (philo->thinking != 1)
	{
		ft_print_action(philo, "is thinking");
		philo->thinking = 1;
	}
	pthread_mutex_unlock(philo->env->lock);
}

void	*ft_philosophy(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	ft_set_timer(philo->env->time_to_die, ft_live, philo);
	pthread_mutex_lock(philo->env->lock);
	ft_print_action(philo, "is dead");
	pthread_mutex_unlock(philo->env->lock);
	pthread_exit(NULL);
}

int	ft_create_threads(t_env *env)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	env->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->lock)
		return (-1);
	if (pthread_mutex_init(env->lock, NULL) != 0)
		return (-1);
	philo = (t_philosopher *)malloc((env->pop + 1) * sizeof(t_philosopher));
	if (!philo)
		return (-1);
	env->forks = (int *)ft_calloc(env->pop, sizeof(int));
	if (!env->forks)
		return (-1);
	env->pids = (pthread_t *)malloc((env->pop + 1) * sizeof(pthread_t));
	if (!env->pids)
		return (-1);
	while (i < env->pop)
	{
		philo[i].id = i;
		philo[i].env = env;
		philo[i].thinking = 0;
		if (pthread_create((env->pids + i), NULL, ft_philosophy, philo + i) < 0)
			perror("pthread_create");
		i++;
	}
	i = 0;
	while (i < env->pop)
		pthread_join(env->pids[i++], NULL);
	pthread_mutex_destroy(env->lock);
	return (0);
}
