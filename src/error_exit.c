/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:35:11 by melalj            #+#    #+#             */
/*   Updated: 2020/02/22 12:03:30 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	error_exit(int error_code, void *content)
{
	(void)content;
	if (error_code == 1)
		ft_printf("number of ants is not valid\n");
	else if (error_code == 2)
		ft_printf("ERROR : in parsing the input\n");
	else if (error_code == 3)
		ft_printf("ERROR : in malloc\n");
	else if (error_code == 4)
		ft_printf("ERROR : in filling the edges\n");
	else if (error_code == 5)
		ft_printf("ERROR : no start or end\n");
	else if (error_code == 6)
		ft_printf("ERROR : no rooms\n");
	else if (error_code == 7)
		ft_printf("ERROR : can't find the end\n");
	else if (error_code == 8)
		ft_printf("ERROR in reading the input\n");
	exit(1);
}
