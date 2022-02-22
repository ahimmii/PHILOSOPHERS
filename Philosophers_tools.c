/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:24:42 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/22 18:12:50 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Philosophers.h"

unsigned int gettime()
{
	struct timeval		time_now;
	u_long				time;
	static u_long		starting_time = 0;

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
	t_philosophers	*tmp;

	while (philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}