/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 02:09:29 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philosopher *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	if (philo->env->pop == 1)
		return ;
	fork_right = philo->env->forks + philo->id;
	if (philo->id >= philo->env->pop)
		fork_right = philo->env->forks;
	fork_left = philo->env->forks + philo->id - 1;
	pthread_mutex_lock(fork_left);
	ft_print_action(philo, "has taken a fork");
	if (!ft_exists(philo))
	{
		pthread_mutex_unlock(fork_left);
		ft_die(philo);
	}
	pthread_mutex_lock(fork_right);
	ft_print_action(philo, "has taken a fork");
	ft_print_action(philo, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

void	ft_sleep(t_philosopher *philo)
{
	if (philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo->env->time_to_sleep);
}

void	ft_think(t_philosopher *philo)
{
	if (philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is thinking");
}

void	ft_print_action(t_philosopher *philo, char *action)
{
	int	timestamp;
	int	dead;

	pthread_mutex_lock(philo->env->dead_lock);
	dead = philo->env->dead;
	pthread_mutex_unlock(philo->env->dead_lock);
	if (dead)
		return ;
	timestamp = ft_get_time() - philo->env->start;
	pthread_mutex_lock(philo->env->dead_lock);
	printf("%d %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(philo->env->dead_lock);
}

void	ft_die(t_philosopher *philo)
{
	ft_print_action(philo, "died");
	pthread_mutex_lock(philo->env->dead_lock);
	philo->env->dead = 1;
	pthread_mutex_unlock(philo->env->dead_lock);
	pthread_exit(NULL);
}
