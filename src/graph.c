/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:03:24 by archid-           #+#    #+#             */
/*   Updated: 2020/01/30 18:29:43 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"


void lstdel_node(void *c, size_t size)
{
	t_edge *edges;
	t_edge *tmp;

	if (!size || !c)
		return ;
	edges = ((t_node *)c)->edges;
	while (edges)
	{
		tmp = edges;
		edges = edges->next;
		free(tmp);
	}
	free(((t_node *)c)->name);
}

t_graph *graph_init(t_node **refs, t_node **nodes, int nodes_c, int v)
{
	t_graph *g;
	t_node	*curr;
	t_node	*walk;

	size_t	i;

	i = 0;
	g = (t_graph *)ft_memalloc(sizeof(t_graph));
	g->nodes_ref = refs;
	g->max_c.x = 0;
	g->max_c.y = 0;
	g->v_visu = v;
	g->n_nodes = nodes_c;
	g->start = NULL;
	g->sink = NULL;
	if (v)
		g->data = (t_dvisu *)malloc(sizeof(t_dvisu));
	while ((int)i < nodes_c)
	{
		curr = nodes[i];
		while (curr)
		{
			if (curr->type == NODE_START)
				g->start = curr;
			else if (curr->type == NODE_END)
				g->sink = curr;
			if (g->nodes_lst == NULL)
			{
				g->nodes_lst = ft_memcpy(malloc(sizeof(t_node)),
											curr, sizeof(t_node));
				walk = g->nodes_lst;
			}
			else
			{
				walk->next = ft_memcpy(malloc(sizeof(t_node)),
										curr, sizeof(t_node));
				walk = walk->next;
			}
			g->max_c.x = (g->max_c.x > curr->cords.x ?
							g->max_c.x : curr->cords.x);
			g->max_c.y = (g->max_c.y > curr->cords.y ?
							g->max_c.y : curr->cords.y);
			curr = curr->next;
		}
		i++;
	}
	if (!(g->start) || !(g->sink))
	{
		ft_printf("error no start or end\n");
		exit(1);
	}
	return (g);
}

void	graph_free(t_graph *g)
{
	t_node *node;
	t_node *nwalk;
	t_edge *edge;
	t_edge *tmp;
	t_edge *ewalk;

	nwalk = g->nodes_lst;
	while (nwalk)
	{
		node = nwalk;
		nwalk = nwalk->next;
		ewalk = node->edges;
		while (ewalk)
		{
			/* FIXME:  */
			edge = ewalk;
			ewalk = ewalk->next;
			if (edge->node_src->edges)
			{
				tmp = edge->node_dst->edges;
				edge->node_dst->edges = NULL;
				free(tmp);
			}
			free(edge->node_src->edges);
			edge->node_src->edges = NULL;
		}
		free(node->name);
		free(node);
	}
	free(g);
}

