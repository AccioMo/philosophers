/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:38 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/01 20:13:07 by mzeggaf          ###   ########.fr       */
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

typedef struct s_universe
{
	int			pop;
	int			feed;
	int			sleep;
	int			starving;
	int			meals_to_go;
	pthread_t	*ids;
}	t_universe;

void	ft_create_threads(t_universe *uni);

#endif
