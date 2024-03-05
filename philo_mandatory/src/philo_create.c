/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/05 19:37:48 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophy(void *arg)
{
	struct timeval	counter;
	struct timeval	end;
	struct timeval	start;
	double			time_to_die;
	long			i;
	t_universe		*uni;

	i = 0;
	uni = (t_universe *)arg;
	gettimeofday(&start, NULL);
	gettimeofday(&counter, NULL);
	time_to_die = (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0) + uni->time_to_die;
	printf("time_to_die: %f ms\n", time_to_die - (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0));
	while ((counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0) <= time_to_die)
		gettimeofday(&counter, NULL);
	gettimeofday(&end, NULL);
	printf("lifespan: %f ms\n", (end.tv_sec * 1000.0 + end.tv_usec / 1000.0) - (start.tv_sec * 1000.0 + start.tv_usec / 1000.0));
	pthread_exit(NULL);
}

void	ft_create_threads(t_universe *uni)
{
	int	i;

	i = 0;
	uni->ids = (pthread_t *)malloc(uni->pop * sizeof(pthread_t));
	if (!uni->ids)
		return ;
	printf("%d\n", uni->pop);
	while (i < uni->pop)
	{
		if (pthread_create((uni->ids + i), NULL, ft_philosophy, uni) < 0)
			perror("pthread_create");
		i++;
	}
	i = 0;
	while (i < uni->pop)
		pthread_join(uni->ids[i++], NULL);
}
