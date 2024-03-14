/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/11 20:09:30 by mzeggaf          ###   ########.fr       */
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
	printf("%d %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(philo->env->dead_lock);
}

int	ft_usleep(int ms)
{
	double	start;

	start = ft_get_time();
	while (ft_get_time() < start + ms)
		;
	return (0);
}

void	ft_sleep(t_philosopher *philo)
{
	if (philo->meals == philo->env->meals_to_go)
		return ;
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo->env->time_to_sleep);
}

void	ft_eat(t_philosopher *philo)
{
	ft_print_action(philo, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	ft_usleep(philo->env->time_to_eat);
}

void	ft_live(t_philosopher *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	if (philo->id >= philo->env->pop)
		fork_right = philo->env->forks;
	else
		fork_right = philo->env->forks + philo->id;
	fork_left = philo->env->forks + philo->id - 1;
	if (fork_right != fork_left)
	{
		pthread_mutex_lock(fork_left);
		pthread_mutex_lock(fork_right);
		ft_print_action(philo, "has taken a fork");
		ft_eat(philo);
		pthread_mutex_unlock(fork_left);
		pthread_mutex_unlock(fork_right);
		ft_sleep(philo);
	}
	ft_print_action(philo, "is thinking");
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
	if (philo->id % 2 == 0 || philo->id == philo->env->pop)
		ft_print_action(philo, "is thinking");
	while (ft_exists(philo))
	{
		ft_live(philo);
	}
	if (philo->meals != philo->env->meals_to_go)
	{	
		ft_print_action(philo, "died");
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
	env->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->dead_lock)
		return (-1);
	if (pthread_mutex_init(env->dead_lock, NULL) != 0)
		return (-1);
	philo = (t_philosopher *)malloc((env->pop + 1) * sizeof(t_philosopher));
	if (!philo)
		return (-1);
	env->forks = (pthread_mutex_t *)ft_calloc(env->pop, sizeof(pthread_mutex_t));
	if (!env->forks)
		return (-1);
	env->pids = (pthread_t *)malloc((env->pop + 1) * sizeof(pthread_t));
	if (!env->pids)
		return (-1);
	while (i < env->pop)
	{
		if (pthread_mutex_init(env->forks + i, NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
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
	i = 0;
	while (i < env->pop)
	{
		if (pthread_mutex_destroy(env->forks + i) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(env->dead_lock);
	free(env->dead_lock);
	free(philo);
	free(env->forks);
	free(env->pids);
	return (0);
}
