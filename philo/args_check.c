#include "philo.h"

int	check_and_fill(char *str, int *info)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			i++;
		*info = ft_atoi_p(str + i);
		if (*info < 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	args_check_and_fill(char **argv, t_dining_room *all, int flag)
{
	if (check_and_fill(argv[1], &all->info->philo_num))
		return (1);
	if (check_and_fill(argv[2], &all->info->time_to_die))
		return (1);
	if (check_and_fill(argv[3], &all->info->time_to_eat))
		return (1);
	if (check_and_fill(argv[4], &all->info->time_to_sleep))
		return (1);
	if (flag)
	{
		if (check_and_fill(argv[5], &all->info->flag))
			return (1);
	}
	else
		all->info->flag = -1;
	all->info->death_flag = 0;
	return (0);
}
