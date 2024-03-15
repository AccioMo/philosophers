/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 07:01:12 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	ft_philosophy(void *arg, int i)
{
	t_philosopher	philo;
	t_env			*env;

	env = (t_env *)arg;
	philo.last_meal = ft_get_time();
	philo.id = i;
	philo.meals = 0;
	philo.thinking = 0;
	if (philo.id % 2 == 0 || philo.id == env->pop)
		ft_think(&philo, env);
	while (ft_exists(&philo, env))
	{
		ft_eat(&philo, env);
		ft_sleep(&philo, env);
		if (!ft_exists(&philo, env))
			break ;
		ft_think(&philo, env);
	}
	exit(0);
}

static void	ft_genocide(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->pop)
	{
		kill(env->pids[i], SIGKILL);
		i++;
	}
}

static void	*ft_watch(void *arg)
{
	t_env	*env;
	int		status;
	int		i;

	i = 0;
	env = (t_env *)arg;
	while (i++ < env->pop)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == 9)
		{
			ft_genocide(env);
			sem_post(env->lock);
			pthread_exit(NULL);
		}
	}
	return (NULL);
}

int	ft_create_watcher(t_env *env)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, ft_watch, env) < 0)
		return (-1);
	if (pthread_join(monitor, NULL) < 0)
		return (-1);
	return (0);
}

int	ft_create_philosophers(t_env *env)
{
	int	i;

	i = 0;
	env->start = ft_get_time();
	while (i < env->pop)
	{
		env->pids[i] = fork();
		if (env->pids[i] == 0)
			ft_philosophy(env, i + 1);
		else if (env->pids[i] < 0)
		{
			perror("fork");
			return (-1);
		}
		i++;
	}
	return (0);
}
