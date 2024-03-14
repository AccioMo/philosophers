/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/14 03:21:26 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

double	ft_get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

void	ft_print_action(t_philosopher *philo, t_env *env, char *action)
{
	int		timestamp;

	timestamp = ft_get_time() - env->start;
	sem_wait(env->lock);
	printf("%d %d %s\n", timestamp, philo->id, action);
	sem_post(env->lock);
}

int	ft_usleep(int ms)
{
	double	start;

	start = ft_get_time();
	while (ft_get_time() < start + ms)
		;
	return (0);
}

void	ft_sleep(t_philosopher *philo, t_env *env)
{
	if (philo->meals == env->meals_to_go)
		return ;
	ft_print_action(philo, env, "is sleeping");
	ft_usleep(env->time_to_sleep);
}

void	ft_eat(t_philosopher *philo, t_env *env)
{
	ft_print_action(philo, env, "is eating");
	philo->last_meal = ft_get_time();
	philo->meals++;
	ft_usleep(env->time_to_eat);
}

void	ft_live(t_philosopher *philo, t_env *env)
{
	sem_wait(env->forks_lock);
	ft_print_action(philo, env, "has taken a fork");
	ft_eat(philo, env);
	sem_post(env->forks_lock);
	ft_sleep(philo, env);
	ft_print_action(philo, env, "is thinking");
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

int	ft_philosophy(void *arg, int i)
{
	t_philosopher	philo;
	t_env			*env;

	env = (t_env *)arg;
	philo.last_meal = ft_get_time();
	philo.id = i;
	philo.meals = 0;
	if (philo.id % 2 == 0 || philo.id == env->pop)
		ft_print_action(&philo, env, "is thinking");
	while (ft_exists(&philo, env))
		ft_live(&philo, env);
	if (philo.meals != env->meals_to_go)
	{
		ft_print_action(&philo, env, "died");
		sem_wait(env->lock);
		exit(9);
	}
	exit(0);
}

int	ft_create_process(int (*func)(void *, int), void *arg, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		func(arg, i);
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	ft_genocide(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->pop)
	{
		kill(env->pids[i], SIGKILL);
		i++;
	}
}

void	*ft_monitor(void *arg)
{
	t_env	*env;
	int		status;
	int		i;

	i = 0;
	env = (t_env *)arg;
	while (i++ < env->pop)
	{
		waitpid(-1, &status, WNOHANG);
		if (status >> 8 == 9)
		{
			ft_genocide(env);
			sem_post(env->lock);
			pthread_exit(NULL);
		}
	}
	return (NULL);
}

int	ft_create_threads(t_env *env)
{
	int	i;
	pthread_t	monitor;

	i = 0;
	env->pids = (int *)malloc(env->pop * sizeof(int));
	if (!env->pids)
		return (-1);
	env->forks_lock = sem_open("/forks_sem", O_CREAT, 0644, env->pop / 2);
	env->lock = sem_open("/death_sem", O_CREAT, 0644, 1);
	while (i < env->pop)
	{
	double	start = ft_get_time();
		env->pids[i] = ft_create_process(ft_philosophy, env, i);
		if (env->pids[i] < 0)
			return (-1);
		i++;
	printf("time: %f\n", ft_get_time() - start);
	}
	if (pthread_create(&monitor, NULL, ft_monitor, env) < 0)
	{
		perror("pthread_create");
		return (-1);
	}
	pthread_join(monitor, NULL);
	sem_close(env->forks_lock);
	sem_close(env->lock);
	sem_unlink("/forks_sem");
	sem_unlink("/death_sem");
	return (0);
}
