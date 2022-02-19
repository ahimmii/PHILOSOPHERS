/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:33:19 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/19 23:33:20 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

unsigned int gettime()
{
	struct timeval	time_now;
	int				time;
	static int		starting_time = 0;

	gettimeofday(&time_now, NULL);
	time = time_now.tv_sec * 1000;
	time += time_now.tv_usec / 1000;
	if (!starting_time)
		starting_time = time;
	return (time - starting_time);
}