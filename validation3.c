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
	t_node_ptr	*tmp;
	int			index;

	index = 0;
	tmp = NULL;
	while (index != (*src).links.size)
	{
		if (!(tmp = get_from_vec(&(src)->links, index)))
			break ;
		if ((*tmp)->name == (*dst).name)
			return (1);
		index++;
	}
	return (0);
}

t_edge *write_edge(t_node_ptr *cur)
{
	t_edge *result;

	result = malloc(sizeof(t_edge));
	result->dst = *cur;
	result->capacity = 0;

	return result;
}

int		write_link(const char *line, t_vector *node_vec)
{
	t_node_ptr	src_node;
	t_node_ptr	dst_node;
	char		**link;

	link = ft_strsplit(line, '-');

	src_node = find_and_get(node_vec, link[0]);
	dst_node = find_and_get(node_vec, link[1]);
	free_array(link);
	if (src_node == NULL || dst_node == NULL)
		return (1);
	if (check_duplicate_links(src_node, dst_node))
		return (1);

	push_back_vec(&src_node->links, write_edge(&dst_node));
	push_back_vec(&dst_node->links, write_edge(&src_node));

	return (0);
}
