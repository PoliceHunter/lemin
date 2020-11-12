//
// Created by Taisha Myrcella on 11/11/20.
//

#include "lem_in.h"

t_way			*new_way(char *raw_way, const char separator)
{
	t_way *result;

	result = (t_way *)malloc(sizeof(t_way));
	result->way_nodes = ft_strsplit_with_len(raw_way, separator,
											 &result->way_len);
	result->ants = malloc(sizeof(unsigned short) * result->way_len);
	ft_memset(result->ants, 0, sizeof(unsigned short) * result->way_len);
	free(raw_way);
	return (result);
}

void			shift_array_right(void *array, unsigned int size,
								  unsigned int element_size)
{
	ft_memmove(array + element_size, array, (size - 1) * element_size);
	ft_memset(array, 0, element_size);
}

int				make_way_step(t_way *way)
{
	int result;

	result = 0;
	if (way->ants[way->way_len - 1] != 0)
		result = 1;
	shift_array_right(way->ants, way->way_len, sizeof(unsigned short));
	return (result);
}

void			find_ways(t_node_ptr src, t_node_ptr dst, char *tmp_buffer,
						  t_vector *ways)
{
	t_way		*way;
	t_node_ptr	*child;
	int			i;

	i = -1;
	way = NULL;
	tmp_buffer = ft_strjoin_free(ft_strjoin_free(tmp_buffer, src->name), " ");
	while (++i != (src)->links.size)
	{
		child = get_from_vec(&(src)->links, i);
		if ((*child)->bfs <= src->bfs)
			continue;
		if (ft_strcmp((*child)->name, dst->name) != 0)
		{
			find_ways(*child, dst, ft_strdup(tmp_buffer), ways);
			continue;
		}
		way = new_way(ft_strjoin_free(tmp_buffer, dst->name), ' ');
		insert_with_sort(ways, way, &cmp_way);
		free(way);
		return ;
	}
	free(tmp_buffer);
}