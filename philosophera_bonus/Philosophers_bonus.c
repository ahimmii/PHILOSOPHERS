/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:46:42 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/23 04:23:36 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	*philo_action1(t_philosophers *lst, t_pid *pid)
{
	lst->last_meal = 0;
	while (1)
	{
		if (gettime() == 0 && lst->id % 2 == 0)
			usleep(lst->time_to_eat * 1000);
		sem_wait(lst->fork);
		sem_wait(lst->print);
		printf("%ld %d  hast taken a fork\n", gettime(), lst->id);
		sem_post(lst->print);
		sem_wait(lst->fork);
		sem_wait(lst->print);
		printf("%ld %d  hast taken a fork\n", gettime(), lst->id);
		printf("%ld %d  is eating\n", gettime(), lst->id);
		sem_post(lst->print);
		lst->last_meal = gettime();
		usleep(lst->time_to_eat * 1000);
		if (lst -> number_of_times_each_philosopher_must_eat > 0)
			lst -> number_of_times_each_philosopher_must_eat--;
		philo_action2(lst, pid);
	}
	return (NULL);
}

void	philo_action2(t_philosophers *lst, t_pid *pid)
{
	sem_wait(lst->print);
	printf("%ld %d  is sleeping\n", gettime(), lst->id);
	sem_post(lst->print);
	sem_post(lst->fork);
	sem_post(lst->fork);
	usleep(lst->time_to_sleep * 1000);
	sem_wait(lst->print);
	printf("%ld %d  is thinking\n", gettime(), lst->id);
	sem_post(lst->print);
}

void	*tracker(void *data)
{
	t_philosophers	*philosopher;

	philosopher = (t_philosophers *)data;
	while (1)
	{
		if (philosopher->number_of_times_each_philosopher_must_eat == 0)
		{
			sem_wait(philosopher->print);
			sem_close(philosopher->fork);
			sem_close(philosopher->print);
			sem_post(philosopher->ext);
			exit(0);
		}
		if (philosopher->last_meal + philosopher->time_to_die < gettime())
		{
			sem_wait(philosopher->print);
			printf("%ld %d  died\n", gettime(), philosopher->id);
			sem_post(philosopher->ext);
			exit(0);
		}
		usleep(1000);
	}
	return (NULL);
}

t_pid	*loop_fork(t_philosophers *lst, t_pid *pids)
{
	int	i;
	int	pid;

	i = 0;
	while (++i <= lst->n_of_philo)
	{	
		lst->id = i;
		pid = fork();
		if (pid == 0)
		{
			pthread_create(&lst->thread_philo, NULL, &tracker, lst);
			philo_action1(lst, pids);
		}
		ft_lstadd_back(&pids, ft_lstnew(pid));
	}
	return (pids);
}

int	main(int argc, char *argv[])
{
	t_philosophers	*lst;
	int				i;
	int				pid;
	t_pid			*pids;

	i = 0;
	if (args_check(argc, argv))
		return (1);
	pids = NULL;
	lst = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (argc >= 2)
	{
		open_sem(lst, argv);
		philo_create(lst, pids, argv, argc);
		pids = loop_fork(lst, pids);
		clear_philo(pids, lst);
	}
}
