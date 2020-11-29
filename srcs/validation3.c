/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 00:04:40 by ksean             #+#    #+#             */
/*   Updated: 2020/11/07 00:04:57 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_duplicate_links(t_node_ptr src, t_node_ptr dst)
{
	t_edge		*tmp;
	int			index;

	index = 0;
	tmp = NULL;
	while (index != (*src).links.size)
	{
		if (!(tmp = get_from_vec(&(src)->links, index)))
			break ;
		if (tmp->dst->name == dst->name)
			return (1);
		index++;
	}
	return (0);
}

t_edge	new_edge(t_node_ptr *dst, const size_t capacity)
{
	t_edge result;

	result.dst = *dst;
	result.capacity = capacity;
	result.original_capacity = capacity;
	result.backward = NULL;
	result.mark = MARK_NONE;
	return (result);
}

int		write_link(const char *line, t_vector *node_vec)
{
	t_node_ptr	src_node;
	t_node_ptr	dst_node;
	t_edge		tmp;
	char		**link;

	link = ft_strsplit(line, '-');
	src_node = find_and_get(node_vec, link[0]);
	dst_node = find_and_get(node_vec, link[1]);
	free_array(link);
	if (src_node == NULL || dst_node == NULL)
		return (1);
	if (check_duplicate_links(src_node, dst_node))
		return (1);
	tmp = new_edge(&dst_node, 1);
	push_back_vec(&src_node->links, &tmp);
	tmp = new_edge(&src_node, 1);
	push_back_vec(&dst_node->links, &tmp);
	return (0);
}
