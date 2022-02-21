/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:46:42 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/21 18:54:14 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

t_philosophers	*philo_create(t_philosophers *lst, int philosophers, char **argv)
{
	t_philosophers	*new;
	int i;

	i = 1;
	while (i <= philosophers)
	{
		ft_lstadd_back(&lst, ft_lstnew(new, i));
		i++;
	}
	ft_lstlast(lst)->next = lst;
	i = 1;
	while (i <= philosophers)
	{
		lst->id = i;
		lst->time_to_die = ft_atoi(argv[2]);
		lst->time_to_eat = ft_atoi(argv[3]);
		lst->time_to_sleep = ft_atoi(argv[4]);
		lst->last_meal = 0;
		lst->n_of_philo = philosophers;
		lst = lst->next;
		i++;
	}
	return (lst);
}

void	*philo_action(t_philosophers	*lst)
{
	lst->last_meal = 0;
	while (1)
	{
		if (gettime() == 0 && lst->id % 2 == 0 )
			usleep(lst->time_to_eat * 1000);
		sem_wait(lst->fork);
		//pthread_mutex_lock(&lst->fork);
		printf("%d %d  hast taken a fork 🍴\n", gettime(), lst->id);
		sem_wait(lst->fork);
		//pthread_mutex_lock(&lst->next->fork);
		printf("%d %d  hast taken a fork 🍴\n", gettime(), lst->id);
		printf("%d %d  is eating 🍔\n", gettime(), lst->id);
		lst->last_meal = gettime();
		usleep(lst->time_to_eat * 1000);
		printf("%d %d  is sleeping 😴\n", gettime(), lst->id);
		sem_post(lst->fork);
		sem_post(lst->fork);
		//pthread_mutex_unlock(&lst->fork);
		//pthread_mutex_unlock(&lst->next->fork);
		usleep(lst->time_to_sleep * 1000);
		printf("%d %d  is thinking 🤔\n", gettime(), lst->id);
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
			printf("%d %d  died 😵\n", gettime(), philosopher->id);
			break;
		}
		philosopher = philosopher->next;
	}
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_philosophers	*lst;
	int				philo;
	int				i;
    int             pid;
	sem_t			*forks;
	
	i = 1;
	philo = ft_atoi(argv[1]);
	forks = sem_open("fork", O_CREAT | O_EXCL, 666, philo);
	pid = getpid();
	if (argc >= 2)
	{
		lst = philo_create(lst, philo, argv);
		while (i <= philo)
		{	
			if (pid == getpid())
			{
				//lst->fork = forks;
				lst->pid = fork();
				lst = lst->next;
			}
			i++;
		}
		if (pid != getpid())
		{
		 	philo_action(lst);
		}
		// pthread_create(&lst->thread_philo, NULL, &tracker, lst);
		// pthread_join(lst->thread_philo, NULL);
		// pthread_kill(lst->thread_philo, 0);
	}
	wait(NULL);
}
