/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tracker_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:52:08 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:52:09 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_solver_helper		init_helper(void)
{
	t_solver_helper res;

	res.best_ant_step = INT_MAX;
	res.current_ant_step = 0;
	res.best_history = NULL;
	res.current_history = NULL;
	res.is_history_need = FALSE;
	res.best_ways = new_vector(1, sizeof(t_way));
	return (res);
}

t_track				init_tracker(size_t count)
{
	t_track result;

	result.ready_to_go = count;
	result.all = count;
	result.finished = 0;
	result.ants_in_way = 0;
	return (result);
}
