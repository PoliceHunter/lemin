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
	int			finished_ant;
	size_t		i;

	i = way->nodes.size;
	//// Потенциально может возникнуть ошибка, если у нас
	//	remove_all_not_free(&curr->ants);
	// curr->ant_number = NO_ANT; // Очистить вектор с мурашами, но не удалить
	while (--i > 0) // i := (size, 0]
	{
		curr = *(t_node_ptr*)get_from_vec(&way->nodes, i);
		prev = *(t_node_ptr*)get_from_vec(&way->nodes, i - 1);

		if (prev->ants.size == NO_ANT)
			continue;

		push_back_vec(&curr->ants, get_from_vec(&prev->ants, 0));//Закидываем в вектор мурашей мураша
		//curr->ant_number = prev->ant_number;
		//prev->ant_number = NO_ANT;
		remove_all_not_free(&prev->ants);// Удаляем из текущего вектора мурашей мураша он может быть только один
	}
	curr = *(t_node_ptr*)get_last(&way->nodes); // Dst node
	ft_assert(curr->is_end_node, "Error last way node isn't last");
	finished_ant = curr->ants.size; // В кол-во пришедших муравшей кладем размер вектора дляя мурашей
	return (finished_ant);
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

