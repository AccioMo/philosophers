/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:38 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/09 21:19:14 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "../../libft/libft.h"
# include "../../ft_printf/ft_printf.h"

typedef struct s_env
{
	int				pop;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_to_go;
	double			start;
	int				dead;
	pthread_t		*pids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*print_lock;
}	t_env;

typedef struct s_philosopher
{
	int		id;
	int		thinking;
	int		meals;
	double	last_meal;
	t_env	*env;
}	t_philosopher;

double	ft_get_time(void);
int		ft_create_threads(t_env *env);

#endif
