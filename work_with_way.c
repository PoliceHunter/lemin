/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_way.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:20 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:23:22 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	shift_array_right(void *array, unsigned int size,
						unsigned int element_size)
{
	ft_memmove(array + element_size, array, (size - 1) * element_size);
	ft_memset(array, 0, element_size);
}


void remove_all_not_free(t_vector *ants)
{
	int i;

	i = -1;
	if (ants->size == 0)
		return;
	while (++i < ants->size)
	{
		remove_from_vec(ants, i);
	}
}
// Return number of ant or NO_ANT
int		make_way_step(t_way *way)
{
	t_node_ptr	prev;
	t_node_ptr	curr;
	size_t		i;

	i = way->nodes.size;
	//// Потенциально может возникнуть ошибка, если у нас
	while (--i > 0) // i := (size, 0]
	{
		curr = *(t_node_ptr *) get_from_vec(&way->nodes, i);
		prev = *(t_node_ptr *) get_from_vec(&way->nodes, i - 1);

		if (prev->ants.size == 0)
			continue;

		int * ant = pop_front_vec(&prev->ants);
		emplace_back_vec(&curr->ants, ant); // Закидываем в вектор мурашей мураша
		free(ant);
	}
	curr = *(t_node_ptr *) get_last(&way->nodes); // dst node
	ft_assert(curr->is_end_node, "Error last way node isn't last");
	return (curr->ants.size);
}

//static size_t			count_words(const char *s, char c)
//{
//	size_t index;
//	size_t words;
//
//	index = 0;
//	words = 0;
//	while (s[index] != '\0')
//	{
//		while (s[index] == c)
//			index++;
//		while (s[index] != c && s[index] != '\0')
//		{
//			words++;
//			while (s[index] != c && s[index] != '\0')
//				index++;
//		}
//	}
//	return (words);
//}

