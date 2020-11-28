#include "lem_in.h"

void	reset_state(t_vector *nodes, int except_mark)
{
	t_node_ptr	ptr;
	int			index;

	index = -1;
	while (++index < nodes->size)
	{
		ptr = get_from_node_vec(nodes, index);
		if (ptr->traversal_state != except_mark)
			ptr->traversal_state = STATE_NO_INVOLVED;
		ptr->bfs = 0;
		if (except_mark == STATE_NONE)
		{
			ptr->is_first_cross = FALSE;
			ptr->is_cross = 0;
		}
		remove_all_not_free(&ptr->ants);
	}
}

int		reset_all_states(t_vector *nodes)
{
	reset_state(nodes, STATE_NONE);
	return (TRUE);
}

void	reset_all_edges(t_vector *nodes)
{
	t_edge		*edge;
	t_node_ptr	node;
	int			way_i;
	int			i;

	way_i = -1;
	while (++way_i != nodes->size)
	{
		node = get_from_vec(nodes, way_i);
		i = -1;
		while (++i != node->links.size)
		{
			edge = get_from_vec(&node->links, i);
			reset_edge(edge);
		}
	}
}
