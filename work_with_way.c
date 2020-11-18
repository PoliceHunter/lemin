/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_way.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:20 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:23:22 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//t_way				new_way(char *raw_way, const char separator)
//{
//	t_way result;
//
//	result.way_nodes = ft_strsplit_with_len(raw_way, separator,
//								&result.way_len);
//	result.ants = malloc(sizeof(unsigned short) * result.way_len);
//	ft_memset(result.ants, 0, sizeof(unsigned short) * result.way_len);
//	free(raw_way);
//	return (result);
//}
//
//void				shift_array_right(void *array, unsigned int size,
//						unsigned int element_size)
//{
//	ft_memmove(array + element_size, array, (size - 1) * element_size);
//	ft_memset(array, 0, element_size);
//}
//
//int					make_way_step(t_way *way)
//{
//	int result;
//
//	result = 0;
//	if (way->ants[way->way_len - 1] != 0)
//		result = 1;
//	shift_array_right(way->ants, way->way_len, sizeof(unsigned short));
//	return (result);
//}
//
//static size_t			count_words(char *s, char c)
//{
//	size_t index;
//	size_t words;
//
//	index = 0;
//	words = 0;
//	while (s[index] != '\0')
//	{
//		while (s[index] == c)
//			index++;
//		while (s[index] != c && s[index] != '\0')
//		{
//			words++;
//			while (s[index] != c && s[index] != '\0')
//				index++;
//		}
//	}
//	return (words);
//}
//
//void				find_ways(t_node_ptr src, t_node_ptr dst, char *tmp_buffer,
//					t_vector *ways)
//{
//	t_way		way;
//	t_node_ptr	*candidate;
//	int			i;
//	int			tmp;
//
//	i = -1;
//
//	tmp_buffer = ft_strjoin_free(ft_strjoin_free(tmp_buffer, src->name), " ");
//	while (++i != (src)->links.size)
//	{
//		candidate = get_from_vec(&(src)->links, i);
//		if (!src->is_start_node && (*candidate)->bfs < src->bfs && (*candidate)->r_bfs > src->r_bfs)
//			continue;
//		if (ft_strcmp((*candidate)->name, dst->name) != 0)
//		{
//			find_ways(*candidate, dst, ft_strdup(tmp_buffer), ways);
//			continue ;
//		}
//		way = new_way(ft_strjoin_free(tmp_buffer, dst->name), ' ');
//		tmp = ways->size;
//		insert_with_sort(ways, &way, &cmp_way);
//		if (tmp == ways->size)
//			free_ways(&way);
//		return ;
//	}
//
//	free(tmp_buffer);
//}
//