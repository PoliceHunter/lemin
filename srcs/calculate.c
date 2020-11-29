/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:54:54 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:54:55 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			process_candidate(t_solver_helper *helper, t_node_ptr src,
			int ants_count, t_vector ways)
{
	helper->current_ant_step = get_ant_step(src, ants_count, ways,
			helper->is_history_need ? &helper->current_history : NULL);
	return (helper->current_ant_step);
}

void		candidate_win(t_solver_helper *helper)
{
	if (helper->best_history != NULL)
		free(helper->best_history);
	helper->best_ant_step = helper->current_ant_step;
	helper->best_history = helper->current_history;
	helper->current_history = NULL;
	helper->is_history_need = FALSE;
	helper->current_ant_step = 0;
}

t_vector	try_candidate(t_solver_helper *helper, t_node_ptr src,
					int ants_count, t_vector ways)
{
	if (ways.size == 0)
		return (ways);
	if (process_candidate(helper, src, ants_count,
						ways) < (int)helper->best_ant_step)
	{
		free_ways(&helper->best_ways);
		helper->best_ways = ways;
		candidate_win(helper);
		return (new_vector(10, sizeof(t_way)));
	}
	else
	{
		ft_strclr(helper->current_history);
		return (ways);
	}
}

char		*calculate_best_history(t_solver_helper *helper,
						t_node_ptr src, int ants_count)
{
	helper->is_history_need = TRUE;
	process_candidate(helper, src, ants_count, helper->best_ways);
	helper->best_history = helper->current_history;
	helper->is_history_need = FALSE;
	return (helper->best_history);
}
