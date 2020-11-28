#include "lem_in.h"

t_way	*get_place_for_way(t_vector *vec)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	++vec->size;
	return (get_last(vec));
}

t_way	*get_last_way(t_vector *vec)
{
	return (get_last(vec));
}

void	free_way(t_way *way)
{
	free_vec(&way->nodes);
	free_vec(&way->edges);
	free(way);
}

void	free_ways(t_vector *ways)
{
	if (ways->size == 0)
	{
		free_vec(ways);
		return ;
	}
	while (ways->size != 0)
		free_way(pop_back_vec(ways));
	if (ways->data != NULL)
		free_vec(ways);
}
