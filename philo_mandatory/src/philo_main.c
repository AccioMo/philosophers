/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:03:15 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/01 20:08:03 by mzeggaf          ###   ########.fr       */
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
	t_universe	uni;

	ft_input_check(argc);
	uni.pop = ft_atoi(argv[1]);
	uni.starving = ft_atoi(argv[2]);
	uni.feed = ft_atoi(argv[3]);
	uni.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		uni.meals_to_go = ft_atoi(argv[5]);
	else
		uni.meals_to_go = -1;
	ft_create_threads(&uni);
	printf("Done\n");
	return (0);
}
