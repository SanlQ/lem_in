/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:06:04 by melalj            #+#    #+#             */
/*   Updated: 2020/02/07 17:13:52 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	edge_bfs_iter(t_graph *g, t_edge *edge)
{
	if (edge->v_c < 0 || edge->residual->v_c < 0)
	{
		SDL_SetRenderDrawColor(g->data->rend, 255, 150, 255, 255);
		if (edge->v_c == -1 || edge->residual->v_c == -1)
			SDL_Delay(300);
		edge->v_c--;
		edge->residual->v_c--;
		return (1);
	}
	else
		return (0);
}

int	edge_bfs_path(t_graph *g, t_edge *edge)
{
	int change;

	change = (g->data->path_n != 0) ? g->data->path_n * 100 : 1;
	change = (edge->path_n == -1) ? change : edge->path_n;
	if (edge->v_c > 0 || edge->residual->v_c > 0)
	{
		SDL_SetRenderDrawColor(g->data->rend, 255 * change, 150 * change,
		1 * change, 255);
		if (edge->v_c == 1 || edge->residual->v_c == 1)
			SDL_Delay(300);
		edge->path_n = (edge->path_n == -1) ? g->data->path_n : edge->path_n;
		edge->residual->path_n = (edge->path_n == -1) ? g->data->path_n :
		edge->path_n;
		edge->v_c++;
		edge->residual->v_c++;
		return (1);
	}
	else
		return (0);
}

int	edges_draw(t_graph *g, t_node *node)
{
	t_edge	*curr;
	int		*ranges_x;
	int		*ranges_y;
	t_cords	src;
	t_cords	dst;

	curr = node->edges;
	ranges_x = range_comp(0, g->max_c.x, 0, g->data->w_width - 50);
	src.x = map(node->cords.x, ranges_x) + 10;
	ranges_y = range_comp(0, g->max_c.y, 0, g->data->w_height - 100 - 250);
	src.y = map(node->cords.y, ranges_y) + 10;
	while (curr)
	{
		if (ft_strequ(curr->node_src->name, "4") && ft_strequ(curr->node_dst->name, "7"))
			ft_printf("path_n : %d --- color %d\n", curr->path_n, curr->color.hex);
		curr->color.hex = (g->data->f == 1 && curr->path_n == -1) ? 0 : curr->color.hex;
		if (curr->color.hex)
		{
			SDL_SetRenderDrawColor(g->data->rend, curr->color.rbg[2], curr->color.rbg[1], curr->color.rbg[0], 255);
			if (curr->v_c == 1 || curr->v_c == -1 || curr->residual->v_c == 1 || curr->residual->v_c == -1)
				SDL_Delay(200);
			curr->v_c += 5;
			curr->residual->v_c += 5;
		}
		else
			SDL_SetRenderDrawColor(g->data->rend, 150, 0, 255, 255);
		dst.x = map(curr->node_dst->cords.x, ranges_x) + 10;
		dst.y = map(curr->node_dst->cords.y, ranges_y) + 10;
		SDL_RenderDrawLine(g->data->rend, src.x, src.y, dst.x, dst.y);
		curr = curr->next;
	}
	free(ranges_x);
	free(ranges_y);
	SDL_SetRenderDrawColor(g->data->rend, 0, 0, 0, 255);
	return (0);
}
