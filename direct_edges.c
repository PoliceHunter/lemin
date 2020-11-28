#include "lem_in.h"

void	disable_edge(t_edge *edge)
{
	edge->capacity = 0;
	edge->backward->capacity = 0;
	edge->mark = MARK_DISABLE;
	edge->backward->mark = MARK_DISABLE;
}

void	reset_edge(t_edge *edge)
{
	if (edge->mark == MARK_DISABLE ||
	edge->backward->dst->is_first_cross == TRUE)
	{
		edge->capacity = 0;
		edge->backward->capacity = 0;
		return ;
	}
	edge->capacity = edge->original_capacity;
	edge->backward->capacity = edge->backward->original_capacity;
	edge->mark = MARK_NONE;
}

void	direct_edge(t_edge *edge)
{
	ft_assert(edge->capacity == 1 && edge->backward->capacity == 1,
	"You try to reduce wrong edge");
	edge->capacity = 0;
	edge->backward->capacity = 1;
}

void	mark_edge(t_edge *edge)
{
	edge->mark = MARK_FORWARD_PATH;
	edge->backward->mark = MARK_BACKWARD_PATH;
}

void	direct_and_mark_way_edges(t_way *way)
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i != way->edges.size)
	{
		edge = *(t_edge **)get_from_vec(&way->edges, i);
		if ((edge->backward->dst->is_cross == 1 ||
			edge->backward->dst->is_first_cross == TRUE) && edge->dst->is_cross)
		{
			disable_edge(edge);
			continue ;
		}
		direct_edge(edge);
		mark_edge(edge);
	}
}
