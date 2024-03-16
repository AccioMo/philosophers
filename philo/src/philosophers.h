/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:38 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/16 01:32:25 by mzeggaf          ###   ########.fr       */
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

/*			general struct			*/
typedef struct s_env
{
	int				pop;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_to_go;
	int				dead;
	double			start;
	pthread_t		*pids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
}	t_env;

/*			philosopher struct			*/
typedef struct s_philosopher
{
	int		id;
	int		thinking;
	int		meals;
	double	last_meal;
	t_env	*env;
}	t_philosopher;

/*			functions_bonus			*/
int		ft_arg_check(int argc, char *argv[], t_env *env);
int		ft_create_watcher(t_philosopher *philo);
void	ft_clear(t_philosopher *philo);

/*			create_bonus			*/
int		ft_allocate(t_env *env);
int		ft_init_mutexes(t_env *env);
void	*ft_create_philosophers(t_env *env);
int		ft_breathing(t_philosopher *philo);

/*			actions_bonus			*/
void	ft_eat(t_philosopher *philo);
void	ft_sleep(t_philosopher *philo);
void	ft_think(t_philosopher *philo);
void	ft_print_action(t_philosopher *philo, char *action);
void	ft_die(t_philosopher *philo);

/*			utils_bonus				*/
double	ft_get_time(void);
void	ft_usleep(int ms, t_env *env);
long	ft_round(double nb);

#endif
