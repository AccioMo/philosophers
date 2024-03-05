/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:11:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/04 21:23:55 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophy(void *uni)
{
	struct timeval	start;
	struct timeval	end;
	int				i;

	i = 0;
	gettimeofday(&start, NULL);
	while (i < 1000)
		i++;
	gettimeofday(&end, NULL);
	printf("lifespan: %f\n", start.tv_usec - end.tv_usec);
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
