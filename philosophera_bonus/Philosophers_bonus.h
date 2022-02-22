/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:13:37 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/22 05:08:45 by ahimmi           ###   ########.fr       */
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
	unsigned long			last_meal;
	int						time_to_sleep;
	pthread_t				thread_philo;
	sem_t					*print;
	sem_t 					*fork;
} t_philosophers;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
} t_pid;


void	philo_create(t_philosophers *lst, int philosophers,char **argv);
int				ft_atoi(const char *str);
unsigned int				gettime();
void			ft_lstadd_back(t_pid **lst, t_pid *new);
t_pid	*ft_lstlast(t_pid *lst);
t_pid			*ft_lstnew(t_pid *data, int i);

#endif