/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 03:25:33 by melalj            #+#    #+#             */
/*   Updated: 2020/02/22 13:43:38 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		flow_free(t_flow *flow)
{
	t_path	*curr_path;
	t_path	*curr_temp;

	if (flow)
	{
		curr_path = flow->paths;
		while (curr_path)
		{
			curr_temp = curr_path;
			delete_queue(&(curr_path->edge));
			curr_path = curr_path->next;
			free(curr_temp);
		}
		free(flow);
	}
	return (1);
}
