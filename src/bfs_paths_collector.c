/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_paths_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:56:28 by melalj            #+#    #+#             */
/*   Updated: 2020/02/04 23:15:34 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	insert_mid(t_flow **flow, t_path **path, t_path **curr, t_path **prev)
{
	while ((*curr)->next)
	{
		if ((*path)->size <= (*curr)->size && ((*prev)->next = *path))
		{
			(*path)->next = *curr;
			break ;
		}
		*prev = (!*prev) ? (*flow)->paths : (*prev)->next;
		*curr = (*curr)->next;
	}
}

static t_edge	*bfs_add_path_follow_flow(t_node *node)
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

static t_path	*bfs_add_path(t_graph *g)
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
		prev = NULL;
		curr = flow->paths;
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
				insert_mid(&flow, &path, &curr, &prev);
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
