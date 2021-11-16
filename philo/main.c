#include "philo.h"

void	init_struct(t_dining_room *all)
{
	all->info = NULL;
	all->phil = NULL;
	all->fork = NULL;
	all->t = NULL;
}

int	malloc_all(t_dining_room *all)
{
	all->t = malloc(sizeof(pthread_t) * all->info->philo_num);
	if (!all->t)
		return (1);
	all->phil = malloc(sizeof(t_philo_atributes) * all->info->philo_num);
	if (!all->phil)
		return (1);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->info->philo_num);
	if (!all->fork)
		return (1);
	return (0);
}

int	all_mutex_init(t_dining_room *all)
{
	int	i;

	i = 0;
	while (i < all->info->philo_num)
	{
		if (pthread_mutex_init(&all->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&all->write, NULL) != 0)
		return (1);
	return (0);
}

int	second_main(t_dining_room *all)
{
	int	i;

	gettimeofday(&all->start, NULL);
	if (threads_start(1, all))
		return (free_all_and_print_error(all, THREAD_CREATION_ERROR));
	usleep(100);
	if (threads_start(0, all))
		return (free_all_and_print_error(all, THREAD_CREATION_ERROR));
	i = 0;
	while (i < all->info->philo_num)
	{
		pthread_join(all->t[i], NULL);
		i++;
	}
	i = 0;
	while (i < all->info->philo_num)
	{
		pthread_mutex_destroy(&all->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&all->write);
	return (free_all_and_print_error(all, NULL));
}

int	main(int argc, char **argv)
{
	t_dining_room		all;

	if (argc != 5 && argc != 6)
		return (print_error(ARG_NUMBER_ERROR));
	init_struct(&all);
	all.info = malloc(sizeof(t_philo_arg));
	if (!all.info)
		return (free_all_and_print_error(&all, MALLOC_ERROR));
	if (args_check_and_fill(argv, &all, argc == 6))
		return (free_all_and_print_error(&all, ARG_ERROR));
	if (all.info->flag == 0)
		return (free_all_and_print_error(&all, NULL));
	if (malloc_all(&all))
		return (free_all_and_print_error(&all, MALLOC_ERROR));
	if (all_mutex_init(&all))
		return (free_all_and_print_error(&all, MUTEX_CREATION_ERROR));
	return (second_main(&all));
}
