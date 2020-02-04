/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:28:36 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/04 15:03:51 by magoumi          ###   ########.fr       */
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

/*
****** push ants to the start of everypath *****
*/

void	ft_push_in_path(t_path *path, int i)
{
	path->edge->edge->node_dst->seen = i;
}

size_t	push_ants_to_start(size_t ants, t_flow *paths, int *i)
{
	size_t	j;
	t_path	*curr;

	if (!ants)
		return (0);
	curr = paths->paths;
	j = 0;
	while (curr && j < paths->n_paths && ants)
	{
		ft_printf("\033[1;34mL%d-%s \033[0m", *i,
		curr->edge->edge->node_dst->name);
		ft_push_in_path(curr, *i);
		curr = curr->next;
		ants--;
		*i += 1;
		j++;
	}
	return (j);
}

int		push_to_next(t_queue *curr)
{
	int	ant;
	int a;

	a = 0;
	if (curr->next)
		if (curr->edge->node_dst->seen != 0)
			a = push_to_next(curr->next);
	ant = curr->edge->node_src->seen;
	if (!ant)
		return (a ? 1 : 0);
	curr->edge->node_dst->seen = ant;
	ft_printf("\033[0;34mL%d-%s \033[0m", ant, curr->edge->node_dst->name);
	curr->edge->node_src->seen = 0;
	return (1);
}

/*
**	craete a while loop to loop thro the path and push every single ant **
*/

void	push_ants_in_path(t_path *path)
{
	t_queue *curr;

	curr = path->edge->next;
	while (curr && curr->next)
	{
		if (push_to_next(curr))
			break ;
		curr = curr->next;
	}
}

void	push_ants(t_flow *paths, size_t n_ants)
{
	size_t	ants;
	int		i;
	int		d;
	t_path	*curr;

	ants = n_ants;
	init_paths_with_ants(paths);
	i = 1;
	d = 0;
	while (i)
	{
		curr = paths->paths;
		while (curr)
		{
			push_ants_in_path(curr);
			curr = curr->next;
		}
		ants -= push_ants_to_start(ants, paths, &i);
		ft_printf("\n");
		if (check_paths(paths))
			break ;
	}
}
