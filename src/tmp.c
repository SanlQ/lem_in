/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 07:57:36 by magoumi           #+#    #+#             */
/*   Updated: 2020/01/30 09:13:26 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int     count_tours(t_flow *paths, size_t n_ants)
{
	int     ants;
	size_t  i;
	int     *n_paths;
	t_path  *p;
	if (!(n_paths = malloc(paths->n_paths + 1)))
		return (0);
	i = 0;
	ants = n_ants;
	p = paths->paths;
	while (i < paths->n_paths)
	{
		ft_printf("[path %d size:[%d]\n", i , p->size);
		n_paths[i] = p->size;
		p = p->next;
		i++;
	}
	return (1);
}

int		get_paths_size(t_path *p, int n)
{
	int i;
	int	size;

	i = 0;
	size = 0;
	while(p->next && i < n)
	{
		size += p->size;
		p = p->next;
		i++;
	}
	return (size);
}

int		count_paths(t_flow *paths, size_t n_ants)
{
	int		tmp;
	int		n;
	int		i;
	int		size;
	t_path  *p;

	p = paths->paths;
	i = 1;
	tmp = 0;
	while(p->next)
	{
		size = get_paths_size(p, i);
		n = ((n_ants + size) / i) - 2;
		if (n > tmp)
			return (i);
		tmp = n;
		i++;
	}
	return (n);
}
t_ants	*ft_create_ants(size_t n_ants)
{
	size_t	i;
	t_ants	*head;
	t_ants	*tmp;
	t_ants	*p;

	i = 0;
	head = NULL;
	while (i < n_ants)
	{
		if (!(tmp = (t_ants*)malloc(sizeof(t_ants))))
			return (NULL);
		tmp->ant = i;
		tmp->end = 0;
		tmp->position = 0;
		tmp->path = NULL;
		tmp->next = NULL;
		if (head == NULL)
			head = tmp;
		else
		{
			p = head;
			while (p->next)
				p = p->next;
			p->next = tmp; 
		}
		i++;
	}
	return (head);
}

void	ant_to_path(t_ants *ant, t_flow *paths, size_t j)
{
	size_t	i;
	t_path	*p;
	
	ft_printf("[starting pushing ant %zu]\n", ant->ant);
	p = paths->paths;
	if (ant->end)
		return ;
	ft_printf("L%d ", ant->ant);
	i = 0;
	while (i < j)
		p = p->next;
	if (ant->position == 0)
		ft_printf("S-");
	else
		ft_printf("%d-", ant->position);
	ant->position++;
	if (p->size == ant->position){
	 	ant->end = 1;
	 	ft_printf("E");
	}
	else
		ft_printf("%d", ant->position);
	//ft_printf("[ant %zu passed successfully]\n", ant->ant);
}
*/
/*
	if (check_path(paths->paths))
		ft_printf("path is empty\n");
	else
		ft_printf("path is not empty\n");
	printf("[%s]\n", paths->paths->edge->edge->node_src->name);
*/

/*
	t_ants	*ants;
	t_ants	*tmp;
	size_t	tours;
	size_t	i;
	size_t	j;
	ants = NULL;
	while (tmp)
	ants = ft_create_ants(n_ants);
	if (!paths->n_paths)
		return ;
	tours = (n_ants / (paths->n_paths)) + (n_ants % (paths->n_paths));
	i = 0;
	tmp = ants;
	if (!ants)
		return ;
	while (i < tours)
	{
		j = 0;
		ants = tmp;
		while (j < paths->n_paths)
		{
			if (j)
				ft_printf(" ");
			ant_to_path(ants, paths, j);
			ants = ants->next;
			j++;
		}
		ft_printf("\n");
		i++;
	}
	{
		ft_printf("ant number is [%d]\n", tmp->ant);
		tmp = tmp->next;
	}
*/

/*
// if (curr->next->edge->node_src->seen)
		// {
		// 	ft_printf("L%d-", curr->next->edge->node_src->seen);
		// 	if (curr->edge->node_dst->seen)
		// 	{
		// 		curr->edge->node_dst->seen = curr->next->edge->node_src->seen;
		// 		ft_printf("%s", curr->next->edge->node_dst->name);
		// 	}
		// 	ft_printf(" ");
		// }
		// curr = curr->next;
*/
