/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:33:38 by melalj            #+#    #+#             */
/*   Updated: 2020/01/20 21:16:02 by magoumi          ###   ########.fr       */
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

t_edge	*bfs_queue_add_edges(t_graph *g, t_queue **q, t_queue *q_p, t_edge *edge)
{
	t_edge *curr;
	int t;

	curr = edge;
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
	q_curr = NULL;
	queue = NULL;
	curr = NULL;
	// ft_printf("start %s --- end %s\n", g->start->name, g->sink->name);
	q_curr = bfs_queue_init(g, &queue);
	// print_queue(queue);
	while (q_curr)
	{
		curr = q_curr->edge->node_dst->edges;
		if ((curr = bfs_queue_add_edges(g, &queue, q_curr, curr)) && (ret = 1))
			break ;
		q_curr = q_curr->next;
	}
	// if (ret)
	// 	ft_printf("%s ", curr->node_dst->name);
	while (ret && curr)
	{
		// ft_printf("%s ", curr->node_src->name);
		curr->flow = 1;
		curr->node_dst->seen = 1;
		curr->node_src->seen = 1;
		curr = curr->origin;
	}
	// ft_printf("\n");
	delete_queue(&queue);
	return (ret);
}

t_edge *bfs_add_path_follow_flow(t_node *node)
{
	t_edge *curr;

	curr = node->edges;
	while (curr)
	{
		if (curr->flow && curr->residual->flow)
		{
			curr->flow = 0;
			curr->residual->flow = 0;
		}
		if (curr->flow)
		{
			curr->flow = 0;
			break ;
		}
		curr = curr->next;
	}
	return (curr);
}

t_path	*bfs_add_path(t_graph *g)
{
	t_path *path;
	t_edge *curr;

	if (!(curr = bfs_add_path_follow_flow(g->start)))
		return (NULL);
	path = (t_path *)malloc(sizeof(t_path));
	path->next = NULL;
	path->size = 0;
	path->edge = NULL;
	while (curr)
	{
		add_to_queue(&(path->edge), curr, 0);
		path->size++;
		curr = bfs_add_path_follow_flow(curr->node_dst);
	}
	return (path);
}

t_flow	*bfs_paths_collector(t_graph *g)
{
	t_flow	*flow;
	t_path	*path;
	t_path	*curr;
	t_path	*prev;

	flow = (t_flow *)malloc(sizeof(t_flow));
	flow->n_paths = 0;
	flow->paths = NULL;
	while ((path = bfs_add_path(g)))
	{
		curr = flow->paths;
		prev = NULL;
		if (!curr)
			flow->paths = path;
		else
		{
			curr = flow->paths;
			prev = NULL;
			if (path->size <= curr->size && (flow->paths = path))
				path->next = curr;
			else
			{
				while (curr->next)
				{
					if (path->size <= curr->size && (prev->next = path))
					{
						path->next = curr;
						break ;
					}
					prev = (!prev) ? flow->paths : prev->next;
					curr = curr->next;
				}
				if (!curr->next)
				{
					if (path->size <= curr->size && (prev->next = path))
						path->next = curr;
					else
						curr->next = path;
				}
			}
		}
		flow->n_paths++;
	}
	return (flow);
}

t_flow	*bfs(t_graph *g)
{
	t_flow	*flow;

	while (bfs_queue_iter(g))
		;
	flow = bfs_paths_collector(g);
	return (flow);
}
