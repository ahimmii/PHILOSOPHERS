/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <ahimmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:44:11 by ahimmi            #+#    #+#             */
/*   Updated: 2022/02/10 21:46:22 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


int	ft_atoi(const char *str)
{
	int	i;
	int	ms;
	int	r;

	ms = 1;
	r = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			ms = ms * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = (str[i] - 48) + (r * 10);
		i++;
	}
	return (r * ms);
}
