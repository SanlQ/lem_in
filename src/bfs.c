/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:33:38 by melalj            #+#    #+#             */
/*   Updated: 2020/02/04 23:08:57 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_queue	*bfs_queue_init(t_graph *g, t_queue **queue)
{
	t_edge *curr;

	*queue = NULL;
	curr = g->start->edges;
	while (curr)
	{
		if (!curr->flow)
			add_to_queue(queue, curr, 0);
		curr = curr->next;
	}
	return (*queue);
}

t_edge	*bfs_queue_add_edges(t_graph *g, t_queue **q, t_queue *q_p, t_edge *e)
{
	t_edge	*curr;
	int		t;

	curr = e;
	while (curr)
	{
		t = 0;
		if ((curr->node_src->seen &&
			((q_p->edge && !q_p->edge->node_src->seen && !curr->node_dst->seen)
				|| (curr->node_dst->seen && !curr->residual->flow))))
			t = 1;
		if (!curr->seen && !curr->flow && curr->node_dst != g->start && !t)
		{
			add_to_queue(q, curr, 0);
			curr->origin = q_p->edge;
			curr->seen = 1;
		}
		if (!curr->flow && curr->node_dst == g->sink)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int		bfs_queue_iter(t_graph *g)
{
	t_queue	*q_curr;
	t_queue	*queue;
	t_edge	*curr;
	int		ret;

	ret = 0;
	curr = NULL;
	q_curr = bfs_queue_init(g, &queue);
	while (q_curr)
	{
		curr = q_curr->edge->node_dst->edges;
		if ((curr = bfs_queue_add_edges(g, &queue, q_curr, curr)) && ++ret)
			break ;
		q_curr = q_curr->next;
	}
	while (ret && curr)
	{
		curr->flow = 1;
		curr->node_dst->seen = 1;
		curr->node_src->seen = 1;
		curr = curr->origin;
	}
	delete_queue(&queue);
	return (ret);
}

t_flow	*bfs(t_graph *g)
{
	t_flow	*flow;

	while (bfs_queue_iter(g))
		;
	flow = bfs_paths_collector(g);
	return (flow);
}
