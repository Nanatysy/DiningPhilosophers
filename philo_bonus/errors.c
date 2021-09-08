/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:38:12 by dwillett          #+#    #+#             */
/*   Updated: 2021/08/04 13:24:43 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
