/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:13:37 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/20 00:11:57 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPGERS_H
#define PHILOSOPGERS_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosophers
{
	int						n_of_philo;
	int						id;
	int						time_to_die;
	int						time_to_eat;
	unsigned int			last_meal;
	int						time_to_sleep;
	pthread_t				thread_philo;
	struct	s_philosophers	*next;
	pthread_mutex_t			fork;
	
} t_philosophers;

typedef struct s_pid
{
	int pid;
}

t_philosophers	*philo_create(t_philosophers *lst, int philosophers,char **argv);
int				ft_atoi(const char *str);
unsigned int				gettime();
void			ft_lstadd_back(t_philosophers **lst, t_philosophers *new);
t_philosophers	*ft_lstlast(t_philosophers *lst);
t_philosophers	*ft_lstnew(t_philosophers *data, int i);

#endif