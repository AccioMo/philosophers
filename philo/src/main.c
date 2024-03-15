/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:03:15 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/15 23:08:59 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_env	env;
	void	*philo;
	int		i;

	i = 0;
	ft_arg_check(argc, argv, &env);
	if (ft_allocate(&env) < 0)
		return (-1);
	if (ft_init_mutexes(&env) < 0)
	{
		free(env.lock);
		free(env.forks);
		free(env.pids);
		return (-1);
	}
	philo = ft_create_philosophers(&env);
	if (!philo)
		ft_clear(philo);
	while (i < env.pop)
		pthread_join(env.pids[i++], NULL);
	ft_clear(philo);
	return (0);
}
