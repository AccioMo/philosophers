/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:03:15 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/07 22:46:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_input_check(int argc)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("usage: ./philo_mandatory number_of_philosophers \
					time_to_die time_to_eat time_to_sleep \
					[number_of_times_each_philosopher_must_eat]", 2);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	t_env	env;

	ft_input_check(argc);
	env.pop = ft_atoi(argv[1]);
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]);
	env.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env.meals_to_go = ft_atoi(argv[5]);
	else
		env.meals_to_go = -1;
	env.start = ft_get_time();
	ft_create_threads(&env);
	ft_printf("Done\n");
	return (0);
}
