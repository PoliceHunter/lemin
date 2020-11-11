//
// Created by Taisha Myrcella on 11/11/20.
//

#include "lem_in.h"

int				is_cross(t_way *left, t_way *right)
{
	unsigned int	i;
	unsigned int	j;

	i = 1;
	while (i < left->way_len - 1)
	{
		j = 1;
		while (j < right->way_len - 1)
		{
			if (ft_strcmp(left->way_nodes[i], right->way_nodes[j]) == 0)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int				cmp_way(void *left_way, void *right_way)
{
	t_way			*left;
	t_way			*right;
	unsigned int	index;

	left = left_way;
	right = right_way;
	if (left->way_len == right->way_len)
	{
		index = 0;
		while (index < left->way_len && index < right->way_len)
		{
			if (left->way_nodes[index] < right->way_nodes[index])
				return (1);
			index++;
		}
	}
	return (left->way_len > right->way_len);
}

int				is_cross_group(t_vector *group, t_way *way)
{
	int index;

	index = 0;
	while (index != group->size)
	{
		if (is_cross(get_from_vec(group, index), way))
			return (1);
		++index;
	}
	return (0);
}

t_vector		get_non_crossing_group(t_vector *ways, t_way *init_way)
{
	t_way		*current_way;
	t_vector	group;
	int			index;

	index = -1;
	group = new_vector(ways->size, sizeof(t_way));
	push_back_vec(&group, init_way);
	while (++index != ways->size)
	{
		current_way = get_from_vec(ways, index);
		if (current_way == init_way)
			continue;
		if (!is_cross_group(&group, current_way))
			insert_with_sort(&group, current_way, &cmp_way);
	}
	return (group);
}

int				is_group_identical(const t_vector left_group,
									  const t_vector right_group)
{
	const t_way	*left;
	const t_way	*right;
	int			index;

	index = 0;
	if (left_group.size != right_group.size)
		return (0);
	while (index != left_group.size)
	{
		left = get_from_vec_const(&left_group, index);
		right = get_from_vec_const(&right_group, index);
		if (left->way_len != right->way_len)
			return (0);
		++index;
	}
	return (1);
}