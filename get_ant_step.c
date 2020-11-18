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
//
//t_ants_tracker		new_tracker(const unsigned int ants_count)
//{
//	t_ants_tracker result;
//
//	result.finished = 0;
//	result.in_path = ants_count;
//	result.count = ants_count;
//	return (result);
//}
//
//void				write_history(t_vector way_vector, char **history)
//{
//	char *ants_way;
//
//	ants_way = get_ant_pos(&way_vector);
//	if (ants_way == NULL)
//		return ;
//	*history = ft_strjoin_free3(*history, ft_strjoin("\n", ants_way));
//	free(ants_way);
//}
//
//unsigned int		get_rest_ant_step(t_ants_tracker tracker,
//		const unsigned int steps_limit, t_vector *ways, char **history)
//{
//	unsigned int	steps_count;
//	int				index;
//
//	steps_count = 0;
//	while (tracker.finished != tracker.count)
//	{
//		index = 0;
//		while (index != ways->size)
//		{
//			tracker.finished += make_way_step(get_from_vec(ways, index));
//			index++;
//		}
//		write_history(*ways, history);
//		if (++steps_count > steps_limit)
//			return (INT_MAX);
//	}
//	return (steps_count);
//}
//
//int					process_way(t_way *way, t_ants_tracker *tracker,
//						unsigned int *previous_ways_len, const int index)
//{
//	tracker->finished += make_way_step(way);
//	if (tracker->in_path > (way->way_len * index - *previous_ways_len))
//	{
//		way->ants[0] = 1 + (tracker->count - tracker->in_path);
//		--tracker->in_path;
//	}
//	if (tracker->in_path <= 0)
//		return (1);
//	*previous_ways_len += way->way_len;
//	return (0);
//}
//
//unsigned int		get_ant_step(t_vector ways, const unsigned int ants_count,
//						char **history, unsigned int min_step_count)
//{
//	unsigned int	steps_count;
//	int				index;
//	unsigned int	previous_ways_len;
//	t_ants_tracker	tracker;
//
//	steps_count = 0;
//	tracker = new_tracker(ants_count);
//	while (tracker.in_path != 0)
//	{
//		previous_ways_len = 0;
//		index = 0;
//		while (index != ways.size && tracker.in_path > 0)
//		{
//			if (process_way(get_from_vec(&ways, index),
//							&tracker, &previous_ways_len, index))
//				break ;
//			++index;
//		}
//		write_history(ways, history);
//		++steps_count;
//		if (steps_count > min_step_count)
//			return (INT_MAX);
//	}
//	return (steps_count + get_rest_ant_step(tracker,
//							min_step_count - steps_count, &ways, history));
//}
//