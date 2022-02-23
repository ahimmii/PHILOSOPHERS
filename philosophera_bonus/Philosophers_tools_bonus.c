/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:33:19 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/23 04:31:50 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

u_long	gettime(void)
{
	struct timeval	time_now;
	u_long			time;
	static u_long	starting_time = 0;

	gettimeofday(&time_now, NULL);
	time = time_now.tv_sec * 1000;
	time += time_now.tv_usec / 1000;
	if (!starting_time)
		starting_time = time;
	return (time - starting_time);
}

void	clear_philo(t_pid *pids, t_philosophers *philo)
{
	sem_wait(philo->ext);
	free(philo);
	sem_close(philo -> fork);
	sem_close(philo -> print);
	while (pids)
	{
		kill(pids->pid, SIGQUIT);
		pids = pids->next;
	}
}

int	args_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
		return (write(STDERR_FILENO, "Error:\nArguments needed\n", 24));
	if (ac > 6)
		return (write(STDERR_FILENO, "Error:\nToo many args\n", 21));
	while (i < ac)
		if (ft_atoi(av[i++]) <= 0)
			return (write(STDERR_FILENO, "Error:\nArgument not valid\n", 28));
	return (0);
}

void	philo_create(t_philosophers *lst, t_pid *pids, char **argv, int argc)
{
	lst->n_of_philo = ft_atoi(argv[1]);
	lst->time_to_die = ft_atoi(argv[2]);
	lst->time_to_eat = ft_atoi(argv[3]);
	lst->time_to_sleep = ft_atoi(argv[4]);
	lst->number_of_times_each_philosopher_must_eat = -1;
	lst->last_meal = 0;
	if (argc == 6)
		lst->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void	open_sem(t_philosophers *lst, char **av)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("ext");
	lst->fork = sem_open("fork", O_CREAT | O_EXCL, 666, ft_atoi(av[1]));
	lst->print = sem_open("print", O_CREAT | O_EXCL, 666, 1);
	lst->ext = sem_open("ext", O_CREAT | O_EXCL, 666, 0);
}
