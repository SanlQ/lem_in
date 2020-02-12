/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 22:07:41 by melalj            #+#    #+#             */
/*   Updated: 2020/02/11 00:17:48 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	parser_free(t_parse *p)
{
	t_parse *walk;
	t_parse *hold;

	walk = p;
	while (walk)
	{
		hold = walk;
		walk = walk->next;
		free(hold->line);
		free(hold);
	}
}

int		main(void)
{
	t_parse		*pp;
	t_node		**nodes;
	int			nodes_c;
	t_graph		*g;
	int		n_ants;
	t_flow		*flow;

	pp = get_lines(&nodes_c);
	n_ants = ft_atoi(pp->line);
	nodes = h_table(pp, nodes_c);
	edges_fill(nodes, pp, nodes_c);
	parser_free(pp);
	g = graph_init(nodes, nodes_c);
	flow = bfs(g, n_ants);
	ant_count(flow, n_ants);
	push_ants(flow, n_ants, g);
	return (0);
}
