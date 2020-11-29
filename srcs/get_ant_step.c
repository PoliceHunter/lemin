/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ant_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:32:52 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:32:53 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int	get_rest_ant_step(t_track tracker,
							t_vector *ways, char **history)
{
	unsigned int	steps_count;
	int				way_index;
	int				finish_hp;
	int				ants_in_way;

	finish_hp = 0;
	steps_count = 0;
	while (tracker.finished != tracker.all)
	{
		way_index = 0;
		ants_in_way = 0;
		while (way_index != ways->size)
		{
			finish_hp = make_way_step(get_from_vec(ways, way_index),
						&ants_in_way);
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
	t_track			tracker;
	size_t			steps_count;
	int				index;

	tracker = init_tracker(ants_count);
	remove_from_vec(&src->ants, 0);
	steps_count = 0;
	while (tracker.ready_to_go != 0)
	{
		index = -1;
		previous_ways_len = 0;
		tracker.ants_in_way = 0;
		while (++index != ways.size)
			process_way(get_from_vec(&ways, index), &tracker,
				&previous_ways_len, index);
		tracker.finished += (*(t_node_ptr*)get_last(&((t_way*)
				get_last(&ways))->nodes))->ants.size;
		write_history(ways, way_history);
		++steps_count;
	}
	if (tracker.ready_to_go == 0)
		steps_count += get_rest_ant_step(tracker, &ways, way_history);
	return (steps_count);
}

char			*ft_strjoin_free3(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	if (s1 != NULL)
		free(s1);
	return (str);
}
