/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:13:37 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/23 04:20:29 by ahimmi           ###   ########.fr       */
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
	int						number_of_times_each_philosopher_must_eat;
	u_long					last_meal;
	int						time_to_sleep;
	pthread_t				thread_philo;
	sem_t					*print;
	sem_t 					*fork;
	sem_t 					*ext;
} t_philosophers;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
} t_pid;


void	philo_create(t_philosophers *lst, t_pid *pids, char **argv, int argc);
int		ft_atoi(const char *str);
u_long	gettime();
void	ft_lstadd_back(t_pid **lst, t_pid *new);
t_pid	*ft_lstlast(t_pid *lst);
t_pid	*ft_lstnew(int pid);
void	detach_threads(t_philosophers *philo);
void	*philo_action1(t_philosophers *lst, t_pid *pid);
void	philo_action2(t_philosophers *lst, t_pid *pid);
void	clear_philo(t_pid *pids, t_philosophers *philo);
int		args_check(int ac, char **av);
void	open_sem(t_philosophers *lst, char **av);
t_pid	*loop_fork(t_philosophers *lst, t_pid *pids);

#endif