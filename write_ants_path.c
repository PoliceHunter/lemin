/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ants_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:30:22 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/12 13:30:24 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_degenerate(t_group_handler *handler)
{
	if (is_group_identical(handler->candidate_group, handler->min_group))
	{
		free_vec(&handler->candidate_group);
		return (1);
	}
	return (0);
}

void		win_candidate(t_group_handler *handler)
{
	free_vec(&handler->min_group);
	handler->min_group = handler->candidate_group;
}

void		lose_candidate(t_group_handler *handler)
{
	free_vec(&handler->candidate_group);
}

void		decide_candidate(t_group_handler *handler,
			unsigned int candidate_step, char *way_history)
{
	if (candidate_step < handler->min_group_step)
	{
		handler->min_group_step = candidate_step;
		win_candidate(handler);
		if (handler->result != NULL)
			free(handler->result);
		handler->result = way_history;
	}
	else
	{
		lose_candidate(handler);
		free(way_history);
	}
}

char		*write_ants_in_line(t_vector *ways, int ants)
{
	t_group_handler	group_helper;
	char			*way_history;
	int				index;

	index = -1;
	way_history = NULL;
	group_helper = init_group_handler();
	while (++index != ways->size)
	{
		group_helper.candidate_group =
				get_non_crossing_group(ways, get_from_vec(ways, index));
		if (is_degenerate(&group_helper))
			continue;
		decide_candidate(&group_helper,
			get_ant_step(group_helper.candidate_group,
				ants, &way_history, group_helper.min_group_step), way_history);
	}
	free_vec(&group_helper.min_group);
	return (group_helper.result);
}
