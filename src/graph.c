/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:43:23 by melalj            #+#    #+#             */
/*   Updated: 2020/02/17 01:33:17 by melalj           ###   ########.fr       */
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
				// g->nodes_lst = ft_memcpy(malloc(sizeof(t_node)),
				// 							curr, sizeof(t_node));
				g->nodes_lst = curr;
				walk = g->nodes_lst;
			}
			else
			{
				// walk->next = ft_memcpy(malloc(sizeof(t_node)),
				// 						curr, sizeof(t_node));
				walk->next = curr;
				walk = walk->next;
			}
			curr = curr->next;
		}
		i++;
	}
	// error_exit(5, g);
	return (g);
}

void	edges_free(t_graph *g)
{
	t_node *node;
	t_node	*node_tmp;
	t_edge *edge;
	t_edge *edge_tmp;

	node = g->nodes_lst;
	while (node)
	{
		edge = node->edges;
		while (edge)
		{
			edge_tmp = edge;
			edge = edge->next;
			free(edge_tmp);
			edge_tmp = NULL;
		}
		// node_tmp = node;
		// free(node_tmp->name);
		// node_tmp->name = 0;
		// free(node_tmp);
		// node_tmp = 0;
		node = node->next;
	}
}

void	nodes_free(t_graph *g)
{
	t_node *node;
	t_node *node_tmp;

	node = g->nodes_lst;
	while (node)
	{
		node_tmp = node;
		node = node->next;
		free(node_tmp->name);
		free(node_tmp);
	}
}

void	graph_free(t_graph *g)
{

	edges_free(g);
	nodes_free(g);
	free(g);
}
