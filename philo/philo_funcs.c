#include "philo.h"

void	*philo_checker(void *info)
{
	t_philo_atributes	*tmp;
	long				diff;

	tmp = info;
	while (tmp->meal_count != tmp->arg->flag)
	{
		diff = gettime(tmp->start);
		if (diff > tmp->arg->time_to_die)
		{
			if (tmp->arg->death_flag)
				break ;
			tmp->arg->death_flag = 1;
			myprint(DIE, tmp->num, tmp->beginning_of_era, &tmp->write);
			pthread_mutex_lock(&tmp->write);
			break ;
		}
		usleep(50);
	}
	return (0);
}

void	*philo_live(void *st)
{
	t_philo_atributes	*tmp;
	pthread_t			checker;

	tmp = st;
	gettimeofday(&tmp->start, NULL);
	if (pthread_create(&checker, NULL, &philo_checker, tmp) != 0)
		return (0);
	while (1)
	{
		if (tmp->arg->death_flag == 1)
			break ;
		eat(tmp);
		if ((tmp->arg->flag != 0 && tmp->meal_count == tmp->arg->flag) || \
				tmp->arg->death_flag == 1 || tmp->arg->philo_num == 1)
			break ;
		myprint(SLEEP, tmp->num, tmp->beginning_of_era, &tmp->write);
		mysleep(tmp->arg->time_to_sleep);
		if (tmp->arg->death_flag == 1)
			break ;
		myprint(THINK, tmp->num, tmp->beginning_of_era, &tmp->write);
	}
	pthread_join(checker, NULL);
	return (0);
}

int	threads_start(int first, t_dining_room *all)
{
	while (first < all->info->philo_num)
	{
		all->phil[first].num = first + 1;
		all->phil[first].meal_count = 0;
		all->phil[first].arg = all->info;
		all->phil[first].fork = all->fork;
		all->phil[first].beginning_of_era = all->start;
		all->phil[first].write = all->write;
		all->phil[first].death_flag = &all->phil->arg->death_flag;
		if (all->phil[first].num == all->info->philo_num)
			all->phil[first].flag_last = 1;
		else
			all->phil[first].flag_last = 0;
		if (pthread_create(&all->t[first], NULL, &philo_live,
				   &all->phil[first]) != 0)
			return (1);
		first += 2;
	}
	return (0);
}
