/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 22:34:12 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philosopher *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	if (philo->env->pop == 1)
		return ;
	philo->thinking = 0;
	fork_right = philo->env->forks + philo->id;
	if (philo->id >= philo->env->pop)
		fork_right = philo->env->forks;
	fork_left = philo->env->forks + philo->id - 1;
	pthread_mutex_lock(fork_left);
	ft_print_action(philo, "has taken a fork");
	pthread_mutex_lock(fork_right);
	ft_print_action(philo, "has taken a fork");
	ft_print_action(philo, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	ft_usleep(philo->env->time_to_eat, philo->env);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

void	ft_sleep(t_philosopher *philo)
{
	if (philo->env->pop == 1 || philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo->env->time_to_sleep, philo->env);
}

void	ft_think(t_philosopher *philo)
{
	if (philo->thinking || philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is thinking");
	philo->thinking = 1;
}

void	ft_print_action(t_philosopher *philo, char *action)
{
	long	timestamp;
	int		dead;

	pthread_mutex_lock(philo->env->lock);
	dead = philo->env->dead;
	if (dead)
	{
		pthread_mutex_unlock(philo->env->lock);
		return ;
	}
	timestamp = ft_round(ft_get_time()) - ft_round(philo->env->start);
	printf("%ld %d %s\n", timestamp, philo->id, action);
	if (ft_strncmp(action, "died", 4) != 0)
		pthread_mutex_unlock(philo->env->lock);
}

void	ft_die(t_philosopher *philo)
{
	ft_print_action(philo, "died");
	philo->env->dead = 1;
	pthread_mutex_unlock(philo->env->lock);
	pthread_exit(NULL);
}
