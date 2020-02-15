/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 22:07:41 by melalj            #+#    #+#             */
/*   Updated: 2020/02/15 05:24:47 by magoumi          ###   ########.fr       */
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

void	ft_check_arguments(t_graph *g, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-s"))
			g->color = 1;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_parse		*pp;
	t_node		**nodes;
	int			nodes_c;
	t_graph		*g;
	int			n_ants;
	t_flow		*flow;

	pp = get_lines(&nodes_c);
	n_ants = ft_atoi(pp->line);
	nodes = h_table(pp, nodes_c);
	edges_fill(nodes, pp, nodes_c);
	parser_free(pp);
	g = graph_init(nodes, nodes_c);
	flow = bfs(g, n_ants);
	if (argc == 2)
		ft_check_arguments(g, argv);
	ant_count(flow, n_ants);
	push_ants(flow, n_ants, g);
	return (0);
}
