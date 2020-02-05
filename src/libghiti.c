/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libghiti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:19:55 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/05 01:18:38 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
******		check if a path is empty or not			******
*/

int		check_path(t_path *paths)
{
	int		i;
	t_queue *curr;
	t_edge	*e_curr;

	curr = paths->edge;
	i = 0;
	while (curr)
	{
		e_curr = curr->edge;
		while (e_curr)
		{
			if (e_curr->node_dst->seen)
				i++;
			if (e_curr->node_src->seen)
				i++;
			e_curr = e_curr->next;
		}
		curr = curr->next;
	}
	if (i > 1)
		return (0);
	return (1);
}

int		check_paths(t_flow *paths)
{
	t_path *curr;
	int		ret;
	
	curr = paths->paths;
	ret = 0;
	while (curr)
	{
		if (check_path(curr))
			ret = 1;
		curr = curr->next;
	}
	return (ret);
}
