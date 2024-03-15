/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:46:54 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 23:21:13 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_arg_check(int argc, char *argv[], t_env *env)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("usage: ./philosophers_bonus number_of_philosophers \
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

int	ft_input_check(int argc, char *argv[], t_env *env)
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
	return (0);
}

int	ft_start(t_env *env)
{
	env->pids = (int *)ft_calloc(env->pop, sizeof(int));
	if (!env->pids)
		return (-1);
	sem_unlink("/fork_lock");
	sem_unlink("/death_lock");
	env->forks_lock = sem_open("/fork_lock", O_CREAT, S_IRWXU, env->pop);
	env->lock = sem_open("/death_lock", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	ft_exists(t_philosopher *philo, t_env *env)
{
	long	current;
	long	deadline;
	int		hungry;

	current = ft_round(ft_get_time());
	deadline = ft_round(philo->last_meal) + ft_round(env->time_to_die);
	hungry = philo->meals < env->meals_to_go;
	if (current >= deadline)
		ft_die(philo, env);
	if (env->meals_to_go < 0 || hungry)
		return (1);
	return (0);
}

void	ft_clear(t_env *env)
{
	sem_close(env->forks_lock);
	sem_close(env->lock);
	sem_unlink("/fork_lock");
	sem_unlink("/death_lock");
	free(env->pids);
}
