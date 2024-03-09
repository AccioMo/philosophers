/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/09 19:03:59 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double	ft_get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

void	ft_print_action(t_philosopher *philo, char *action)
{
	int		timestamp;
	int		dead;

	pthread_mutex_lock(philo->env->dead_lock);
	dead = philo->env->dead;
	pthread_mutex_unlock(philo->env->dead_lock);
	if (dead)
		return ;
	timestamp = ft_get_time() - philo->env->start;
	pthread_mutex_lock(philo->env->dead_lock);
	printf("%d ms %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(philo->env->dead_lock);
}

int	ft_usleep(int ms)
{
	double	start;

	start = ft_get_time();
	while (ft_get_time() < start + ms)
		; // usleep(500);
	return (0);
}

void	ft_sleep(t_philosopher *philo)
{
	if (philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is sleeping");
	// pthread_mutex_unlock(philo->env->lock);
	ft_usleep(philo->env->time_to_sleep);
	// pthread_mutex_lock(philo->env->lock);
}

void	ft_eat(t_philosopher *philo)
{
	ft_print_action(philo, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	// pthread_mutex_unlock(philo->env->lock);
	ft_usleep(philo->env->time_to_eat);
	// pthread_mutex_lock(philo->env->lock);
}

void	ft_live(t_philosopher *philo)
{
	// int	*forks;
	int	right;
	int	fork_left;
	int	fork_right;

	right = (philo->id + 1) * ((philo->id + 1) < philo->env->pop);
	pthread_mutex_lock(philo->env->fork_lock);
	fork_left = philo->env->forks[philo->id];
	fork_right = philo->env->forks[right];
	pthread_mutex_unlock(philo->env->fork_lock);
	if (fork_left == 0 && fork_right == 0)
	{
		pthread_mutex_lock(philo->env->fork_lock);
		philo->env->forks[philo->id] = 1;
		philo->env->forks[right] = 1;
		pthread_mutex_unlock(philo->env->fork_lock);
		ft_print_action(philo, "has taken fork");
		ft_eat(philo);
		pthread_mutex_lock(philo->env->fork_lock);
		philo->env->forks[philo->id] = 0;
		philo->env->forks[right] = 0;
		pthread_mutex_unlock(philo->env->fork_lock);
		ft_sleep(philo);
	}
	else if (philo->thinking != 1)
	{
		ft_print_action(philo, "is thinking");
		philo->thinking = 1;
	}
	// pthread_mutex_unlock(philo->env->lock);
}

int	ft_exists(t_philosopher *philo)
{
	double	current;
	double	deadline;
	int		dead;
	int		hungry;

	pthread_mutex_lock(philo->env->dead_lock);
	dead = philo->env->dead;
	pthread_mutex_unlock(philo->env->dead_lock);
	current = ft_get_time();
	deadline = philo->last_meal + philo->env->time_to_die;
	hungry = philo->meals < philo->env->meals_to_go;
	if (!dead && current < deadline && (philo->env->meals_to_go < 0 || hungry))
		return (1);
	return (0);
}

void	*ft_philosophy(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo->last_meal = ft_get_time();
	while (ft_exists(philo))
	{
		ft_live(philo);
	}
	if (philo->meals != philo->env->meals_to_go)
	{	
		ft_print_action(philo, "is dead");
		pthread_mutex_lock(philo->env->dead_lock);
		philo->env->dead = 1;
		pthread_mutex_unlock(philo->env->dead_lock);
	}
	pthread_exit(NULL);
}

int	ft_create_threads(t_env *env)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	env->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->fork_lock)
		return (-1);
	env->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->dead_lock)
		return (-1);
	if (pthread_mutex_init(env->fork_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(env->dead_lock, NULL) != 0)
		return (-1);
	philo = (t_philosopher *)malloc((env->pop + 1) * sizeof(t_philosopher));
	if (!philo)
		return (-1);
	env->forks = (int *)ft_calloc(env->pop, sizeof(int));
	if (!env->forks)
		return (-1);
	env->pids = (pthread_t *)malloc((env->pop + 1) * sizeof(pthread_t));
	if (!env->pids)
		return (-1);
	while (i < env->pop)
	{
		philo[i].id = i + 1;
		philo[i].env = env;
		philo[i].meals = 0;
		philo[i].thinking = 0;
		if (pthread_create((env->pids + i), NULL, ft_philosophy, philo + i) < 0)
			perror("pthread_create");
		i++;
	}
	i = 0;
	while (i < env->pop)
		pthread_join(env->pids[i++], NULL);
	pthread_mutex_destroy(env->fork_lock);
	pthread_mutex_destroy(env->dead_lock);
	return (0);
}
