/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:09:55 by melalj            #+#    #+#             */
/*   Updated: 2020/02/05 00:59:57 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include "./visu_lib/SDL_LIB/2.0.10/include/SDL2/SDL.h"
# include "./visu_lib/SDL_IMG_LIB/include/SDL2/SDL_image.h"

/*
********************************** data types **********************************
*/


typedef struct	s_cords
{
	int x;
	int y;
}				t_cords;

typedef enum				e_node_type
{
	NODE_DEFAULT = 1,
	NODE_START, NODE_END
}							t_node_type;


typedef struct s_node		t_node;
struct						s_node
{
	char				*name;
	size_t				index;
	t_cords				cords;
	enum e_node_type	type;

	int					seen;

	struct s_edge		*edges;
	struct s_node		*next;
};

typedef union	u_rgb
{
	int		hex;
	char	rbg[4];
}				t_rgb;

typedef struct s_edge		t_edge;
struct						s_edge
{
	int				seen;
	int				flow;

	int				v_c;
	int				path_n;
	int				drawn;
	t_rgb			color;

	struct s_edge	*residual;
	struct s_node	*node_dst;
	struct s_node	*node_src;
	struct s_edge	*origin;
	struct s_edge	*next;
};

typedef struct s_dvisu		t_dvisu;
typedef struct s_flow		t_flow;
typedef struct s_graph		t_graph;
struct						s_graph
{
	t_node			*nodes_lst;
	t_node			**nodes_ref;
	size_t			n_nodes;
	t_cords			max_c;
	struct s_node	*start;
	struct s_node	*sink;
	t_dvisu			*data;
	t_flow			*flows;
	int				v_visu;
};

typedef struct s_parse		t_parse;
struct	s_parse
{
	char			*line;
	t_node_type		prop;
	int				type;
	struct s_parse	*next;
};

typedef struct				s_queue
{
	t_edge			*edge;
	struct s_queue	*next;
}							t_queue;

typedef struct				s_path
{
	t_queue			*edge;
	unsigned int	size;
	int				n_ant;
	struct s_path	*next;
}							t_path;



typedef	struct				s_flow
{
	t_path		*paths;
	size_t		n_paths;
	int			score;
}							t_flow;

struct						s_dvisu
{
	SDL_Window		*window;
	SDL_Surface		*s_surface;
	SDL_Texture		*tex;
	int				w_width;
	int				w_height;
	SDL_Renderer	*rend;
	int				f;
	int				path_n;
};

// typedef	struct				s_ants
// {
// 	size_t			end;
// 	t_path			*path;
// }							t_ants;


/*
***** function prototypes ******
*/

/*
********** visu *********
*/

int		visu_init(t_graph *g);
void	visu_quit();
int		graph_draw(t_graph *g);
int		edge_draw(t_graph *g, t_edge *edge, int type);
int		edges_draw(t_graph *g, t_node *node);
int		nodes_draw(t_graph *g, SDL_Rect dstr);


/*
** queue
*/
void	add_to_queue(t_queue **queue, t_edge *edge, int head);
void	print_queue(t_queue *queue);
void	delete_queue(t_queue **queue);

/*
** bfs
*/
t_flow *bfs(t_graph *g, int n_ants);

/*
************** tools **********
*/
int		map(int val, int *ranges);
int		*range_comp(int in_s, int in_e, int out_s, int out_e);

/*
** reset
*/


/* FIXME: re-write functions so that they are generalized */

t_graph *graph_init(t_node **refs, t_node **nodes, int nodes_c, int v);
void						read_line(int fd, char **line);
t_parse						*get_lines(int *nodes_c);
unsigned long				hash(unsigned char *str);

/* FIXME: review add_node */
int							add_node(t_node **lst_node, t_parse *lines,
										int nodes_c, int prop,
										t_node **refs);
t_node						**h_table(t_node **refs, t_parse *lines,
										int nodes_c);
int							edges_fill(t_node **lst_node, t_parse *lines,
										int nodes_c);
void						graph_free(t_graph *g);
void    					push_ants(t_flow *paths, size_t n_ants);
int							check_paths(t_flow *paths);
int							check_path(t_path *paths);
void						init_paths_with_ants(t_flow *paths);
void						error_exit(int error_code, void *content);
t_flow						*bfs_paths_collector(t_graph *g, int n_ants);
void						ant_count(t_flow *flow, int n_ants);


#endif
