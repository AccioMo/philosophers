/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/14 21:52:14 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sleep(t_philosopher *philo, t_env *env)
{
	if (philo->meals == env->meals_to_go)
		return ;
	ft_print_action(philo, env, "is sleeping");
	ft_usleep(env->time_to_sleep);
}

void	ft_eat(t_philosopher *philo, t_env *env)
{
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
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
	ft_print_action(philo, env, "is thinking");
}

void	ft_print_action(t_philosopher *philo, t_env *env, char *action)
{
	int		timestamp;

	timestamp = ft_get_time() - env->start;
	sem_wait(env->lock);
	printf("%d %d %s\n", timestamp, philo->id, action);
	sem_post(env->lock);
}

int	ft_exists(t_philosopher *philo, t_env *env)
{
	double	current;
	double	deadline;
	int		hungry;

	current = ft_get_time();
	deadline = philo->last_meal + env->time_to_die;
	hungry = philo->meals < env->meals_to_go;
	if (current < deadline && (env->meals_to_go < 0 || hungry))
		return (1);
	return (0);
}
