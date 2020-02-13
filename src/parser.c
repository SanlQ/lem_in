/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:54:11 by melalj            #+#    #+#             */
/*   Updated: 2020/02/13 23:28:41 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_node		*new_node(int index, t_parse *line, int prop)
{
	t_node	*new_n;
	char	**s_line;

	s_line = ft_strsplit(line->line, ' ');
	new_n = (t_node *)malloc(sizeof(t_node));
	new_n->name = ft_strdup(s_line[0]);
	new_n->cords.x = ft_atoi(s_line[1]);
	new_n->cords.y = ft_atoi(s_line[2]);
	free_tab(s_line);
	new_n->edges = NULL;
	new_n->next = NULL;
	new_n->type = NODE_DEFAULT;
	new_n->seen = false;
	new_n->index = index;
	if (prop > 1)
		new_n->type = (prop == 2 ? NODE_START : NODE_END);
	return (new_n);
}

int			add_node(t_node **lst_node, t_parse *lines, int nodes_c, int prop)
{
	static size_t	index = 0;
	char			**s_lines;
	t_node			*curr;
	int				hash_h;

	s_lines = ft_strsplit(lines->line, ' ');
	hash_h = hash((unsigned char*)s_lines[0]) % nodes_c;
	if (!lst_node[hash_h])
	{
		lst_node[hash_h] = new_node(index, lines, prop);
		free_tab(s_lines);
		return (1);
	}
	curr = lst_node[hash_h];
	if (ft_strequ((curr)->name, s_lines[0]) && free_tab(s_lines))
		return (0);
	while (curr->next)
	{
		if (ft_strequ((curr)->name, s_lines[0]) && free_tab(s_lines))
			return (0);
		(curr) = (curr)->next;
	}
	(curr)->next = new_node(index, lines, prop);
	free_tab(s_lines);
	return (1);
}

/*
*****	get node based on a hash ******
*/

t_node		*get_node(t_node **lst_node, char *name, int nodes_c)
{
	int		hash_h;
	t_node	*curr;

	hash_h = hash((unsigned char*)name) % nodes_c;
	curr = lst_node[hash_h];
	while (curr)
	{
		if (ft_strequ((curr)->name, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
**  add the edge and it's residual
*/

int			add_edge(t_node *src, t_node *dst, bool is_residual, t_edge *e)
{
	t_edge *curr;
	t_edge *tmp;

	is_residual ^= true;
	if (src->edges == NULL)
	{
		src->edges = (t_edge *)malloc(sizeof(t_edge));
		tmp = src->edges;
	}
	else
	{
		curr = src->edges;
			if ((ft_strequ(curr->node_src->name, src->name)
					&& ft_strequ(curr->node_dst->name, dst->name))
					|| (ft_strequ(curr->node_src->name, dst->name)
							&& ft_strequ(curr->node_dst->name, src->name)))
			{
				exit(1);
			}
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = (t_edge *)malloc(sizeof(t_edge));
		tmp = curr->next;
	}
	tmp->node_dst = dst;
	tmp->node_src = src;
	tmp->origin = NULL;
	tmp->flow = 0;
	tmp->next = NULL;
	if (is_residual == false)
	{
		tmp->residual = e;
		e->residual = tmp;
		e->seen = 0;
		tmp->seen = 0;
		return (0);
	}
	add_edge(dst, src, true, tmp);
	return (1);
}

int			edges_fill(t_node **lst_node, t_parse *lines, int nodes_c)
{
	char	**s_lines;
	t_node	*node[2];
	int		d;

	d = 0;
	while (lines && lines->type < 2 && ++d && ft_printf("%s\n", lines->line))
		lines = lines->next;
	if (d < 2 || !lines)
		error_exit(2, NULL);
	while (lines)
	{
		if (lines->line[0] == '#' && ((lines = lines->next) != NULL ? 1 : 1))
			continue;
		if (!(s_lines = ft_strsplit(lines->line, '-')))
			error_exit(3, NULL);
		node[0] = get_node(lst_node, s_lines[0], nodes_c);
		node[1] = get_node(lst_node, s_lines[1], nodes_c);
		free_tab(s_lines);
		if (!node[0] || !node[1])
			error_exit(4, NULL);
		add_edge(node[0], node[1], false, NULL);
		lines = lines->next;
	}
	return (1);
}
