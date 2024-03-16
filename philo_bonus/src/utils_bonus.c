/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/16 01:22:45 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	ft_round(double nb)
{
	return ((long)(nb + 0.5));
}

double	ft_get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

void	ft_usleep(int ms)
{
	double	start;

	start = ft_get_time();
	while (ft_get_time() < start + ms)
		;
}

void	*ft_watch(void *arg)
{
	t_philosopher	*philo;
	long			current;
	long			ddl;
	int				meals;

	philo = (t_philosopher *)arg;
	while (1)
	{
		current = ft_round(ft_get_time());
		sem_wait(philo->env->lock);
		meals = philo->meals;
		ddl = ft_round(philo->last_meal) + ft_round(philo->env->time_to_die);
		sem_post(philo->env->lock);
		if (current >= ddl)
		{
			ft_print_action(philo, philo->env, "died");
			exit(9);
		}
		if (meals == philo->env->meals_to_go)
			exit(0);
	}
}

void	ft_create_watcher_thread(t_philosopher *philo)
{
	pthread_t	watcher;

	if (pthread_create(&watcher, NULL, ft_watch, (void *)philo) < 0)
		return ;
	if (pthread_detach(watcher) < 0)
		return ;
}
