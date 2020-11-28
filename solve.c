/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:24:33 by ksean             #+#    #+#             */
/*   Updated: 2020/11/15 12:37:04 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <string.h>
#include <stdlib.h>

int		make_way_step(t_way *way)
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
			continue ;
		ant = pop_front_vec(&prev->ants);
		emplace_back_vec(&curr->ants, ant);
		free(ant);
	}
	curr = *(t_node_ptr *)get_last(&way->nodes);
	return (curr->ants.size);
}

int		process_candidate(t_solver_helper *helper, t_node_ptr src,
							int ants_count, t_vector ways)
{
	helper->current_ant_step = get_ant_step(src, ants_count, ways,
				helper->is_history_need ? &helper->current_history : NULL);
	return (helper->current_ant_step);
}

int		try_candidate(t_solver_helper *helper, t_node_ptr src,
							int ants_count, t_vector ways)
{
	src->bfs = 0;
	if (process_candidate(helper, src, ants_count, ways) <
	(int)helper->best_ant_step)
		candidate_win(helper);
	else
	{
		ft_strclr(helper->current_history);
		return (FALSE);
	}
	return (TRUE);
}

void is_cross(t_vector ways);

int	solve(t_node_ptr src, int ants_count, t_vector * nodes, char ** history)
{
	t_vector		ways;
	int				is_need_recalculate;
	t_solver_helper	helper;
	int				is_attendance;

	helper = init_helper();
	is_need_recalculate = TRUE;
	while (reset_all_states(nodes))
	{
		ways = new_vector(10, sizeof(t_way));
		while ((is_attendance = find_by_bfs(src, get_place_for_way(&ways), nodes)) == TRUE)
		{
			if (get_last_way(&ways)->state == IS_CROSS)
				break ;
			is_cross(ways);
			is_need_recalculate = try_candidate(&helper, src, ants_count, ways);
		}
		if (ways.size == 0)
			return (0); // NULL
		if (is_need_recalculate == FALSE && is_attendance == FALSE)
		{
			ways.size -= 1;
			free_ways(&ways);
			return (helper.best_ant_step);
		}
		if (is_need_recalculate == FALSE || is_attendance == FALSE)
		{
			ways.size -= 1;
			helper.is_history_need = TRUE;
			process_candidate(&helper, src, ants_count, ways);
			*history = helper.best_history;
			free_ways(&ways);
		}
		if (is_need_recalculate == FALSE)
			return (helper.best_ant_step);
		is_need_recalculate = FALSE;
		reset_all_edges(nodes);
		free_ways(&ways); //// change and fix free_ways
	}
	return (0); // NULL
}
