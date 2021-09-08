/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:37:41 by dwillett          #+#    #+#             */
/*   Updated: 2021/08/04 13:05:10 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	myprint(int flag, int num, struct timeval start, pthread_mutex_t *write)
{
	pthread_mutex_lock(write);
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
		printf("%ld %s%d died%s\n", gettime(start), RED, num, NONE);
	pthread_mutex_unlock(write);
}

void	eat(t_philo_atributes *tmp)
{
	pthread_mutex_lock(&tmp->fork[tmp->num - 1]);
	if (tmp->arg->death_flag == 1)
		return ;
	myprint(TAKE_FORK, tmp->num, tmp->beginning_of_era, &tmp->write);
	if (tmp->arg->philo_num == 1 || tmp->arg->death_flag == 1)
		return ;
	if (tmp->flag_last)
		pthread_mutex_lock(&tmp->fork[0]);
	else
		pthread_mutex_lock(&tmp->fork[tmp->num]);
	if (tmp->arg->death_flag == 1)
		return ;
	myprint(TAKE_FORK, tmp->num, tmp->beginning_of_era, &tmp->write);
	gettimeofday(&tmp->start, NULL);
	if (tmp->arg->death_flag == 1)
		return ;
	myprint(EAT, tmp->num, tmp->beginning_of_era, &tmp->write);
	mysleep(tmp->arg->time_to_eat);
	tmp->meal_count++;
	if (tmp->flag_last)
		pthread_mutex_unlock(&tmp->fork[0]);
	else
		pthread_mutex_unlock(&tmp->fork[tmp->num]);
	pthread_mutex_unlock(&tmp->fork[tmp->num - 1]);
}
