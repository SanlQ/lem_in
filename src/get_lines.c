/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melalj <melalj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 22:08:00 by melalj            #+#    #+#             */
/*   Updated: 2020/02/22 13:47:38 by melalj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int				check_node_comment(char *line)
{
	if (line && line[0] == '#' && line[1] != '#')
		return (-1);
	else if (line && line[0] == '#' && line[1] == '#')
	{
		if (ft_strequ(line + 2, "start"))
			return (NODE_START);
		else if (ft_strequ(line + 2, "end"))
			return (NODE_END);
		else
			return (-1);
	}
	return (0);
}

int				check_node(char *line)
{
	char	**sline;
	int		i;

	if ((i = check_node_comment(line)))
		return (i);
	if (!(sline = ft_strsplit(line, ' ')))
		error_exit(3, NULL);
	i = -1;
	while (sline[++i])
	{
		if (!i && sline[0][0] == 'L')
			break ;
		if (i && !ft_isnumber(sline[i]))
			break ;
	}
	free_tab(sline);
	if (i != 3)
		return (0);
	return (1);
}

int				check_edge(char *line)
{
	char	**sline;
	int		i;

	if (line && line[0] == '#')
		return (-1);
	if (!(sline = ft_strsplit(line, '-')))
		error_exit(3, NULL);
	i = -1;
	while (sline[++i])
		if (i == 1 && ft_strequ(sline[1], sline[0]))
			break ;
	free_tab(sline);
	if (i != 2)
		return (0);
	return (1);
}

static t_parse	*add_pline(char *line, int type, int prop)
{
	t_parse	*p_lines;

	if (!(p_lines = (t_parse*)malloc(sizeof(t_parse))))
		error_exit(3, NULL);
	p_lines->line = ft_strdup(line);
	p_lines->prop = prop;
	p_lines->type = type;
	p_lines->next = NULL;
	return (p_lines);
}

int				parse_line(t_parse **p_lines, int *type, int *prop)
{
	char *line;

	read_line(0, &line);
	if (line && ft_strequ(line, "") && (*type)++)
		*prop = -1;
	else if (line && !(*type) && ft_isnumber(line))
	{
		if (ft_atoi(line) <= 0)
			error_exit(1, p_lines);
		*p_lines = add_pline(line, *type, *prop);
		(*type)++;
	}
	else if (line && (*type) == 1 && ((*prop) = check_node(line)))
	{
		*p_lines = add_pline(line, *type, *prop);
	}
	else if (line && check_edge(line))
	{
		(*type) = ((*type) == 1) ? (*type) + 1 : (*type);
		*p_lines = add_pline(line, *type, *prop);
	}
	else
		error_exit(2, *p_lines);
	free(line);
	return ((*type == 1 && *prop == 1) ? 1 : 0);
}

t_parse			*get_lines(int *nodes_c)
{
	t_parse	*p_lines;
	t_parse	*current;
	int		type;
	int		prop;

	p_lines = NULL;
	type = 0;
	current = NULL;
	while (!type && parser_free(current))
		parse_line(&(current), &type, &prop);
	p_lines = current;
	while (p_lines && type >= 0)
	{
		*nodes_c += parse_line(&(current->next), &type, &prop);
		if (!current->next && prop != 0)
			break ;
		if (!current->next && prop == 0)
		{
			current = current->next;
			continue;
		}
		current = current->next;
	}
	return (p_lines);
}

/*
**	if (!ft_isascii(tmp[0]) || tmp[0] == 0) // the condition that fix /dev/zero
**		exit(0);
*/

void			read_line(int fd, char **line)
{
	char	*dump;
	int		ret;
	char	tmp[2];

	if (!(*line = ft_strdup("")))
		error_exit(3, NULL);
	while ((ret = read(fd, tmp, 1)))
	{
		if (ret == -1)
			error_exit(8, NULL);
		if (tmp[0] == '\n')
			break ;
		tmp[1] = 0;
		if (!(dump = ft_strjoin(*line, tmp)))
			error_exit(3, NULL);
		free(*line);
		*line = dump;
	}
}
