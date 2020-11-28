/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:28 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:23:30 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node_ptr		write_history_help(t_vector ways, char **history, int way_i)
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
			*history = ft_strjoin_free(*history, ft_strjoin_free(
				ft_strjoin_free(ft_strjoin_free(ft_strjoin_free2(
					"L", ft_itoa(*(int *)get_from_vec(
					&node->ants, 0))), "-"), node->name), " "));
	}
	return (dst);
}

void			write_history(t_vector ways, char **history)
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
		*history = ft_strjoin_free(*history, ft_strjoin_free(ft_strjoin_free(
				ft_strjoin_free(ft_strjoin_free2("L", ft_itoa(*ant))
					, "-"), dst->name), " "));
		free(ant);
	}
	*history = ft_strjoin_free(*history, "\n");
}

int				process_way(t_way *way, t_ants_tracker *tracker,
				int *previous_ways_len, const int index)
{
	t_node_ptr	curr;
	int			ant;
	int			step;

	ant = 1 + tracker->all - tracker->ready_to_go;
	curr = *(t_node_ptr *)get_from_vec(&way->nodes, 1);
	step = make_way_step(way);
	if (step > index)
		tracker->finished++;
	if (tracker->ready_to_go > (way->nodes.size * index - *previous_ways_len))
	{
		push_back_vec(&curr->ants, &ant);
		tracker->ready_to_go--;
	}
	if (curr->is_end_node == 1)
		tracker->finished++;
	if (tracker->ready_to_go <= 0)
		return (TRUE);
	*previous_ways_len += way->nodes.size;
	return (FALSE);
}

unsigned int	get_rest_ant_step(t_ants_tracker tracker,
						t_vector *ways, char **history)
{
	unsigned int	steps_count;
	int				way_index;
	int				finish_hp;

	finish_hp = 0;
	steps_count = 0;
	while (tracker.finished != tracker.all)
	{
		way_index = 0;
		while (way_index != ways->size)
		{
			finish_hp = make_way_step(get_from_vec(ways, way_index));
			way_index++;
		}
		tracker.finished += finish_hp;
		steps_count++;
		write_history(*ways, history);
	}
	return (steps_count);
}

size_t			get_ant_step(t_node_ptr src, int ants_count,
				t_vector ways, char **way_history)
{
	int				previous_ways_len;
	t_ants_tracker	tracker;
	size_t			steps_count;
	int				index;

	tracker = init_tracker(ants_count);
	remove_from_vec(&src->ants, 0);
	steps_count = 0;
	while (tracker.ready_to_go != 0)
	{
		index = -1;
		previous_ways_len = 0;
		while (++index != ways.size)
		{
			if (process_way(get_from_vec(&ways, index), &tracker,
					&previous_ways_len, index) && ways.size == index + 1)
				break ;
		}
		write_history(ways, way_history);
		++steps_count;
	}
	if (tracker.ready_to_go == 0)
		steps_count += get_rest_ant_step(tracker, &ways, way_history);
	return (steps_count);
}
