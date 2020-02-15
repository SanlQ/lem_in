/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libghiti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:19:55 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/15 11:02:52 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
******		check if a path is empty or not			******
*/

int		check_path(t_path *paths, t_graph *g)
{
	int		i;
	t_queue *curr;
	t_edge	*e_curr;

	curr = paths->edge;
	i = 0;
	while (curr)
	{
		e_curr = curr->edge;
		if (e_curr->node_dst->seen && g->sink != e_curr->node_dst)
			i++;
		if (e_curr->node_src->seen)
			i++;
		curr = curr->next;
	}
	if (i >= 1)
		return (0);
	return (1);
}

int		check_paths(t_flow *paths, t_graph *g)
{
	t_path	*curr;
	int		ret;

	curr = paths->paths;
	ret = 0;
	if (check_path(curr, g))
		ret = 1;
	return (ret);
}
