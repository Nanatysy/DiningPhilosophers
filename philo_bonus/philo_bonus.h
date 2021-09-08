/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillett <dwillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 17:32:18 by dwillett          #+#    #+#             */
/*   Updated: 2021/08/04 13:25:14 by dwillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define MAX_INT 2147483647
# define ARG_NUMBER_ERROR "ERROR: Wrong number of arguments\n"
# define ARG_ERROR "ERROR: Something wrong with the arguments\n"
# define PROCESS_CREATION_ERROR "ERROR: Failed to create new process\n"
# define SEM_CREATION_ERROR "ERROR: Failed to create semaphore\n"
# define MALLOC_ERROR "ERROR: failed to allocate memory\n"

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define CIAN "\x1b[36m"
# define NONE "\x1b[0m"

# define EAT 7
# define SLEEP 8
# define THINK 9
# define DIE 10
# define TAKE_FORK 11

typedef struct s_philo_arg
{
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			flag;
}				t_philo_arg;

typedef struct s_philo_atributes
{
	int				num;
	int				flag_last;
	struct timeval	start;
	struct timeval	beginning_of_era;
	t_philo_arg		*arg;
	pthread_t		checker;
	sem_t			*fork;
	sem_t			*write;
	int				death_flag;
	int				meal_count;
}						t_philo_atributes;

typedef struct s_dining_room
{
	t_philo_arg			*info;
	t_philo_atributes	*phil;
	pid_t				*prcs;
	sem_t				*fork;
	sem_t				*write;
	struct timeval		start;
}						t_dining_room;

void	init_struct(t_dining_room *all);
void	mysleep(int mili);
void	myprint(int flag, int num, struct timeval start, sem_t *write);
void	eat(t_philo_atributes *tmp);
void	*philo_checker(void *arg);
long	gettime(struct timeval start);
int		malloc_all(t_dining_room *all);
int		ft_strlen(char *str);
int		ft_atoi_p(char *str);
int		print_error(char *str);
int		free_all_and_print_error(t_dining_room *all, char *flag);
int		check_and_fill(char *str, int *info);
int		args_check_and_fill(char **argv, t_philo_arg *info, int flag);
int		process_start(int first, t_dining_room *all);
int		child_main(t_dining_room *all);
int		mommy_main(t_dining_room *all);
int		start_philo(t_dining_room *all);

#endif
