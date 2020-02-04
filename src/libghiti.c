/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libghiti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:19:55 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/04 22:21:17 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
**** reset the value of seen in every node to zero so we can use it for	******
****	    		the number of the ant in the future					******
*/

void	init_paths_with_ants(t_flow *paths)
{
	t_path	*curr;
	t_queue *c_curr;
	t_edge	*e_curr;

	curr = paths->paths;
	while (curr)
	{
		c_curr = curr->edge;
		while (c_curr)
		{
			e_curr = c_curr->edge;
			while (e_curr)
			{
				e_curr->node_dst->seen = 0;
				e_curr->node_src->seen = 0;
				e_curr = e_curr->next;
			}
			c_curr = c_curr->next;
		}
		curr = curr->next;
	}
}

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

	curr = paths->paths;
	while (curr)
	{
		if (!check_path(curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}
