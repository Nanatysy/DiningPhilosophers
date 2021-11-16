#include "philo_bonus.h"

void	*philo_checker(void *arg)
{
	t_philo_atributes	*tmp;

	tmp = arg;
	while (tmp->meal_count != tmp->arg->flag)
	{
		if (gettime(tmp->start) > tmp->arg->time_to_die)
		{
			myprint(DIE, tmp->num, tmp->beginning_of_era, tmp->write);
			tmp->death_flag = 1;
			exit(0);
		}
		usleep(100);
	}
	return (0);
}

int	child_main(t_dining_room *all)
{
	pthread_create(&all->phil->checker, NULL, &philo_checker, all->phil);
	while (1)
	{
		eat(all->phil);
		if (all->phil->meal_count == all->info->flag || all->phil->death_flag
			|| all->info->philo_num == 1)
			break ;
		myprint(SLEEP, all->phil->num, all->start, all->write);
		mysleep(all->phil->arg->time_to_sleep);
		if (all->phil->death_flag)
			break ;
		myprint(THINK, all->phil->num, all->start, all->write);
	}
	pthread_join(all->phil->checker, NULL);
	return (0);
}

int	start_philo(t_dining_room *all)
{
	all->fork = sem_open("forks", O_CREAT, 0666, all->info->philo_num);
	if (all->fork == NULL)
		return (free_all_and_print_error(all, SEM_CREATION_ERROR));
	all->write = sem_open("write", O_CREAT, 0666, 1);
	if (all->write == NULL)
		return (free_all_and_print_error(all, SEM_CREATION_ERROR));
	sem_unlink("forks");
	sem_unlink("write");
	gettimeofday(&all->start, NULL);
	if (process_start(1, all) == 0)
		return (0);
	usleep(100);
	if (process_start(0, all) == 0)
		return (0);
	return (1);
}
