/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:42:06 by ksean             #+#    #+#             */
/*   Updated: 2020/11/19 00:09:22 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		this_start(char *line, t_help *help)
{
	if (ft_strcmp("##start", line) == 0)
	{
		if (help->multi_st_end == 2)
		{
			help->errors++;
			return (0);
		}
		help->start = 1;
		help->multi_st_end++;
		return (1);
	}
	return (0);
}

int		this_end(char *line, t_help *help)
{
	if (ft_strcmp("##end", line) == 0)
	{
		if (help->multi_st_end == 2)
		{
			help->errors++;
			return (0);
		}
		help->end = 1;
		help->multi_st_end++;
		return (1);
	}
	return (0);
}

int		empty_string(const char *line, t_help *help)
{
	if (line == NULL)
	{
		help->errors++;
		return (1);
	}
	if (line[0] == '\0' || line[0] == 'L')
	{
		help->errors++;
		return (1);
	}
	return (0);
}

int		ft_is_digitstr(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
			continue;
		}
		return (0);
	}
	return (1);
}
