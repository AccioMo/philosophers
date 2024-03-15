/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:36:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 22:38:05 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_round(double nb)
{
	nb = nb + 0.5;
	return ((long)nb);
}

double	ft_get_time(void)
{
	struct timeval	counter;

	gettimeofday(&counter, NULL);
	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
}

void	ft_usleep(int ms, t_env *env)
{
	double	start;
	int		dead;

	start = ft_get_time();
	while (ft_get_time() < start + ms)
	{
		pthread_mutex_lock(env->lock);
		dead = env->dead;
		pthread_mutex_unlock(env->lock);
		if (dead)
			return ;
	}
}
