/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:46:54 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 00:46:18 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_input_check(int argc, char *argv[], t_env *env)
{
	env->pop = ft_atoi(argv[1]);
	if (env->pop < 0)
		return (1);
	env->time_to_die = ft_atoi(argv[2]);
	if (env->time_to_die < 0)
		return (1);
	env->time_to_eat = ft_atoi(argv[3]);
	if (env->time_to_eat < 0)
		return (1);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (env->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		env->meals_to_go = ft_atoi(argv[5]);
		if (env->meals_to_go < 0)
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
		ft_putstr_fd("error: input must be positive\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_clear(t_env *env, void *philo)
{
	int	i;

	i = 0;
	while (i < env->pop)
		pthread_mutex_destroy(env->forks + i++);
	pthread_mutex_destroy(env->dead_lock);
	free(env->dead_lock);
	free(env->forks);
	free(env->pids);
	free(philo);
}
