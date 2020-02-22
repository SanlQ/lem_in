/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_paths_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:56:28 by melalj            #+#    #+#             */
/*   Updated: 2020/02/22 13:43:35 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		insert_mid(t_flow **flow, t_path **path, t_path **curr,
t_path **prev)
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
			curr->origin = 0;
			curr->seen = 0;
			curr->node_dst->seen = 0;
			curr->node_src->seen = 0;
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
	path->n_ant = 0;
	path->edge = NULL;
	while (curr)
	{
		add_to_queue(&(path->edge), curr);
		path->size++;
		curr = bfs_add_path_follow_flow(curr->node_dst);
	}
	return (path);
}

static void		bfs_insert(t_flow *f, t_path **path, t_path **c, t_path **prev)
{
	*prev = NULL;
	*c = f->paths;
	if (!(*c))
		f->paths = *path;
	else
	{
		*c = f->paths;
		*prev = NULL;
		if ((*path)->size <= (*c)->size && (f->paths = *path))
			(*path)->next = *c;
		else
		{
			insert_mid(&f, path, c, prev);
			if (!(*c)->next)
			{
				if ((*path)->size <= (*c)->size && ((*prev)->next = *path))
					(*path)->next = *c;
				else
					(*c)->next = *path;
			}
		}
	}
	f->score += (*path)->size;
	f->n_paths++;
}

t_flow			*bfs_paths_collector(t_graph *g, int n_ants)
{
	t_flow	*flow;
	t_path	*path;
	t_path	*curr;
	t_path	*prev;

	if (!(flow = (t_flow *)malloc(sizeof(t_flow))))
		error_exit(3, NULL);
	flow->n_paths = 0;
	flow->paths = NULL;
	flow->score = 0;
	while ((path = bfs_add_path(g)))
		bfs_insert(flow, &path, &curr, &prev);
	if (!flow->n_paths)
		error_exit(7, NULL);
	flow->score = (flow->score + n_ants) / flow->n_paths - 2;
	return (flow);
}
