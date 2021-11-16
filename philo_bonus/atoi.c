#include "philo_bonus.h"

int	ft_atoi_p(char *str)
{
	long int	res;
	int			i;

	res = 0;
	i = 0;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (int)str[i++] - '0';
	if (str[i] != '\0')
		return (-1);
	if (res > MAX_INT)
		return (-1);
	return ((int)res);
}
