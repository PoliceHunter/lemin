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

int		write_link(const char *line, t_vector *node_vec)
{
	t_node_ptr	src_node;
	t_node_ptr	dst_node;
	char		**link;
	char		*src;
	char		*dst;

	link = ft_strsplit(line, '-');
	src = link[0];
	dst = link[1];
	src_node = find_and_get(node_vec, src);
	dst_node = find_and_get(node_vec, dst);
	free_array(link);
	if (src_node == NULL || dst_node == NULL)
		return (1);
	if (check_duplicate_links(src_node, dst_node))
		return (1);
	push_back_vec(&src_node->links, &dst_node);
	push_back_vec(&dst_node->links, &src_node);
	return (0);
}
