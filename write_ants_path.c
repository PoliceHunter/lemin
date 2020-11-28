/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:28 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:51:33 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			make_way_step(t_way *way, int *ants_in_way)
{
	t_node_ptr	prev;
	t_node_ptr	curr;
	int			i;
	int			*ant;

	i = way->nodes.size;
	while (--i > 0)
	{
		curr = *(t_node_ptr *)get_from_vec(&way->nodes, i);
		prev = *(t_node_ptr *)get_from_vec(&way->nodes, i - 1);
		if (prev->ants.size == 0)
			continue;
		ant = pop_front_vec(&prev->ants);
		emplace_back_vec(&curr->ants, ant);
		free(ant);
		if (curr->is_end_node == FALSE)
			*ants_in_way += curr->ants.size;
	}
	curr = *(t_node_ptr *)get_last(&way->nodes);
	return (curr->ants.size);
}

t_node_ptr	write_history_help(t_vector ways, char **history, int way_i)
{
	t_way		*way;
	int			i;
	t_node_ptr	dst;
	t_node_ptr	node;

	way = get_from_vec(&ways, way_i);
	i = 0;
	while (++i < way->nodes.size)
	{
		node = *(t_node_ptr *)get_from_vec(&way->nodes, i);
		if (node->is_end_node)
		{
			dst = node;
			continue ;
		}
		if (node->ants.size != 0)
			*history = ft_strjoin_free3(*history, ft_strjoin_free(
					ft_strjoin_free(ft_strjoin_free(ft_strjoin_free2(
							"L", ft_itoa(*(int *)get_from_vec(&node->ants, 0))),
													"-"), node->name), " "));
	}
	return (dst);
}

void		write_history(t_vector ways, char **history)
{
	int			way_i;
	t_way		*way;
	t_node_ptr	dst;
	int			*ant;

	dst = NULL;
	if (history == NULL)
	{
		way = get_last(&ways);
		dst = *(t_node_ptr *)get_last(&way->nodes);
		dst->ants.size = 0;
		return ;
	}
	way_i = -1;
	while (++way_i < ways.size)
		dst = write_history_help(ways, history, way_i);
	while (dst->ants.size != 0)
	{
		ant = pop_back_vec(&dst->ants);
		*history = ft_strjoin_free3(*history, ft_strjoin_free(ft_strjoin_free(
				ft_strjoin_free(ft_strjoin_free2("L", ft_itoa(*ant))
						, "-"), dst->name), " "));
		free(ant);
	}
	*history = ft_strjoin_free(*history, "\n");
}

int			process_way(t_way *way, t_track *tracker,
				int *previous_ways_len, const int index)
{
	t_node_ptr	curr;
	int			ant;

	ant = 1 + tracker->all - tracker->ready_to_go;
	curr = *(t_node_ptr *)get_from_vec(&way->nodes, 1);
	make_way_step(way, &tracker->ants_in_way);
	if (tracker->ready_to_go > (way->nodes.size * index - *previous_ways_len))
	{
		push_back_vec(&curr->ants, &ant);
		--tracker->ready_to_go;
		tracker->ants_in_way++;
	}
	if (tracker->ready_to_go <= 0)
		return (TRUE);
	*previous_ways_len += way->nodes.size;
	return (FALSE);
}
