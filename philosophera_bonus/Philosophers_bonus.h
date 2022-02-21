/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:13:37 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/21 18:50:07 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPGERS_BONUS_H
#define PHILOSOPGERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

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
	int						pid;
	sem_t 					*fork;
	
} t_philosophers;

t_philosophers	*philo_create(t_philosophers *lst, int philosophers,char **argv);
int				ft_atoi(const char *str);
unsigned int				gettime();
void			ft_lstadd_back(t_philosophers **lst, t_philosophers *new);
t_philosophers	*ft_lstlast(t_philosophers *lst);
t_philosophers	*ft_lstnew(t_philosophers *data, int i);

#endif