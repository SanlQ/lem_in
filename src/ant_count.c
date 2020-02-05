/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:23:07 by melalj            #+#    #+#             */
/*   Updated: 2020/02/04 23:44:28 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ant_count(t_flow *flow, int n_ants)
{
	t_path	*curr_path;
	int		i;

	i = 0;
	while (n_ants)
	{
		curr_path = flow->paths;
		while (curr_path)
		{
			if (curr_path->size <= flow->paths->size + i)
			{
				curr_path->n_ant++;
				n_ants--;
				if (!n_ants)
					break ;
			}
			curr_path = curr_path->next;
		}
		i++;
	}
}
