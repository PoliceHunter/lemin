#include "lem_in.h"

t_solver_helper	init_helper(void)
{
	t_solver_helper	res;

	res.best_ant_step = INT_MAX;
	res.current_ant_step = 0;
	res.best_history = NULL;
	res.current_history = NULL;
	return (res);
}

void			candidate_win(t_solver_helper *helper)
{
	if (helper->best_history != NULL)
		free(helper->best_history);
	helper->best_ant_step = helper->current_ant_step;
	helper->best_history = helper->current_history;
	helper->current_history = NULL;
	helper->is_history_need = FALSE;
	helper->current_ant_step = 0;
}

t_ants_tracker	init_tracker(size_t count)
{
	t_ants_tracker result;

	result.ready_to_go = count;
	result.all = count;
	result.finished = 0;
	return (result);
}
