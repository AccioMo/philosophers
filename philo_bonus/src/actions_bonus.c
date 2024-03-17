/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/17 22:45:55 by mzeggaf          ###   ########.fr       */
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
	philo->thinking = 0;
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
	ft_print_action(philo, env, "is eating");
	sem_wait(env->lock);
	philo->last_meal = ft_get_time();
	philo->meals++;
	sem_post(env->lock);
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
	sem_wait(env->print_lock);
	printf("%ld %d %s\n", timestamp, philo->id, action);
	if (ft_strncmp(action, "died", 4))
		sem_post(env->print_lock);
}
