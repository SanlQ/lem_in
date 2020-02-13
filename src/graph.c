/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:43:23 by melalj            #+#    #+#             */
/*   Updated: 2020/02/13 23:43:48 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	lstdel_node(void *c, size_t size)
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

t_graph	*graph_init(t_node **nodes, int nodes_c)
{
	t_graph *g;
	t_node	*curr;
	t_node	*walk;
	size_t	i;

	i = 0;
	g = (t_graph *)ft_memalloc(sizeof(t_graph));
	g->n_nodes = nodes_c;
	g->start = NULL;
	g->sink = NULL;
	g->color = 0;
	while ((int)i < nodes_c)
	{
		curr = nodes[i];
		while (curr)
		{
			g->start = (curr->type == NODE_START) ? curr : g->start;
			g->sink = (curr->type == NODE_END) ? curr : g->sink;
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
			curr = curr->next;
		}
		i++;
	}
	// error_exit(5, g);
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
	while (nwalk && (node = nwalk))
	{
		nwalk = nwalk->next;
		ewalk = node->edges;
		while (ewalk && (edge = ewalk))
		{
			ewalk = ewalk->next;
			if (edge->node_src->edges && (tmp = edge->node_dst->edges))
				free(tmp);
			free(edge->node_src->edges);
			edge->node_src->edges = NULL;
		}
		free(node->name);
		free(node);
	}
	free(g);
}
