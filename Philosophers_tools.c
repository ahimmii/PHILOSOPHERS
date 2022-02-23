/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:24:42 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/23 04:35:24 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

unsigned int	gettime(void)
{
	struct timeval			time_now;
	unsigned long			time;
	static unsigned long	starting_time = 0;

	gettimeofday(&time_now, NULL);
	time = time_now.tv_sec * 1000;
	time += time_now.tv_usec / 1000;
	if (!starting_time)
		starting_time = time;
	return (time - starting_time);
}

void	detach_threads(t_philosophers *philo)
{
	int		i;

	i = 0;
	while (i <= philo->n_of_philo)
	{
		pthread_detach(philo->thread_philo);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		i++;
	}
}

void	clear_philo(t_philosophers *philo)
{
	t_philosophers	*next;

	next = philo;
	free(philo);
	philo = philo->next;
	while (next != philo && philo != NULL)
	{
		free(philo);
		philo = philo->next;
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
