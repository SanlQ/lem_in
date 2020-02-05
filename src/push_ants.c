/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:28:36 by magoumi           #+#    #+#             */
/*   Updated: 2020/02/05 00:49:45 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
		if (curr->n_ant && curr->n_ant--)
		{
			// ft_printf("\033[1;34mL%d-%s \033[0m", *i,
			// curr->edge->edge->node_dst->name);
			ft_printf("L%d-%s ", *i,
			curr->edge->edge->node_dst->name);
			ft_push_in_path(curr, *i);
			ants--;
			*i += 1;
			j++;
		}
		curr = curr->next;
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
	// ft_printf("\033[0;34mL%d-%s \033[0m", ant, curr->edge->node_dst->name);
	ft_printf("L%d-%s ", ant, curr->edge->node_dst->name);
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
