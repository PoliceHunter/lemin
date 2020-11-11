/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:57:23 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 12:57:52 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error_if_vec(char *txt, t_vector *vec)
{
	ft_printf("%s", txt);
	free_vec_node(vec);
	exit(5);
}

void	ft_error_if_help_and_vec(char *txt, t_help *help, t_vector *vec)
{
	free(help->name);
	ft_error_if_vec(txt, vec);
}

int		find_comment(const char *line)
{
	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strcmp("##start", line) == 0)
			return (0);
		if (ft_strcmp("##end", line) == 0)
			return (0);
		return (1);
	}
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

int		it_is_link(const char *line)
{
	int index;

	index = -1;
	while (line[++index] != '\0')
	{
		if (line[index] == '-')
			return (1);
		else if (line[index] == ' ')
			return (0);
	}
	return (0);
}
