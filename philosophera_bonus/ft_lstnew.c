/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahimmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:06:25 by ahimmi            #+#    #+#             */
/*   Updated: 2021/11/07 15:06:28 by ahimmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

t_pid	*ft_lstnew(int pid)
{
	t_pid	*element;

	element = (t_pid *)malloc(sizeof (t_pid));
	if (!element)
		return (NULL);
	element->pid = pid;
	element->next = NULL;
	return (element);
}
