/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 22:07:41 by melalj            #+#    #+#             */
/*   Updated: 2020/02/05 00:32:54 by melalj           ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_parse		*pp;
	t_node		**nodes;
	int			nodes_c;
	int			i;
	t_graph		*g;
	t_node		**refs;
	size_t		n_ants;
	t_flow		*flow;

	i = 0;
	pp = get_lines(&nodes_c);
	n_ants = (size_t)ft_atoi(pp->line);
	refs = (t_node **)malloc(sizeof(t_node *) * nodes_c);
	nodes = h_table(refs, pp, nodes_c);
	edges_fill(nodes, pp, nodes_c);
	parser_free(pp);
	g = graph_init(refs, nodes, nodes_c, (ac == 2 && ft_strequ(av[1], "-v") ? 1 : 0));
	// visu_init(g);
	// ft_printf("\n\nstarting solving process\n\n");
	flow = bfs(g, n_ants);
	// ft_printf("[%zu]\n", flow->n_paths);
	// curr = flow->paths;
	// while (curr)
	// {
	// 	ft_printf("path: ");
	// 	print_queue(curr->edge);
	// 	curr = curr->next;
	// }
	// ft_printf("\n\n[starting pushing ants]\n\n");
	ant_count(flow, n_ants);
	push_ants(flow, n_ants);
	/*
	 graph_draw(g);
	*/
	return (0);
}
