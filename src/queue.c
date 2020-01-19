/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:34:42 by melalj            #+#    #+#             */
/*   Updated: 2020/01/18 00:47:39 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void add_to_queue(t_queue **queue, t_edge *edge, int head)
{
	t_queue *curr;

	if (!*queue)
	{
		*queue = (t_queue *)malloc(sizeof(t_queue));
		(*queue)->edge = edge;
		(*queue)->next = NULL;
	}
	else
	{
		if (!head)
		{
			curr = (*queue);
			while (curr->next)
				curr = curr->next;
			curr->next = (t_queue *)malloc(sizeof(t_queue));
			curr->next->edge = edge;
			curr->next->next = NULL;
		}
		else
		{
			curr = (t_queue *)malloc(sizeof(t_queue));
			curr->edge = edge;
			curr->next = (*queue);
			(*queue) = curr;
		}
	}
}

void	print_queue(t_queue *queue)
{
	t_queue *curr;

	curr = queue;
	ft_printf("%s ", curr->edge->node_src->name);
	while (curr && curr->edge)
	{
		ft_printf("%s ", curr->edge->node_dst->name);
		curr = curr->next;
	}
	ft_printf("\n");
}

void	delete_queue(t_queue **queue)
{
	t_queue *curr;

	while (*queue)
	{
		curr = *queue;
		curr->edge->seen = 0;
		curr->edge->origin = NULL;
		*queue = (*queue)->next;
		free(curr);
	}
}