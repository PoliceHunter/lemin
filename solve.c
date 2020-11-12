/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:24:33 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 13:00:35 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void				set_bfs(t_node_ptr node) //// 29/25 lines
{
	t_node_ptr	cur;
	t_node_ptr	*kid;
	int			i;

	cur = node;
	cur->visited = 1;
	i = -1;
	while (++i < (cur)->links.size)
	{
		kid = get_from_vec(&(cur)->links, i);
		if ((*kid)->bfs == 0 && !(*kid)->is_start_node && (*kid)->visited == -1)
			(*kid)->visited = 0;
	}
	i = -1;
	while (++i < (cur)->links.size)
	{
		kid = get_from_vec(&(cur)->links, i);
		if ((((*kid)->bfs) > cur->bfs + 1) && (*kid)->is_end_node != 1)
			(*kid)->bfs = cur->bfs + 1;
		if ((*kid)->bfs == 0 && !(*kid)->is_start_node && (*kid)->visited == 0)
			(*kid)->bfs = cur->bfs + 1;
	}
	i = -1;
	while (++i < (cur)->links.size)
	{
		kid = get_from_vec(&(cur)->links, i);
		if ((*kid)->visited != 1 && (*kid)->is_end_node != 1)
			set_bfs(*kid);
	}
}

char				*ft_strjoin_free3(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	if (s1 != NULL)
		free(s1);
	return (str);
}

char				*get_ant_pos(const t_vector *ways)
{
	char			*result;
	char			*node;
	int				way_i;
	unsigned int	i;
	const t_way		*way;

	way_i = -1;
	result = NULL;
	while (++way_i != ways->size)
	{
		i = 0;
		way = get_from_vec_const(ways, way_i);
		while (++i < way->way_len)
		{
			if (way->ants[i] != 0)
			{
				node = (!result) ? ft_strjoin_free2("L", ft_itoa(way->
				ants[i])) : ft_strjoin_free2(" L", ft_itoa(way->ants[i]));
				node = ft_strjoin_free(node, "-");
				node = ft_strjoin_free(node, way->way_nodes[i]);
				result = ft_strjoin_free3(result, node);
			}
		}
	}
	return (result);
}

void				printf_ways(t_vector ways)
{
	unsigned int	i;
	int				index;
	t_way			*way;

	i = 0;
	index = 0;
	while (index != ways.size)
	{
		way = get_from_vec(&ways, index);
		while (i != way->way_len)
		{
			printf("%s->", way->way_nodes[i]);
			++i;
		}
		printf("\n");
		++index;
	}
}

char				*solve(t_node_ptr src, t_node_ptr dst)
{
	t_vector	ways;
	char		*result;

	src->bfs = 0;
	dst->bfs = INT_MAX;
	result = NULL;
	set_bfs(src);
	ways = new_vector(10, sizeof(t_way));
	find_ways(src, dst, NULL, &ways);
	result = write_ants_in_line(&ways, src->n_ants);
	if (ways.size == 0)
	{
		ft_printf("Error\nNo ways!\n");
		free(result);
		free_vec_ways(ways);
		return (NULL);
	}
	free_vec_ways(ways);
	return (result);
}
