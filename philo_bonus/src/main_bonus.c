/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:03:15 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/14 21:47:38 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_env	env;

	ft_arg_check(argc);
	if (ft_input_check(argc, argv, &env) != 0)
	{
		ft_putstr_fd("error: input must be positive\n", 2);
		return (1);
	}
	ft_start(&env);
	ft_create_philosophers(&env);
	ft_create_watcher(&env);
	ft_clear(&env);
	return (0);
}
