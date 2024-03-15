/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 06:59:46 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sleep(t_philosopher *philo, t_env *env)
{
	if (env->pop == 1 || philo->meals == env->meals_to_go)
		return ;
	ft_print_action(philo, env, "is sleeping");
	ft_usleep(env->time_to_sleep);
}

void	ft_eat(t_philosopher *philo, t_env *env)
{
	if (env->pop == 1)
		return ;
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
	if (!ft_exists(philo, env))
	{
		sem_post(env->forks_lock);
		ft_die(philo, env);
	}
	philo->thinking = 0;
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
	ft_print_action(philo, env, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	ft_usleep(env->time_to_eat);
	sem_post(env->forks_lock);
	sem_post(env->forks_lock);
}

void	ft_think(t_philosopher *philo, t_env *env)
{
	if (philo->thinking || philo->meals == env->meals_to_go)
		return ;
	ft_print_action(philo, env, "is thinking");
	philo->thinking = 1;
}

void	ft_print_action(t_philosopher *philo, t_env *env, char *action)
{
	long	timestamp;

	timestamp = ft_round(ft_get_time()) - ft_round(env->start);
	sem_wait(env->lock);
	printf("%ld %d %s\n", timestamp, philo->id, action);
	sem_post(env->lock);
}

void	ft_die(t_philosopher *philo, t_env *env)
{
	ft_print_action(philo, env, "died");
	sem_wait(env->lock);
	exit(9);
}
