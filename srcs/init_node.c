/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:28:16 by ksean             #+#    #+#             */
/*   Updated: 2020/11/09 15:06:06 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	init_node(char *name)
{
	t_node node;

	node.name = ft_strdup(name);
	node.x = 0;
	node.y = 0;
	node.links = new_vector(5, sizeof(t_edge));
	node.is_end_node = 0;
	node.is_start_node = 0;
	node.bfs = 0;
	node.traversal_state = STATE_NO_INVOLVED;
	node.is_cross = FALSE;
	node.ants = new_vector(5, sizeof(int));
	return (node);
}

t_node	init_and_write_node(t_help *help)
{
	t_node node;

	node.name = ft_strdup(help->name);
	node.x = help->x;
	node.y = help->y;
	node.links = new_vector(5, sizeof(t_edge));
	node.ants = new_vector(5, sizeof(int));
	node.is_end_node = help->end;
	node.is_start_node = help->start;
	if (help->start == 1)
		push_back_vec(&node.ants, &help->ants);
	node.bfs = 0;
	node.traversal_state = STATE_NO_INVOLVED;
	node.is_cross = FALSE;
	return (node);
}

t_help	init_help(void)
{
	t_help help;

	help.ants = 0;
	help.errors = 0;
	help.name = NULL;
	help.x = 0;
	help.y = 0;
	help.end = 0;
	help.start = 0;
	help.multi_st_end = 0;
	return (help);
}
