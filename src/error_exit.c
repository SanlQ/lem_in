/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:35:11 by melalj            #+#    #+#             */
/*   Updated: 2020/02/11 00:21:52 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	error_exit(int error_code, void *content)
{
	(void)content;
	if (error_code == 1)
		ft_printf("number of ants is not valid\n");
	else if (error_code == 2)
		ft_printf("error in parsing the input\n");
	else if (error_code == 3)
		ft_printf("error in malloc\n");
	else if (error_code == 4)
		ft_printf("error in filling the edges\n");
	else if (error_code == 5)
	{
		ft_printf("error no start or end\n");
		graph_free((t_graph *)content);
	}
	exit(1);
}
