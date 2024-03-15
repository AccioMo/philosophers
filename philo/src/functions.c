/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:46:54 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 23:10:00 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_input_check(int argc, char *argv[], t_env *env)
{
	env->pop = ft_atoi(argv[1]);
	if (env->pop < 1)
		return (1);
	env->time_to_die = ft_atoi(argv[2]);
	if (env->time_to_die < 1)
		return (1);
	env->time_to_eat = ft_atoi(argv[3]);
	if (env->time_to_eat < 1)
		return (1);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (env->time_to_sleep < 1)
		return (1);
	if (argc == 6)
	{
		env->meals_to_go = ft_atoi(argv[5]);
		if (env->meals_to_go < 1)
			return (1);
	}
	else
		env->meals_to_go = -1;
	env->dead = 0;
	return (0);
}

void	ft_arg_check(int argc, char *argv[], t_env *env)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("usage: ./philo_mandatory number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (ft_input_check(argc, argv, env) != 0)
	{
		ft_putstr_fd("Error: Input must be greater than 0.\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_clear(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->env->pop)
		pthread_mutex_destroy(philo->env->forks + i++);
	pthread_mutex_destroy(philo->env->lock);
	free(philo->env->lock);
	free(philo->env->forks);
	free(philo->env->pids);
	free(philo);
}

static void	*ft_watch(void *arg)
{
	t_philosopher	*philo;
	long			current;
	long			ddl;
	int				i;

	i = 0;
	philo = (t_philosopher *)arg;
	while (i < philo->env->pop)
	{
		current = ft_round(ft_get_time());
		ddl = ft_round(philo->last_meal) + ft_round(philo->env->time_to_die);
		if (current >= ddl)
			ft_die(&philo[i]);
		i++;
		if (i == philo->env->pop)
			i = 0;
	}
	return (NULL);
}

int	ft_create_watcher(t_philosopher *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, ft_watch, philo) < 0)
		return (-1);
	if (pthread_join(monitor, NULL) < 0)
		return (-1);
	return (0);
}
