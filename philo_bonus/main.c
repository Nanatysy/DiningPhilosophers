/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:31:11 by dwillett          #+#    #+#             */
/*   Updated: 2021/08/04 13:24:17 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_struct(t_dining_room *all)
{
	all->info = NULL;
	all->phil = NULL;
	all->prcs = NULL;
}

int	malloc_all(t_dining_room *all)
{
	all->prcs = malloc(sizeof(pid_t) * all->info->philo_num);
	if (!all->prcs)
		return (1);
	all->phil = malloc(sizeof(t_philo_atributes));
	if (!all->phil)
		return (1);
	return (0);
}

int	process_start(int first, t_dining_room *all)
{
	while (first < all->info->philo_num)
	{
		all->prcs[first] = fork();
		if (all->prcs[first] == 0)
		{
			all->phil->num = first + 1;
			all->phil->flag_last = 0;
			if (first == all->info->philo_num - 1)
				all->phil->flag_last = 1;
			all->phil->meal_count = 0;
			all->phil->death_flag = 0;
			all->phil->beginning_of_era = all->start;
			all->phil->start = all->start;
			all->phil->fork = all->fork;
			all->phil->write = all->write;
			all->phil->arg = all->info;
			return (0);
		}
		first += 2;
	}
	return (1);
}

int	mommy_main(t_dining_room *all)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	while (i < all->info->philo_num)
		kill(all->prcs[i++], 9);
	sem_close(all->fork);
	sem_close(all->write);
	return (free_all_and_print_error(all, NULL));
}

int	main(int argc, char **argv)
{
	t_dining_room	all;

	if (argc != 5 && argc != 6)
		return (print_error(ARG_NUMBER_ERROR));
	init_struct(&all);
	all.info = malloc(sizeof(t_philo_arg));
	if (!all.info)
		return (print_error(MALLOC_ERROR));
	if (args_check_and_fill(argv, all.info, argc == 6))
		return (free_all_and_print_error(&all, ARG_ERROR));
	if (all.info->flag == 0)
		return (free_all_and_print_error(&all, NULL));
	if (malloc_all(&all))
		return (free_all_and_print_error(&all, MALLOC_ERROR));
	if (start_philo(&all) == 0)
		child_main(&all);
	else
		mommy_main(&all);
	return (0);
}
