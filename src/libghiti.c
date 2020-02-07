/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libghiti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:19:55 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/07 12:00:43 by melalj           ###   ########.fr       */
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
		// while (e_curr)
		// {
			// ft_printf("%d ", e_curr->node_dst->seen);
			if (e_curr->node_dst->seen && g->sink != e_curr->node_dst)
				i++;
			if (e_curr->node_src->seen)
				i++;
			// e_curr = e_curr->next;
		// }
		curr = curr->next;
	}
		// ft_printf("\n %d\n", i);
	if (i >= 1)
		return (0);
	return (1);
}

int		check_paths(t_flow *paths, t_graph *g)
{
	t_path *curr;
	int		ret;
	
	curr = paths->paths;
	ret = 0;
	// while (curr)
	// {
		if (check_path(curr, g))
			ret = 1;
		// curr = curr->next;
	// }
	// ft_printf("ret : %d\n", ret);
	return (ret);
}
