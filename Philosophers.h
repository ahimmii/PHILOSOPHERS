/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 01:13:37 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/23 04:41:33 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosophers
{
	int						id;
	int						n_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	unsigned long			last_meal;
	pthread_t				thread_philo;
	pthread_mutex_t			fork;
	pthread_mutex_t			print;
	struct s_philosophers	*next;
}	t_philosophers;

t_philosophers	*philo_create(t_philosophers *lst, \
	int philosophers, char **argv, int argc);
int				ft_atoi(const char *str);
unsigned int	gettime(void);
void			ft_lstadd_back(t_philosophers **lst, t_philosophers *new);
t_philosophers	*ft_lstlast(t_philosophers *lst);
t_philosophers	*ft_lstnew(t_philosophers *data, int i);
void			detach_threads(t_philosophers *philo);
void			clear_philo(t_philosophers *philo);
int				args_check(int ac, char **av);

#endif