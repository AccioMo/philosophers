#include "philo_mandatory/src/philosophers.h"

typedef struct s_nuke
{
	int				num;
	pthread_mutex_t	*mutex;
}	t_nuke;

void	*func(void *arg)
{
	int	num;

	pthread_mutex_lock(((t_nuke *)arg)->mutex);
	num = ((t_nuke *)arg)->num;
	printf("%d\n", num);
	((t_nuke *)arg)->num = num + 1;
	pthread_mutex_unlock(((t_nuke *)arg)->mutex);
	return (NULL);
}

int	main()
{
	pthread_t		*thread;
	t_nuke			*arg;
	int				i;

	i = 0;
	thread = (pthread_t *)malloc(3 * sizeof(pthread_t));
	arg = (t_nuke *)malloc(sizeof(t_nuke));
	arg->num = 42;
	arg->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arg->mutex, NULL);
	while (i < 3)
	{
		pthread_create(&thread[i], NULL, func, arg);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(arg->mutex);
	return (0);
}