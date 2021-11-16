#include "philo_bonus.h"

void	mysleep(int mili)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (gettime(start) < mili)
		usleep(50);
}

long	gettime(struct timeval start)
{
	long			tmp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	tmp = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec / 1000) \
	- (start.tv_usec / 1000);
	return (tmp);
}

void	myprint(int flag, int num, struct timeval start, sem_t *write)
{
	sem_wait(write);
	if (flag == EAT)
		printf("%ld %s%d is eating%s\n", gettime(start), GREEN, num,
			   NONE);
	else if (flag == SLEEP)
		printf("%ld %s%d is sleeping%s\n", gettime(start), YELLOW, num,
			   NONE);
	else if (flag == THINK)
		printf("%ld %s%d is thinking%s\n", gettime(start), CIAN, num,
			   NONE);
	else if (flag == TAKE_FORK)
		printf("%ld %d has taking a fork\n", gettime(start), num);
	else
	{
		printf("%ld %s%d is DEAD%s\n", gettime(start), RED, num, NONE);
		return ;
	}
	sem_post(write);
}

void	eat(t_philo_atributes *tmp)
{
	sem_wait(tmp->fork);
	if (tmp->death_flag == 1)
		return ;
	myprint(TAKE_FORK, tmp->num, tmp->beginning_of_era, tmp->write);
	if (tmp->arg->philo_num == 1)
		return ;
	sem_wait(tmp->fork);
	if (tmp->death_flag == 1)
		return ;
	myprint(TAKE_FORK, tmp->num, tmp->beginning_of_era, tmp->write);
	gettimeofday(&tmp->start, NULL);
	if (tmp->death_flag == 1)
		return ;
	myprint(EAT, tmp->num, tmp->beginning_of_era, tmp->write);
	mysleep(tmp->arg->time_to_eat);
	tmp->meal_count++;
	sem_post(tmp->fork);
	sem_post(tmp->fork);
}
