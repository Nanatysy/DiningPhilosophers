#include "philo_bonus.h"

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	free_all_and_print_error(t_dining_room *all, char *flag)
{
	if (all->info)
		free(all->info);
	if (all->phil)
		free(all->phil);
	if (all->prcs)
		free(all->prcs);
	if (flag != NULL)
		return (print_error(flag));
	else
		return (0);
}
