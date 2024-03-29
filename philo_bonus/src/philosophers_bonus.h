/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:38 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/17 22:45:48 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include "../../libft/libft.h"

/*			general struct			*/
typedef struct s_env
{
	int				pop;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_to_go;
	double			start;
	int				full;
	int				*pids;
	sem_t			*lock;
	sem_t			*print_lock;
	sem_t			*forks_lock;
}	t_env;

/*			philosopher struct			*/
typedef struct s_philosopher
{
	int		id;
	int		meals;
	int		thinking;
	double	last_meal;
	t_env	*env;
}	t_philosopher;

/*			functions_bonus			*/
void	ft_arg_check(int argc, char *argv[], t_env *env);
int		ft_hungry(t_philosopher *philo, t_env *env);
int		ft_start(t_env *env);
void	ft_clear(t_env *env);

/*			create_bonus			*/
int		ft_create_monitor(t_env *env);
int		ft_create_philosophers(t_env *env);

/*			actions_bonus			*/
void	ft_eat(t_philosopher *philo, t_env *env);
void	ft_sleep(t_philosopher *philo, t_env *env);
void	ft_think(t_philosopher *philo, t_env *env);
void	ft_print_action(t_philosopher *philo, t_env *env, char *action);

/*			utils_bonus				*/
double	ft_get_time(void);
void	ft_usleep(int ms);
long	ft_round(double nb);
void	*ft_watch(void *arg);

#endif
