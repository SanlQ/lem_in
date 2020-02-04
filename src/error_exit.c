/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:35:11 by melalj            #+#    #+#             */
/*   Updated: 2020/02/04 22:49:14 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	error_exit(int error_code, void *content)
{
	(void)content;
	if (error_code == 1)
		ft_printf("number of ants is not valid\n");
	if (error_code == 2)
		ft_printf("error in parsing the input\n");
	exit(1);
}
