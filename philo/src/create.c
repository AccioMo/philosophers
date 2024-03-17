/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/17 01:19:30 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_philosophy(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->env->lock);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->env->lock);
	if (philo->id % 2 == 0 || philo->id == philo->env->pop)
	{
		ft_usleep(1 + philo->id / 25, philo->env);
		ft_think(philo);
	}
	while (ft_breathing(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_breathing(t_philosopher *philo)
{
	int		dead;
	int		hungry;

	pthread_mutex_lock(philo->env->lock);
	dead = philo->env->dead;
	hungry = philo->meals < philo->env->meals_to_go;
	pthread_mutex_unlock(philo->env->lock);
	if (dead)
		pthread_exit(NULL);
	if (philo->env->meals_to_go < 0 || hungry)
		return (1);
	return (0);
}

int	ft_allocate(t_env *env)
{
	env->pids = (pthread_t *)ft_calloc(env->pop, sizeof(pthread_t));
	env->lock = (pthread_mutex_t *)malloc(1 * sizeof(pthread_mutex_t));
	env->forks = (pthread_mutex_t *)malloc(env->pop * sizeof(pthread_mutex_t));
	if (!env->forks || !env->lock || !env->pids)
	{
		free(env->lock);
		free(env->forks);
		free(env->pids);
		return (-1);
	}
	return (0);
}

int	ft_init_mutexes(t_env *env)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(env->lock, NULL) != 0)
		return (-1);
	while (i < env->pop)
	{
		if (pthread_mutex_init(env->forks + i, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	*ft_create_philosophers(t_env *env)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = (t_philosopher *)ft_calloc(env->pop, sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	env->start = ft_get_time();
	while (i < env->pop)
	{
		philo[i].id = i + 1;
		philo[i].env = env;
		philo[i].meals = 0;
		philo[i].thinking = 0;
		if (pthread_create((env->pids + i), NULL, ft_philosophy, philo + i) < 0)
		{
			perror("pthread_create");
			free(philo);
			return (NULL);
		}
		i++;
	}
	return (philo);
}
