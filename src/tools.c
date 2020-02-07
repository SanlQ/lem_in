/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 19:31:44 by melalj            #+#    #+#             */
/*   Updated: 2020/02/07 17:06:31 by magoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	map(int val, int *ranges)
{
	int d;
	int result;

	d = (ranges[1] - ranges[0]) + ranges[2];
	d = (!d) ? 1 : d;
	result = (val - ranges[0]) * (ranges[3] - ranges[2]) / d;
	return (result);
}

int	*range_comp(int in_s, int in_e, int out_s, int out_e)
{
	int *comp_range;

	if (!(comp_range = (int *)malloc(sizeof(int) * 4)))
		return (NULL);
	comp_range[0] = in_s;
	comp_range[1] = in_e;
	comp_range[2] = out_s;
	comp_range[3] = out_e;
	return (comp_range);
}
