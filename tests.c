#include "libft/libft.h"
#include <stdio.h>

// pthread_mutex_t	mutex;
// pthread_mutex_t	mutex2;

// void	*func(void *arg)
// {
// 	int *num;

// 	num = (int *)arg;
// 	pthread_mutex_lock(&mutex);
// 	printf("hello from thread 1: %d\n", *num);
// 	*num = *num + 1;
// 	pthread_mutex_unlock(&mutex);
// 	return (NULL);
// }

// void	*func2(void *arg)
// {
// 	int *num;

// 	num = (int *)arg;
// 	pthread_mutex_lock(&mutex2);
// 	printf("hello from thread 2: %d\n", *num);
// 	*num = *num + 1;
// 	pthread_mutex_unlock(&mutex2);
// 	return (NULL);
// }

// double	ft_get_time(void)
// {
// 	struct timeval	counter;

// 	gettimeofday(&counter, NULL);
// 	return (counter.tv_sec * 1000.0 + counter.tv_usec / 1000.0);
// }

int	main(int argc, char *argv[])
{
	printf("num: %d\n", ft_atoi(argv[1]));
	return (0);
}