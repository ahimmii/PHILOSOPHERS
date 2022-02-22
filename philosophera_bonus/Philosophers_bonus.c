/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:46:42 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/22 19:06:31 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

t_pid	*pid_new(void)
{
	t_pid	*new;

	new = (t_pid *) malloc(sizeof(t_pid));
	new -> next = NULL;
	return (new);
}

void	philo_create(t_philosophers *lst, int philosophers, char **argv)
{
		lst->n_of_philo = ft_atoi(argv[1]);
		lst->time_to_die = ft_atoi(argv[2]);
		lst->time_to_eat = ft_atoi(argv[3]);
		lst->time_to_sleep = ft_atoi(argv[4]);
		lst->last_meal = 0;
}

void	*philo_action(t_philosophers *lst, t_pid *pid)
{
	lst->last_meal = 0;
	while (1)
	{
		if (gettime() == 0 && lst->id % 2 == 0 )
		  	usleep(lst->time_to_eat * 1000);
		sem_wait(lst->fork);
		sem_wait(lst->print);
		printf("%ld %d  hast taken a fork 🍴\n", gettime(), lst->id);
		sem_post(lst->print);
		sem_wait(lst->fork);
		sem_wait(lst->print);
		printf("%ld %d  hast taken a fork 🍴\n", gettime(), lst->id);
		printf("%ld %d  is eating 🍔\n", gettime(), lst->id);
		sem_post(lst->print);
		lst->last_meal = gettime();
		usleep(lst->time_to_eat * 1000);
		sem_wait(lst->print);
		printf("%ld %d  is sleeping 😴\n", gettime(), lst->id);
		sem_post(lst->print);
		sem_post(lst->fork);
		sem_post(lst->fork);
		usleep(lst->time_to_sleep * 1000);
		sem_wait(lst->print);
		printf("%ld %d  is thinking 🤔\n", gettime(), lst->id);
		sem_post(lst->print);
	}
	return (NULL);
}


void	*tracker(void *data)
{
	t_philosophers *philosopher;

	philosopher = (t_philosophers *)data;
	while (1)
	{
		if (gettime() - philosopher->last_meal > philosopher->time_to_die + 5)
		{
			sem_wait(philosopher->print);
			printf("%ld %d  died 😵\n", gettime(), philosopher->id);
			exit(0);
		}
	}
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_philosophers	*lst;
	int				philo;
	int				i;
    int             pid;
	t_pid			*pids;
	
	i = 0;
	philo = ft_atoi(argv[1]);
	sem_unlink("fork");
	sem_unlink("print");
	pids = (t_pid *)malloc(sizeof(t_pid));
	lst = (t_philosophers *)malloc(sizeof(t_philosophers));
	lst->fork = sem_open("fork", O_CREAT | O_EXCL, 666, philo);
	lst->print = sem_open("print", O_CREAT | O_EXCL, 666, 1);
	pid = getpid();
	if (argc >= 2)
	{
		philo_create(lst, philo, argv);
		while (++i <= philo)
		{	
			if (pid == getpid())
			{
				lst->id = i;
				pids->pid = fork();
				ft_lstadd_back(&pids,pid_new());
				pids = pids->next;
			}
		}
		if (pid != getpid())
		{
			pthread_create(&lst->thread_philo, NULL, &tracker, lst);
			philo_action(lst,pids);
		}
	}
	// while (pids)
	// {
	// 	kill(pids->pid, SIGQUIT);
	// 	pids = pids->next;
	// }
	wait(NULL);
}
